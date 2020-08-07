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
		static string to_binary(char cc);
		static char to_char(string ss[8]);
		static char is_one(string ss);
		static char decode_character(string ss);
	public:
		static string encode_char(char cc);
		static string encode_string(string ss);
		static string decode_message(string ss);
};
#endif
