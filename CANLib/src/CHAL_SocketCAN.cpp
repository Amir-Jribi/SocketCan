#include "CHAL_SocketCAN.h"
#include "SocketCan.h"
#include "libsocketcan.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <thread>
#include <Poco/Delegate.h>
#include <Poco/BasicEvent.h>
#include <cstring>
#include <unistd.h> 
#include <net/if.h>  
#include <sys/socket.h> 
#include <sys/ioctl.h> 
#include <linux/can.h> 
#include <linux/can/raw.h> 
#include <iomanip>


CHAL_SocketCAN::CHAL_SocketCAN(const char* _interface , int _bitrate):interface(_interface),bitrate(_bitrate){}
CHAL_SocketCAN::CHAL_SocketCAN(){}
CHAL_SocketCAN::~CHAL_SocketCAN(){
    if (listener.joinable()){
            listener.join();
    }
}
T_eCOM_Status CHAL_SocketCAN::connect(){
            status=eCOMStatus_NoError;
            if (can_set_bitrate(interface, bitrate) == -1) { 
                perror("Error setting bitrate");
                return status=eCOMStatus_NoDeviceConnected;
            }

            if (can_do_start(interface) == -1) { 
                perror("Error starting CAN interface");
                return status=eCOMStatus_NoDeviceConnected;
            }
            bool result=socketCAN.open(interface);
            if (result==0){
                status=eCOMStatus_Error_Internal;
                return status;
            }
            this->createEventThread();
            return status;
}
    
void CHAL_SocketCAN::createEventThread(){
    listener=std::thread(&CHAL_SocketCAN::run,this);  
}

void CHAL_SocketCAN::stop(){
        stopListen = true; 
        if (listener.joinable()) {
            listener.join(); 
        }
}
T_eCOM_Status CHAL_SocketCAN::disconnect(){
        status=eCOMStatus_NoError;
        this->stop();
          if (can_do_stop(interface) == -1){
            perror("Error closing CAN interface");
            return status=eCOMStatus_Error_Internal;
        }
        return status;
}
void CHAL_SocketCAN::run(){
        while(!stopListen){
            T_stCOM_CANFrame* frame;
            this->readFrame(frame);
            m_pRXEvent.notify(this,*frame);
        }
    }

T_eCOM_Status CHAL_SocketCAN::readFrame(T_stCOM_CANFrame* frame){
    status=eCOMStatus_NoError;
    bool result=socketCAN.receive(&(frame->can_id),frame->data,&(frame->can_dlc)); 
    if (result==0){
        status=eCOMStatus_Error_Internal;
        return status;
    }
    return status;
}
T_eCOM_Status CHAL_SocketCAN::writeFrame(T_stCOM_CANFrame frame){
    status=eCOMStatus_NoError;
    bool result=socketCAN.send(frame.can_id,frame.data,frame.can_dlc);
    if (result==0){
        return status=eCOMStatus_Error_Internal;
    }
    m_pTXEvent(this,frame);
    return status;
}

Poco::BasicEvent<T_stCOM_CANFrame>* CHAL_SocketCAN::GetTxEvent(){
        return &m_pTXEvent;
}
Poco::BasicEvent<T_stCOM_CANFrame>* CHAL_SocketCAN::GetRxEvent(){
        return &m_pRXEvent;
}
Poco::BasicEvent<T_stCOM_CANFrame>* CHAL_SocketCAN::GetErrEvent(){
        return &m_pErrEvent;
}

