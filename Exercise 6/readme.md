# Server-Client Monitoring System

## Overview
This system allows multiple clients to connect to a server. Clients can send messages to the server, which then broadcasts these messages to all connected clients.

## Requirements
- GCC Compiler

## Compilation Instructions
Compile the server and client programs using the following commands:
```bash
gcc -o server server.c -lpthread
gcc -o client client.c
