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
	t.insert(983);
	t.insert(8);
	t.insert(9);
	t.insert(10);
	t.insert(11);
	t.insert(15);
	t.insert(16);
	//cout << t.root->keys[1];
	t.insert(17);
	//cout << t.root->C[2]->keys[2];
	t.insert(18);
	//cout << t.root->C[3]->keys[1];
	t.insert(20);
	t.insert(23);
	t.insert(23);
	t.insert(23);
	t.insert(28);
	t.insert(51);
	t.insert(2);
	t.insert(3);
	t.insert(4);
	t.insert(5);
	t.insert(6);
	t.insert(7);
	t.insert(200);
	t.insert(501);
	t.insert(203);
	t.insert(53);
	t.insert(57);
	t.insert(55);
	t.insert(56);
	t.insert(57);
	t.insert(58);
	t.insert(59);
	t.insert(50);
	t.insert(51);
	t.insert(56);
	t.insert(57);
	t.insert(58);
	t.insert(54);
	t.insert(53);
	t.insert(55);
	t.insert(56);
	t.insert(53);
	t.insert(56);
	t.insert(52);
	t.insert(54);
	t.insert(51);


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

	

	return 0;
}
