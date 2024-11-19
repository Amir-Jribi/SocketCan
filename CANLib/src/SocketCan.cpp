#include "SocketCan.h"
#include <set>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <net/if.h>  
#include <sys/socket.h> 
#include <sys/ioctl.h> 
#include <linux/can/raw.h> 
#include <cerrno>
#include <cstring>

SocketCAN::SocketCAN(){}

SocketCAN::~SocketCAN(){
    if(sockfd_){
        close(sockfd_);
    }
}
bool SocketCAN::open(std::string ifc){
#ifdef __arm__
    sockfd_=socket(PF_CAN,SOCK_RAW,7);
#else 
    sockfd_=socket(PF_CAN,SOCK_RAW,CAN_RAW);
#endif 
    if (-1 == sockfd_){
        std::cerr<<"Failed to open CAN_RAW socket: "<<std::endl;
        return false;
    }
    struct ifreq ifr;
    snprintf(ifr.ifr_name,sizeof(ifr.ifr_name),"%s",ifc.c_str());
    if (-1 == ioctl(sockfd_,SIOGIFINDEX,&ifr)){
        std::cerr<< "Failed to get interface index for "<<ifc<<std::endl;
        return false;
    }
    struct sockaddr_can addr;
    addr.can_family=PF_CAN ;
    addr.can_ifindex=ifr.ifr_ifindex;
    if (-1 == bind(sockfd_,(struct sockaddr*)&addr,sizeof(addr))){
        std::cerr<< "Failed to bind the interface "<<ifc<<std::endl;
        return false;
    }
    return true;
}

bool SocketCAN::send(uint32_t id , uint8_t *data , uint8_t dlc){
    struct can_frame frame;
    frame.can_id=id;
    frame.can_dlc=dlc;
    memcpy(frame.data,data,dlc);
    if(sizeof(frame)!=write(sockfd_,&frame,sizeof(frame))){
        perror("CAN frame write fail :");
        return false;
    }
    return true;
}

bool SocketCAN::receive(uint32_t *id , uint8_t *data , uint8_t *dlc){
    struct can_frame frame;
    if (-1 == sockfd_){
        std::cout<<"No socket open"<<std::endl;
        return false;
    }
    int n_read=read(sockfd_,&frame,sizeof(frame));
    if (-1 == n_read){
        perror("SocketCAN::receive()");
    }
    if (n_read ==sizeof(frame)){
        *id=frame.can_id;
        *dlc=frame.can_dlc;
        memcpy(data,frame.data,frame.can_dlc);
        return true;
    }
    else {
        std::cerr<<"Incomplete CAN frame received, read"<<n_read<<std::endl;
        return false;
    } 
}