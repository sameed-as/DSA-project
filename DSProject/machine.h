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
	BTree* nodeBTree;
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

	machine(string nm, DoublyLinkedList<routing_table<machine>>* dll, CircularLinkedList<machine>* DHT, unsigned long long idspace)
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

		BigInt mod(idspace), two(2);
		power(two, mod);
		real_ID = real_ID % two; //seperating the last bits given by identifier space of user

		nodeBTree = new BTree(idspace);
		cout << "\nId of Machine: \n" << real_ID << endl;
		rt = new routing_table<machine>{ idspace , real_ID};
		DHT->insertmachine(*this);
		successor(DHT);
		dll->insert(*rt);
		routablelist = dll;
		updateroutinglist(DHT);
	}
	void setId_SHA(string nm)
	{
		int i;
		for (i = 0; nm[i] != '\0'; i++)
			ID[i] = nm[i];
	}

	void successor(CircularLinkedList<machine>* DHT)
	{

		cout << "\nId of Machine: \n" << real_ID << endl;
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
			cout << i << " node ID " << rt->succ[i]->data.real_ID << endl;
		}
	}

	void updateroutinglist(CircularLinkedList<machine>* DHT)
	{
		Node<machine>* curr = DHT->getHead();
		curr->data.successor(DHT);
		curr = curr->next;
		while (curr != DHT->getHead())
		{
			curr->data.successor(DHT);
			curr = curr->next;
		}
	}

	~machine()
	{
	}

private:

};
