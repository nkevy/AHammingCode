//client.h is a src file for the ham_send binary
//contains the header file for the client.cpp file
#ifndef CLIENT_H
#define CLIENT_H
//for thread and buffer
#include <thread>
#include <atomic>
#include <functional>
#include <stdexcept>
//for socket
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <unistd.h>
//for hamm
#include "hamm.h"
using namespace std;
#endif

