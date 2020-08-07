//client.h is a src file for the ham_send binary
//contains the header file for the client.cpp file
#ifndef CLIENT_H
#define CLIENT_H
//for thread and buffer
//for socket
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#define BUFFERSIZE 512
//for hamm
#include "hamm.h"
using namespace std;
class ham_server{
	public:
		ham_server(string host,string port);
		void start(void);
		void stop(void);
	private:
		struct addrinfo hint;
		int sock;
		int address_info;
		char buffer[BUFFERSIZE];
		bool signal_stop;
		string get_msg();
};
#endif

