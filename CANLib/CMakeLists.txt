set(CAN_LIB_SOURCES
src/SocketCan.cpp
src/CHAL_SocketCAN.cpp
)


add_library(CANLib STATIC ${CAN_LIB_SOURCES})

target_link_libraries(CANLib PUBLIC socketcan Poco::Foundation
   Poco::XML
    Poco::Util
    Poco::Net
)


target_include_directories(CANLib PUBLIC inc)