/**
 * @file CANTest.cpp
 * @author Amir Jribi
 * @brief This file contains unit tests for the `CHAL_SocketCAN` class.
 * @version 0.1
 * @date 2024-08-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <bits/stdc++.h>
#include <gtest/gtest.h>
#include "CHAL_SocketCAN.h"
#include "SocketCan.h"

using namespace std;

T_eCOM_Status expected=eCOMStatus_NoError;


/**
 * @brief Test the `connect` function of the CHAL_SocketCAN class.
 * Make sure that the pcan_usb is not plugged in !
 */

TEST(CANTest,connectionError){
    CHAL_SocketCAN socketCAN;
    expected=eCOMStatus_NoDeviceConnected;
    T_eCOM_Status res=socketCAN.connect();
    ASSERT_EQ(expected, socketCAN.connect());
}


/**
 * @brief Test the `writeFrame` of the CHAL_SocketCAN class.
 * Ensure that the hardware is correctly connected and configured.
 */


TEST(CANTest, write) 
    { 
    CHAL_SocketCAN socketCAN();
    socketCAN.connect();
    socketCAN.stop();
     T_stCOM_CANFrame frameToSend;
    frameToSend.can_id=0x700;
    frameToSend.can_dlc=8;
    frameToSend.data[0]=0x02;
    frameToSend.data[1]=0x10;
    frameToSend.data[2]=0x02;
    frameToSend.data[3]=0xFF;
    frameToSend.data[4]=0xFF;
    frameToSend.data[5]=0xFF;
    frameToSend.data[6]=0xFF;
    frameToSend.data[7]=0xFF;
    T_eCOM_Status res=socketCAN.writeFrame(frameToSend);
    socketCAN.disconnect();
    
    //sockCAN.
    ASSERT_EQ(expected, res);
    }


/**
 * @brief Test the `readFrame` of the CHAL_SocketCAN class.
 * Ensure that the hardware is correctly connected and configured.
 */

TEST(CANTest, read) 
    { 
    CHAL_SocketCAN socketCAN;
    socketCAN.connect();
    T_stCOM_CANFrame frameToReceive;
    T_stCOM_CANFrame frameToSend;
    socketCAN.stop();
    frameToSend.can_id=0x700;
    frameToSend.can_dlc=8;
    frameToSend.data[0]=0x02;
    frameToSend.data[1]=0x10;
    frameToSend.data[2]=0x02;
    frameToSend.data[3]=0xFF;
    frameToSend.data[4]=0xFF;
    frameToSend.data[5]=0xFF;
    frameToSend.data[6]=0xFF;
    frameToSend.data[7]=0xFF;
    socketCAN.writeFrame(frameToSend);
    T_eCOM_Status res=socketCAN.readFrame(&frameToReceive);
    socketCAN.disconnect();
    ASSERT_EQ(expected, res);
    }

/**
 * @brief Test the `disconnect` of the CHAL_SocketCAN class.
 * Ensure that the hardware is correctly connected and configured.
 */
TEST(CANTest,disconnect){
    CHAL_SocketCAN socketCAN;
    socketCAN.connect();
    T_eCOM_Status res=socketCAN.disconnect();
    ASSERT_EQ(expected, res);
}

/**
 * @brief Test the `connect` of the CHAL_SocketCAN class.
 * Ensure that the hardware is correctly connected and configured.
 */
TEST(CANTest,connect){
    CHAL_SocketCAN socketCAN;
    T_eCOM_Status res=socketCAN.connect();
    socketCAN.disconnect();
    ASSERT_EQ(expected, socketCAN.connect());
}


/**
 * @brief Running all the tests
 * make sure to execute the file with sudo !
 * @param argc 
 * @param argv 
 * @return int 
 */
 
int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}