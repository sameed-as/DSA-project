#pragma once
//includes to include sha 
#pragma comment(lib, "openssl/STATIC/x64/Debug/lib/libcrypto.lib")
#pragma comment(lib, "openssl/STATIC/x64/Debug/lib/libssl.lib")
#include "openssl/STATIC/x64/Debug/include/openssl/sha.h"
#include "openssl/STATIC/x64/Debug/include/openssl/macros.h"
#pragma comment (lib, "crypt32")
#pragma comment(lib, "ws2_32.lib")
#include <fstream>
#include <iostream>

using namespace std;

int sha_from_file(string s)
{
	ifstream f(s, fstream::binary);
	ofstream f1("files/in.txt", fstream::trunc | fstream::binary);
	unsigned char input[255] = { 0 }; // the max value sha1 can take is 255 digits long
	unsigned char output[20] = { 0 }; // the hash value has at max 20 digits
	int i = 0;
	char ch;
	while (f.get(ch) && i < 255)
	{
		
		input[i] = ch;
		i++;
	}
	for (int j = 0; j <= i; j++)
		cout << input[j];
	cout << " " << strlen((char*)input) << " " << i << endl;
	
	cout << "Hash for this" << endl;
	SHA1(input, i, output); // i is used as length of input string bcz strlen terminates calculation when \0 is encountered

	for (int j = 0; j < 20; j++)
		printf("%d", output[j]);
	cout << endl;

	f1 << f.rdbuf();
	f.close();
	f1.close();
	return 0;
	
}