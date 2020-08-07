////////////////////////////////////////////////////////////////
//ham_send.cpp is the main src file for the ham_send binary
//ham_send will send a message to another ham_send program
//ham_send employs the hamming code error correction algorithm
//author: nkevy
//git: https://github.com/nkevy/AHammingCode.git
////////////////////////////////////////////////////////////////
#include "ham_send.h"
int main(int argc,char* argz[]){
	if(1!=argc){
		cout<<"[Usage] ham_send"<<endl;
		cout<<"[Usage] Max length is 100 characters."<<endl;
		cout<<"[Usage] To quit send an empty message."<<endl;
	}
	string host, port;
	cout<<"Enter the host ip you wish to contact:"<<endl;
	cin>>host;
	cout<<"Enter the port you wish to use:"<<endl;
	cin>>port;
	ham_server ham(host,port);
	ham.start();
}
