////////////////////////////////////////////////////////////////
//ham_send.cpp is the main src file for the ham_send binary
//ham_send will send a message to another ham_send program
//ham_send employs the hamming code error correction algorithm
//author: nkevy
//git: https://github.com/nkevy/AHammingCode.git
////////////////////////////////////////////////////////////////
#include "ham_send.h"
int main(int argc,char* argz[]){
	if(1==argc){
		std::cout<<"[Usage] ham_send <message>\n[Usage] max length is 64 characters"<<std::endl;
	}
}
