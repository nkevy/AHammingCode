//client.cpp is a src file for ham_send 
//contains the classes used to send and receive messages 
#include "client.h"
// ham server class
// Yes the client.cpp contains a server.
// The ham server is a simple socket implementation.
// The socket sends a user defined message then waits for a response. 
ham_server::ham_server(string host,string port){
	// ai_family
        //      This field specifies the desired address family for the
        //      returned addresses.  Valid values for this field include
        //      AF_INET and AF_INET6.  The value AF_UNSPEC indicates that
        //      getaddrinfo() should return socket addresses for any address
        //      family (either IPv4 or IPv6, for example) that can be used
        //      with node and service.
	ham_server::hint.ai_family = AF_UNSPEC;
	// ai_socktype
        //      This field specifies the preferred socket type, for example
        //      SOCK_STREAM or SOCK_DGRAM.  Specifying 0 in this field indi‐
        //      cates that socket addresses of any type can be returned by
        //      getaddrinfo().
	ham_server::hint.ai_socktype = SOCK_DGRAM;
	// ai_flags
        // 	This field specifies additional options, described below.
        // 	Multiple flags are specified by bitwise OR-ing them together.
	ham_server::hint.ai_flags = 0;
	// ai_protocol
	//	Must contain a 0;
	ham_server::hint.ai_protocol = 0;
	// Local variables
	struct addrinfo *result, *rp;
	// Get address list.
	int temp = getaddrinfo(host.c_str(),port.c_str(),&(ham_server::hint),&(result));
	if (temp){
		cout<<"[ERROR] Could not find host."<<endl;
		exit(EXIT_FAILURE);
	}
	ham_server::address_info = temp;
	int sfd;
	for(rp=result;rp!=NULL;rp=rp->ai_next){
		sfd = socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
		if(-1==sfd) continue;
		if(-1!=connect(sfd,rp->ai_addr,rp->ai_addrlen))
			break;
		close(sfd);
	}
	if(NULL==rp){
		cout<<"[ERROR] Could not connect."<<endl;
		exit(EXIT_FAILURE);
	}
	freeaddrinfo(result);
	ham_server::sock = sfd;
}	
void ham_server::stop(void){
	ham_server::signal_stop=true;
}
string ham_server::get_msg(void){
	string msg;
	while(!msg.size()){
		cout<<"Enter Text (limit 100 characters):"<<endl;
		cin>>msg;
		if(0==msg.size()){
			cout<<"Stop the program (y/n)?"<<endl;
			cin>>msg;
			if ("y"==msg){
				ham_server::stop();
				msg = "Client has disconnected.";
			}else{
				msg="";
			}
		}
		if(100<msg.size()){
			cout<<"\nText message must be less than 100 characters, try again."<<endl;
			msg="";
		}
	}
	// Encode with the hamming class
	msg=hamming::encode_string(msg);
	return msg;
}
void ham_server::start(void){
	ssize_t nread;
	string temp;
	int t;
	while(!ham_server::signal_stop){
		// Buffer size is 512
		temp=ham_server::get_msg()+"\r\n\r\n";
		t = temp.size()+1;
		if(t!=write(ham_server::sock,temp.c_str(),temp.size()+1)){
			cout<<"[ERROR] Failed to send message."<<endl;
			exit(EXIT_FAILURE);
		}
		nread = read(ham_server::sock,ham_server::buffer,BUFFERSIZE);
		if(-1==nread){
			cout<<"[ERROR] Client could not read response."<<endl;
			exit(EXIT_FAILURE);
		}
		// Decode with the hamming class
		temp=string(ham_server::buffer);
		cout<<"Message:\n"<<hamming::decode_message(temp)<<endl;
	}
	exit(EXIT_SUCCESS);
}	
//eof
