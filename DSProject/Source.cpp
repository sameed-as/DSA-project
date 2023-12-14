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
	BTree t(4);
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
	t.deletion(a);
	//t.deletion(8);
	//t.deletion(8);


	//cout << t.root->keys[3];


    cout << "The B-tree is: ";
    t.traverse_pelyvala();

	

	CircularLinkedList<int> cll;
	cll.insert(10);
	cll.insert(20);

	int expected[] = { 10, 20 };
	int result[2] = { 0 };

	int x = 0;
	Node<int>* current = cll.getHead();
	do {
		result[x++] = current->getData();
		current = current->getNext();
	} while (current != cll.getHead());

	sha_from_file("files/test.PNG");
	sha_from_file("files/out.txt");
	sha_from_file("files/2.JPG");

	BigInt first(1);
	BigInt second(1);
	cout << first + second;

	cout << "\nTEST FOR MACHINES:\n";
	DoublyLinkedList<routing_table<machine>> dll;
	CircularLinkedList<machine> DHT;

	machine m1("9", &dll, &DHT);
	machine m2("4", &dll, &DHT);
	machine m3("18", &dll, &DHT);
	machine m4("1", &dll, &DHT);
	machine m5("20", &dll, &DHT);
}
