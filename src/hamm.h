//hamm.h is a src file for ham_send
//contains the header information for the hamm.cpp file
#ifndef HAMM_H
#define HAMM_H
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;
class hamming{
	private:
		string to_binary(char cc);
		char to_char(string ss[8]);
		char is_one(string ss);
		char get_char(string ss);
	public:
		string encode_char(char cc);
		string encode_string(string ss);
		string decode(string ss);
};
#endif
