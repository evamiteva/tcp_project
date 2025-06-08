# TCP Client-Server Application in C++

This repository contains a simple **TCP client-server** application written in C++. The client connects to the server, sends formatted messages, and receives appropriate responses.

## 🧠 Features

- **Server:**
  - Listens for incoming TCP connections on a fixed port.
  - Reads messages from connected clients.
  - Sends back responses based on received input.
  - Terminates connection based on specific keywords.

- **Client:**
  - Connects to the server at a predefined IP and port.
  - Takes user input in a specific format (`Prv/Vtor/Tret/Cetvrt`) and sends it to the server.
  - Displays the response from the server.
  - Ends the session when certain conditions are met.

## 📁 Files

- `client.cpp` – the TCP client implementation.
- `server.cpp` – the TCP server implementation (make sure it is placed here).
  
> If `server.cpp` is not yet added, please include it to complete the project setup.

## 🛠️ Requirements

- C++ compiler (e.g., `g++`)
- POSIX-compliant system (Linux/MacOS)
- Open ports if running on a networked environment

## ⚙️ Compilation

Compile both the client and server using `g++`:

```bash
g++ -o server server.cpp
g++ -o client client.cpp
