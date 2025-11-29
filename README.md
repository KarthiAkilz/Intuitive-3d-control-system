# **🕹️ Intuitive 3D Control System \- Unreal Engine 5.6 \+ WebSocket Integration**

This project demonstrates a **hybrid interaction system** built in Unreal Engine 5.6, featuring a custom WebSocket communication layer developed in Visual Studio, and a mobile-friendly HTML controller interface. The system enables real-time interaction, external device control, and AR-style camera movement directly inside an Unreal Engine level.

## **🖼️ Project Overview**

This demo integrates multiple components into one cohesive pipeline:

| Component | Description |
| :---- | :---- |
| **UE5 C++ WebSocket Manager** | Handles incoming commands, parses JSON payloads, and triggers Blueprint events for movement, camera rotation, and interactions. |
| **HTML Controller** | A mobile-friendly web interface that includes joystick movement, buttons, and gyroscope data streaming via WebSockets. |
| **Node.js WebSocket Server** | Acts as a communication bridge in terminal between the mobile browser and Unreal Engine. Runs through any terminal (CMD, PowerShell, or VS Code terminal). |

This architecture enables seamless control of in-engine actors from an external device without packaging or plugins.

## **✨ Interaction Features**

### **Hover Interaction**

Objects react to mouse hover using physics-based impulse and color-driven Niagara FX.

<img width="1665" height="933" alt="Cursor_Interactions" src="https://github.com/user-attachments/assets/c4a5aa84-a057-4a44-9b40-6b50c708e7e8" />


### **Grab & Throw System**

* Floating behavior while grabbed  
* Niagara FX activation  
* Physics-based throw impulse  
* Target-ball destruction on impact

<img width="1654" height="907" alt="Throw" src="https://github.com/user-attachments/assets/583e60c7-124e-4a07-9570-8ebc49838245" />
<img width="1650" height="879" alt="Grab" src="https://github.com/user-attachments/assets/15aa4099-6b56-4f93-8541-63e88b5758c7" />


### **WebSocket Controller Interface**

A single-page HTML controller featuring:

* Joystick movement  
* Button inputs  
* Live status indicators

Works across:

* UE PIE (Play In Editor)  
* HTML Client  
* Terminal JSON Testing  
* Wireless Display (Mobile Browser)

### **Gyroscope Over WebSocket**

Real-time gyroscope data from mobile device drives:

* Camera rotation  
* Character orientation  
* AR-style navigation

<img width="1642" height="922" alt="Websocket+Controller" src="https://github.com/user-attachments/assets/35483301-64cb-4fe8-9ad6-ff928ca80c61" />


## **📐 Architecture**

The command flow for the hybrid system is sequential and synchronous:

**Mobile Browser ➡️ WebSocket ➡️ Node.js ➡️ UE5 C++ Module ➡️ Blueprint Events**

* **HTML:** Input capture (joystick, taps, gyroscope)  
* **WebSocket Server:** Routes commands to Unreal  
* **UE C++ Manager:** Parses JSON, triggers gameplay logic  
* **Blueprint:** Implements FX, grab/throw, hover logic

## **⚙️ Setup Instructions**

### **1\. Run WebSocket Server**

The Node.js server automatically listens on all available network interfaces.

1. Navigate to the directory containing server.js.  
2. Run the server using the following command:  
   node server.js

### **2\. Update Controller IP**

You must update the WebSocket address to point to the local network IP address of the machine running the **Node.js server**.

Replace ws://\<YOUR\_IP\>:8081 with your server's actual IP address in the following files:

* controller.html  
* UWebSocketManager.cpp

### **3\. Open Controller on Mobile**

Open the controller.html file through:

* Local network HTTP server (Recommended for best performance)  
* Or directly using file:// (if the browser allows WebSocket connections from local files)

### **4\. Play in Unreal Engine**

Press **Play in Editor (PIE)** and interact using the mobile browser.

## **🎬 Demo Video**

[YouTube link](https://youtu.be/AtbV6i2aLs8)

## **🏷️ Tags**

| Category | Tags |
| :---- | :---- |
| **Technologies** | Unreal Engine 5 (UE5), C++, WebSocket, JavaScript, Node.js |
| **System Type** | Hybrid Controller, Interaction Systems, Remote Control, Client-Server |
| **Key Features** | AR-style controls, Gyroscope Control, Unreal C++, WebSocket Unreal Engine, Hybrid controller UE5, JavaScript controller UE |

## **👤 Created By**

Karthikeyan Akilan

Interactive Systems | Unreal Engine | JavaScript | C++ | WebSocket Integration
