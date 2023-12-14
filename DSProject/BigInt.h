#pragma once
#include <iostream>


using namespace std;

class BigInt {
public:
	unsigned char number[20];
    int mod(int a)
    {
        // Initialize result
        int res = 0;

        // One by one process all digits of 'num'
        for (int i = 0; i < 20; i++)
            res = (res * 10 + number[i] - '0') % a;

        return res;
    }
};