/**
 * @file CHAL_SocketCAN.h
 * @author Amir Jribi
 * @brief Header file for the CHAL_SocketCAN class
 * @version 0.1
 * @date 2024-08-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#ifndef CHALSOCKETCAN_H
#define CHALSOCKETCAN_H

#include "SocketCan.h"
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
typedef struct {
        uint32_t can_id;
        uint8_t can_dlc;
        uint8_t data[8];
} T_stCOM_CANFrame;
typedef enum
{
eCOMStatus_NoError = 0, 
eCOMStatus_NoDeviceConnected,
eCOMStatus_DeviceNotInUse,
eCOMStatus_ConfigurationError,
eCOMStatus_DeviceOff,
eCOMStatus_DeviceBusy,
eCOMStatus_DeviceBusError,
eCOMStatus_DeviceDriverNotFound,
eCOMStatus_Error_OtherDeviceConnected,
eCOMStatus_Error_Internal,
eCOMStatus_Error_Unknown,
} T_eCOM_Status;




class CHAL_SocketCAN{
private:
    Poco::BasicEvent<T_stCOM_CANFrame>m_pRXEvent; // notify when frames has been received
    Poco::BasicEvent<T_stCOM_CANFrame>m_pTXEvent; // notify when frames has been sent
    Poco::BasicEvent<T_stCOM_CANFrame>m_pErrEvent;
    bool stopListen=false;
    std::thread listener;
    SocketCAN socketCAN;
    const char* interface="can0";
    int bitrate=250000;
    

public:
    T_eCOM_Status status=eCOMStatus_NoError;
    /**
     * @brief Construct a new chal socketcan object , Default constructor
     * 
     */
    CHAL_SocketCAN();
    /**
     * @brief Construct a new chal socketcan object , Parameterized Constructor
     * 
     * @param _interface 
     * @param _bitrate 
     */
    CHAL_SocketCAN(const char* _interface , int _bitrate);
    /**
     * @brief Destroy the chal socketcan object
     * The destructor joins the listener thread if it is joinable.
     * 
     */
    ~CHAL_SocketCAN();
    /**
     * @brief configures the bitrate.brings up the CAN interface. 
     * sets up a raw CAN socket, binds it to the specified CAN interface.
     * 
     * @return T_eCOM_Status 
     */
    T_eCOM_Status connect();
    /**
     * @brief Starts the listener thread for receiving CAN frames.
     * 
     * This method creates and starts a thread.
     * 
     */
    void createEventThread();
     /**
     * @brief Runs the listener thread.
     * 
     * This method is executed by the listener thread and continuously reads CAN frames
     * from the CAN interface.
     */
    void run();
    /**
     * @brief changing the flag stopListen to true
     * joins the listener thread if it is joinable.
     * 
     */

    void stop();
    /**
     * @brief Reads a CAN frame from the CAN interface.
     * 
     * @param frame 
     * @return T_eCOM_Status 
     */
    T_eCOM_Status readFrame(T_stCOM_CANFrame* frame);
    /**
     * @brief Sends a CAN frame to the CAN interface.
     * 
     * @param frame 
     * @return T_eCOM_Status 
     */
    T_eCOM_Status writeFrame(T_stCOM_CANFrame frame);
    /**
     * @brief Event fired when a CAN frame is sent.
     * This event is triggered whenever a CAN frame is sent to the CAN interface.
     * 
     * @return Poco::BasicEvent<T_stCOM_CANFrame>* 
     */
    Poco::BasicEvent<T_stCOM_CANFrame>* GetTxEvent();
    /**
     * @brief Event fired when a CAN frame is received.
     * This event is triggered whenever a CAN frame is received from the CAN interface.
     * @return Poco::BasicEvent<T_stCOM_CANFrame>* 
     */
    Poco::BasicEvent<T_stCOM_CANFrame>* GetRxEvent();
    Poco::BasicEvent<T_stCOM_CANFrame>* GetErrEvent();
    /**
     * @brief Disconnects from the CAN interface.
     * 
     * @return T_eCOM_Status 
     */
    T_eCOM_Status disconnect();
};



#endif //CHALSOCKETCAN_H