#pragma once
#include<iostream>
#include "routing_table.h"
#include"BTree.h"
#include "generating_SHA.h"
#include "doublyLL.h"
using namespace std;

class machine
{
public:
	unsigned char name[255];
	unsigned char ID[20];
	BigInt real_ID;
	BTree nodeBTree;
	DoublyLinkedList<routing_table<machine>>* routablelist;
	routing_table<machine>* rt;
	machine(string nm, DoublyLinkedList<routing_table<machine>>* dll)
	{
		char t;
		string id;
		for (int i = 0; nm[i] != '\0'; i++)
			name[i] = nm[i];
		cout << "do you want to set the ID manually?y/n\n";
		cin >> t;
		if (t == 'y')
		{
			cin >> real_ID.digits;
			setId_SHA(real_ID.digits);
		}
		else
		{
			SHA1(name, strlen((char*)name), ID);
			int i;
			for (i = 0; i < 20; i++)
				int a = int(ID[i]);
			real_ID.digits[i] = '\0';
		}

		nodeBTree = NULL;
		rt = new routing_table<machine>{ 5 };
		dll->insert(*rt);
	}
	void setId_SHA(string nm)
	{
		int i;
		for (i = 0; nm[i] != '\0'; i++)
			ID[i] = nm[i];
	}
	~machine()
	{
	}

private:

};
