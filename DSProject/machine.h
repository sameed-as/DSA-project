#pragma once
#include<iostream>
#include "routing_table.h"
#include"BTree.h"
#include "generating_SHA.h"
#include "doublyLL.h"
using namespace std;

class machine
{
	unsigned char name[255];
	unsigned char ID[20];
	BTree nodeBTree;
	DoublyLinkedList<routing_table<machine>>* routablelist;
	routing_table<machine>* rt;
public:
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
			cin >> id;
			setId_SHA(id);
		}
		else
			SHA1(name, strlen((char*)name), ID);

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
