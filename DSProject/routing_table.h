#pragma once
#include <iostream>
#include "DoublyLL.h"

using namespace std;

template <class T>
class routing_table {
public:
	int idx;
	Node<T>** succ;
	int* vals;
	int total_enteries;
	routing_table() {
		idx = 0;
		succ = nullptr;
		vals = nullptr;
		total_enteries = 0;
	}
	routing_table(int num, int id = 5)
	{
		idx = 0;
		total_enteries = num;
		succ = new Node<T>* [num];
		vals = new int[num];
		for (int i = 0; i < num; i++)
			vals[i] = id + pow(2, i - 1);
	}
};