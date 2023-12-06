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
	    BTree t(3);
    t.insert(8);
    t.insert(9);
    t.insert(10);
	cout<<t.root->C[0]->keys[0]<<" ";
	cout << t.root->C[1]->keys[0] << " ";
    t.insert(11);
    t.insert(15);
	t.insert(20);
	t.insert(17);


    cout << "The B-tree is: ";
    t.traverse();



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
