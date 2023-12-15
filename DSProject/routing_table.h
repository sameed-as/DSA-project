#pragma once
#include <iostream>
#include "DoublyLL.h"
#include "BigInt.h"
#include <string>
#include <iomanip>

using namespace std;

template <class T>
class routing_table {
public:
	int idx;
	Node<T>** succ;
	BigInt* vals;
	int total_enteries;

	routing_table() {
		idx = 0;
		succ = nullptr;
		vals = nullptr;
		total_enteries = 0;
	}
	routing_table(unsigned long long num, BigInt id)
	{
		idx = 0;
		total_enteries = num;
		succ = new Node<T>* [num];
		vals = new BigInt[num];
		for (int i = 0; i < num; i++)
		{
			unsigned long long nr = pow(2, i);
			BigInt temp(nr);
			vals[i] = id + temp;
			cout << "val " << i + 1 << ": " << vals[i] << endl;
		}
		cout << endl;
	}

	void print()
	{
		cout << "____________________________________\n";
		cout << "|  index  |  value  |  Machine ID  |\n";
		for (int i = 0; i < total_enteries; i++)
		{
			cout << "____________________________________\n";
			cout << "|  " << setw(5) << i << "  |  " << vals[i] << "  |  " << succ[i]->data.real_ID << "  |\n";
		}
	}
};