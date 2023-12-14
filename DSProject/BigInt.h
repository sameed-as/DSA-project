#pragma once
#include <iostream>


using namespace std;

class BigInt {
public:
	unsigned char number[20] = {0};

    BigInt(string integer)
    {
        for (int i = 0; integer[i] != '\0'; i++)
            number[i] = integer[i];
    }

    int mod(int a)
    {
        // Initialize result
        int res = 0;

        // One by one process all digits of 'num'
        for (int i = 0; number[i] != '\0'; i++)
            res = (res * 10 + number[i] - '0') % a;

        return res;
    }

};