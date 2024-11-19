cmake_minimum_required(VERSION 3.10)
project(DEMO)
include_directories( ${CMAKE_SOURCE_DIR}/Poco/include/
) #needed!!
link_directories(${CMAKE_SOURCE_DIR}/Poco/lib) #needed !!

find_package(Poco REQUIRED COMPONENTS Foundation Net Util ) #needed!!

#libsocketcan.h
include_directories(${CMAKE_SOURCE_DIR}/LibSocketCan/inc)
link_directories(${CMAKE_SOURCE_DIR}/LibSocketCan/lib)

add_subdirectory(App) 
#add_subdirectory(Test)

add_subdirectory(CANLib)



