#include<iostream>
#include<queue>
#include "BTree.h"
#include "circularLinkedlist.h"
#include "routing_table.h"
#include "machine.h"
#include "doublyLL.h"
#include "bigInt.h"
#include <cmath>
#include "generating_SHA.h"
#include <graphviz/gvc.h>
#include<cstdio>

using namespace std;
int main(){
	//BigInt number(3), po(3);
	//power(number, po);
	//cout << number;
	/*BTree t(4);
	BigInt a(2);
	BigInt b(6);
	BigInt c(7);
	BigInt d(8);
	BigInt e(9);
	BigInt f(10);
	BigInt g(20);
	BigInt h(21);
	BigInt i(1);
	BigInt j(3);
	BigInt k(5);
	BigInt l(11);
	BigInt m(18);
	BigInt n(4);
	BigInt o(12);
	BigInt p(16);
	BigInt q(13);

	t.insert(a, "World2.1");
	t.insert(a, "World2.2");
	t.insert(a, "World2.3");
	t.insert(b, "World6");
	t.insert(c, "World7");
	t.insert(d, "World8");
	t.insert(e, "World9");
	t.insert(f, "World10");
	t.insert(g, "Worl20");
	t.insert(h, "Worl21");
	t.insert(i, "World1");
	t.deletion(d);
	t.insert(j, "World3");
	t.insert(k, "World5");
	t.insert(l, "World11");
	t.insert(m, "World18");
	t.insert(n, "World4");
	t.insert(o, "World12");
	t.insert(p, "World16");
	t.insert(q, "World13");
	t.deletion(a);
	t.deletion(a);*/
	//t.deletion(8);
	//t.deletion(8);


	//cout << t.root->keys[3];


    //cout << "The B-tree is: ";
    //t.traverse_pelyvala();

	

	/*CircularLinkedList<int> cll;
	cll.insert(10);
	cll.insert(20);

	int expected[] = { 10, 20 };
	int result[2] = { 0 };

	int x = 0;
	Node<int>* current = cll.getHead();
	do {
		result[x++] = current->getData();
		current = current->getNext();
	} while (current != cll.getHead());*/

	//BigInt first(1);
	//BigInt second(1);
	//cout << first + second;

	int identifierspace = 0;
	cout << "\nEnter your identifier space\n";
	cin >> identifierspace;

	cout << endl;
	cout << sha_from_file("files/test.PNG", identifierspace)<< endl;
	cout << sha_from_file("files/out.txt", identifierspace) << endl;
	cout << sha_from_file("files/2.JPG", identifierspace)   << endl;
	cout << sha_from_file("files/vid1.mkv", identifierspace)   << endl;
	cout << sha_from_file("files/vid2.mkv", identifierspace)   << endl;
	cout << sha_from_file("files/vid3.mkv", identifierspace)   << endl;
	cout << sha_from_file("files/vid4.mkv", identifierspace)   << endl;
	cout << sha_from_file("files/voice1.wav", identifierspace)   << endl;
	cout << sha_from_file("files/voice2.wav", identifierspace)   << endl;


	cout << "\nTEST FOR MACHINES:\n";
	DoublyLinkedList<routing_table<machine>> dll;
	CircularLinkedList<machine> DHT;

	int machinenum;
	cout << "\nEnter the number of machines u want\n";
	cin >> machinenum;

	string machinename = "";
	machine** machines = new machine * [machinenum];
	for (int i = 0; i < machinenum; i++)
	{
		cout << "\nEnter Name of machine\n";
		cin >> machinename;
		machines[i] = new machine(machinename, &dll, &DHT, identifierspace);
	}

	/*machine m1("9", &dll, &DHT, identifierspace);
	machine m2("4", &dll, &DHT, identifierspace);
	machine m3("18", &dll, &DHT, identifierspace);
	machine m4("1", &dll, &DHT, identifierspace);
	machine m5("20", &dll, &DHT, identifierspace);
	m5.print();*/
	DHT.printallrt();
	DHT.print_machine();
}
