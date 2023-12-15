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
#include "BigInt.h"

using namespace std;

BigInt sha_from_file(string s, unsigned long long idspace)
{
	ifstream f(s, fstream::binary);
	ofstream f1("files/in.txt", fstream::trunc | fstream::binary);
	unsigned char input[255] = { 0 }; // the max value sha1 can take is 255 digits long
	unsigned char output[21] = { 0 }; // the hash value has at max 20 digits
	int i = 0;
	char ch;
	while (f.get(ch) && i < 255)
	{
		
		input[i] = ch;
		i++;
	}
	/*for (int j = 0; j <= i; j++)
		cout << input[j];
	cout << " " << strlen((char*)input) << " " << i << endl;
	*/
	cout << "\nHash for this" << endl;
	SHA1(input, i, output); // i is used as length of input string bcz strlen terminates calculation when \0 is encountered

	for (int j = 0; j < 20; j++)
		printf("%02x", output[j]);
	cout << endl;

	string id = "";
	int k;
	for (k = 0; k < 20; k++)
	{
		int n = int(output[i]);
		id += to_string(n);
	}
	BigInt ID_BigInt(id);
	BigInt po(idspace), mod(2);
	power(mod, po);
	ID_BigInt = ID_BigInt % mod;

	f1 << f.rdbuf();
	f.close();
	f1.close();
	return ID_BigInt;
	
}