UDP-Server
==================

This is a UDP Server which defaults to **local PORT NUMBER:1234** and sends info to **remote PORT NUMBER:12345** at multicast address **238.0.0.1**


## Makefile Commands

This project includes a Makefile which can be invoked for different common actions

### make
	
	Will compile the server.cpp code and generate a server executable

### make e

	Will open server.cpp in the *nano* editor

### make run

	Will run the server executable in the background

### make kill
	Will kill all instances of *server*
