## **SocketCAN Communication System**

## **Project Description**
This project implements a communication system between a **Host Linux** machine and an **Electronic Control Unit (ECU)** using **SocketCAN**. The system leverages various CAN protocols to ensure efficient data exchange and is built with a focus on modular design, threading, and testing.

---

## **Features**

### **SocketCAN Communication**
- Establishes a communication link between Host Linux and the ECU using SocketCAN.
- Enables seamless data transmission and reception via CAN protocols.

### **CAN Interface Management**
- Implements C++ classes for managing CAN communication.
- Supports operations such as:
  - Connecting to the CAN interface.
  - Sending and receiving CAN frames.
  - Disconnecting from the CAN interface.

### **Unit Testing**
- Comprehensive unit tests for critical functionalities, including:
  - Connecting
  - Sending
  - Receiving
  - Disconnecting
- Tests are implemented using **Google Test**.

### **Threading for Data Handling**
- Utilizes threading concepts for efficient data handling.

### **Build Management**
- Configured with **CMake** for simplified project build and dependency management.

## **Technologies Used**
- **Programming Language**: C++
- **Build Tool**: CMake
- **CAN Communication**: SocketCAN
- **Operating System**: Linux
- **Testing Framework**: Google Test
- **Programming Paradigm**: Object-Oriented Programming (OOP)
