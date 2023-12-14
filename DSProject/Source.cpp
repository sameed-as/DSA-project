#include<iostream>
#include<queue>
#include "BTree.h"
#include "circularLinkedlist.h"
#include "routing_table.h"
#include "doublyLL.h"
#include "bigInt.h"
#include <cmath>
#include "generating_SHA.h"
#include <graphviz/gvc.h>
#include<cstdio>

using namespace std;
int main(){
	BTree t(3);
	t.insert(2, "World2.1");
	t.insert(2, "World2.2");
	t.insert(6, "World6");
	t.insert(7, "World7");
	t.insert(8, "World8");
	t.insert(9, "World9");
	t.insert(10, "World10");
	t.insert(20, "Worl20");
	t.insert(21, "Worl21");
	t.insert(1, "World1");
	t.deletion(8);
	t.insert(3, "World3");
	t.insert(5, "World5");
	t.insert(11, "World11");
	t.insert(18, "World18");
	t.insert(4, "World4");
	t.insert(12, "World12");
	t.insert(16, "World16");
	t.insert(13, "World13");
	t.deletion(2);
	t.deletion(8);


	//cout << t.root->keys[3];


    cout << "The B-tree is: ";
    t.traverse_pelyvala();



	CircularLinkedList<int> cll;
	cll.insert(10);
	cll.insert(20);

	int expected[] = { 10, 20 };
	int result[2] = { 0 };

	int i = 0;
	Node<int>* current = cll.getHead();
	do {
		result[i++] = current->getData();
		current = current->getNext();
	} while (current != cll.getHead());

	sha_from_file("files/test.PNG");
	sha_from_file("files/out.txt");
	sha_from_file("files/2.JPG");

	BigInt first("12345678");
	cout << first.mod(100);
}
