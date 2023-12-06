#include<iostream>
#include<queue>
#include "BTree.h"
#include "circularLinkedlist.h"
#include "finger Table.h"
#include "doublyLL.h"
//#include "bigInt"
#include <cmath>

using namespace std;
int main(){
	cout << "Hello world" << endl;
	BTree<int> b(3);
	b.insert(1);
	b.insert(2);
	b.insert(3);
	b.insert(4);
	b.insert(5);
	b.insert(6);
	b.insert(7);
	b.insert(8);
	b.insert(9);
	b.insert(10);
	b.insert(11);


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

	

	return 0;
}
