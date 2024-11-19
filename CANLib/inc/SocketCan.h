/**
 * @file SocketCan.h
 * @author Amir Jribi
 * @brief Header file for the SocketCan class
 * @version 0.1
 * @date 2024-08-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef DEMO_CAN_SOCKETCAN_H_
#define DEMO_CAN_SOCKETCAN_H_
#include <linux/can.h>
#include <linux/can/error.h>
#include <unistd.h>
#include <set>
#include <string>


class SocketCAN
{
public:
        /**
         * @brief Construct a new Socket CAN object
         * 
         */
        SocketCAN();
        /**
         * @brief Destroy the Socket CAN object
         * 
         */
        ~SocketCAN();
        /**
         * @brief set up a raw CAN socket in Linux for communication with the CAN bus
         * 
         * @param ifc 
         * @return true 
         * @return false 
         */
        bool open(std::string ifc);
        /**
         * @brief Sends a CAN frame to the CAN0 interface.
         * 
         * @param id 
         * @param data 
         * @param dlc 
         * @return true 
         * @return false 
         */
        bool send(uint32_t id , uint8_t *data , uint8_t dlc);
        /**
         * @brief Reads a CAN frame from the CAN0 interface.
         * 
         * @param id 
         * @param data 
         * @param dlc 
         * @return true 
         * @return false 
         */
        bool receive(uint32_t *id,uint8_t *data,uint8_t *dlc);
private:
        int sockfd_;

};



#endif /* DEMO_CAN_SOCKETCAN_H_ */