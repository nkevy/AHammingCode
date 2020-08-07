//hamm.cpp is a src file for ham_send
//contains classes for the hamming code error correction
#include "hamm.h"
//convert a character ASCII to binary
string hamming::to_binary(char cc){
	return bitset<8>(cc).to_string();
}
//convert a binary string of length eight to a ASCII char
char hamming::to_char(string ss[8]){
	//return static_cast<char>(stoi(ss[0],nullptr,2)+64);
	return static_cast<char>(stoi(ss[0],nullptr,2));
}
//for parity bits
char hamming::is_one(string ss){
	for(int i=0;i<ss.size();i++){
		if('0'==ss[i]){
			return '0';
		}
	}
	return '1';
}
// encode char with hamming code alg
// note: characters have a fixed length
// parity bits are 1 if all checked bits are 1
string hamming::encode_char(char cc){
	string before = hamming::to_binary(cc);
	string after = "000000000000"; 
	//parity 
	string p1,p2,p3,p4;
	p1+
		before[0]+
		before[1]+
		before[3]+
		before[4]+
		before[6];
	p2+
		before[0]+
		before[2]+
		before[3]+
		before[5]+
		before[6];
	p3+
		before[1]+
		before[2]+
		before[3]+
		before[7];
	p4+
		before[4]+
		before[5]+
		before[6]+
		before[7];
	//hamming code
	after[0] = hamming::is_one(p1);
	after[1] = hamming::is_one(p2);
	after[2] = before[0];
	after[3] = hamming::is_one(p3);
	after[4] = before[1];
	after[5] = before[2];
	after[6] = before[3];
	after[7] = hamming::is_one(p4);
	after[8] = before[4];
	after[9] = before[5];
	after[10] = before[6];
	after[11] = before[7];
	return after;
}
string hamming::encode_string(string ss){
	string after;
	for(int i=0;i<ss.size();i++){
		after=after+hamming::encode_char(ss[i]);
	}
	return after;
}
//error correction for hamming code
char hamming::decode_character(string ss){
	char p1,p2,p3,p4;
	string c1,c2,c3,c4;
	bool b1,b2,b3,b4;
	string before=ss;
	string after[8];
	p1 = ss[0];
	c1 = 
		before[2]+
		before[4]+
		before[6]+
		before[8]+
		before[11];
	// bool here represents the check of a parity bit   
	b1=(p1==hamming::is_one(c1));
	p2=ss[1];
	c2 = 
		before[2]+
		before[5]+
		before[6]+
		before[9]+
		before[10];
	b2=p1==hamming::is_one(c2);
	p3=ss[3];
	c3 = 
		before[4]+
		before[5]+
		before[8]+
		before[11];
	b3=p3==hamming::is_one(c3);
	p4=ss[7];
	c4 = 
		before[8]+
		before[9]+
		before[10]+
		before[11];
	b4=p4==hamming::is_one(c4);
	//error correction step
	// note: here we must make a decision about the accuracy of 
	// the error correction. If there is only one error then 
	// the decode_character function will operate well.
	// If there are multiple errors the function may work
	// but there is no grantee. With only a single message
	// as a sample we cannot make generalizations. Errors 
	// may occur but, that is ok. Other protocols types
	// such as congestion control and handshakes could be
	// used to resend potentially problematic data.   
	if(!(b1&&b2)&b3){
		after[0] = (before[2]=='1')?'0':'1';
	}
	if(!(b1&&b3)&b2){
		after[1] = (before[4]=='1')?'0':'1';
	}
	if(!(b2&&b3)&b1){
		after[2] = (before[5]=='1')?'0':'1';
	}
	if(!(b1&&b2&&b3)){
		after[3] = (before[6]=='1')?'0':'1';
	}
	if(!(b1&&b4)&b2){
		after[4] = (before[8]=='1')?'0':'1';
	}
	if(!(b2&&b4)&b1){
		after[5] = (before[9]=='1')?'0':'1';
	}
	if(!(b1&&b2&&b4)){
		after[6] = (before[10]=='1')?'0':'1';
	}
	if(!(b3&&b4)){
		after[7] = (before[11]=='1')?'0':'1';
	}
	return hamming::to_char(after);
}
//decode a binary string assuming hamming code is present
string hamming::decode_message(string ss){
	//split into 12 bit chars
	vector<string> ham_char_list;
	int j=0;
	for(int i=0;i<ss.size();i++){
		if(!i%12){
			ham_char_list.push_back(ss.substr(j,12));
			j=i+1;
		}
	}
	//error correction and concatenation
	char cc;
	string msg;
	for(int i=0;i<ham_char_list.size();i++){
		cc = hamming::decode_character(ham_char_list[i]);
		msg = msg + cc;
	}
	// return corrected message
	return msg;
}
