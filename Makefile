FLG=-std=c++17 -v
LIB=-I/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/usr/include
LNK=
ALL:
	g++ ${FLG} ${LIB} src/ham_send.cpp -o bin/ham_send ${LNK}
clean:
	rm bin/ham_send
