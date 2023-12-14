#pragma once
#include<iostream>
#include "routing_table.h"
#include"BTree.h"
#include "generating_SHA.h"
#include "doublyLL.h"
#include <string>

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

	machine()
	{
		for (int i = 0; i < 255; i++)
			name[i] = 0;
		for (int i = 0; i < 20; i++)
			ID[i] = 0;
		nodeBTree = NULL;
		routablelist = nullptr;
		rt = nullptr;
	}

	machine(string nm, DoublyLinkedList<routing_table<machine>>* dll, CircularLinkedList<machine>* DHT)
	{
		char t;
		for (int i = 0; nm[i] != '\0'; i++)
			name[i] = nm[i];
		cout << "\ndo you want to set the ID manually?y/n\n";
		cin >> t;
		if (t == 'y')
		{
			string id = "";
			cout << "Enter the id:\n";
			cin >> id;
			BigInt temp(id);
			real_ID = temp;
			//setId_SHA(real_ID.digits);
		}
		else
		{
			string id = "";
			SHA1(name, strlen((char*)name), ID);
			int i;
			
			for (i = 0; i < 20; i++)
			{
				int n = int(ID[i]);
				id += to_string(n);
			}
			BigInt temp(id);
			real_ID = temp;
		}

		nodeBTree = NULL;
		cout << "\nId of Machine: \n" << real_ID << endl;
		rt = new routing_table<machine>{ 5 , real_ID};
		DHT->insertmachine(*this);
		successor(DHT);
		dll->insert(*rt);
		routablelist = dll;
	}
	void setId_SHA(string nm)
	{
		int i;
		for (i = 0; nm[i] != '\0'; i++)
			ID[i] = nm[i];
	}

	void successor(CircularLinkedList<machine>* DHT)
	{
		Node<machine>* temp = DHT->getHead();
		machine dummy;
		for (int i = 0; i < rt->total_enteries; i++)
		{
			temp = DHT->getHead();
			if (rt->vals[i] > DHT->maximumval(dummy))
				rt->succ[i] = temp;
			else
			{
				if(rt->vals[i] <= temp->data.real_ID)
				{
					rt->succ[i] = temp;
				}
				else
				{
					while (rt->vals[i] > temp->next->data.real_ID)
					{
						temp = temp->next;
					}
					rt->succ[i] = temp->next;
				}
			}
			cout << rt->succ[i]->data.real_ID << endl;
		}
	}

	~machine()
	{
	}

private:

};
