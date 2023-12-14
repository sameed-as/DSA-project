#include<iostream>
#include<queue>
#include "BTree.h"
#include "circularLinkedlist.h"
#include "finger Table.h"
#include "doublyLL.h"
//#include "bigInt"
#include <cmath>
#include "generating_SHA.h"
#include <graphviz/gvc.h>
#include<cstdio>

using namespace std;
int main(){
	BTree t(3);
	/*t.insert(983);
	t.insert(8);
	t.insert(9);
	t.insert(10);
	t.insert(11);
	t.insert(30);
	t.insert(31);
	t.insert(32);
	t.insert(33);
	t.insert(34);
	t.insert(35);
	t.insert(36);
	t.insert(38);
	t.insert(15);
	t.insert(16);
	t.insert(17);
	t.insert(18);
	t.insert(20);
	t.insert(23);
	t.insert(24);
	t.insert(25);
	t.insert(28);
	t.insert(51);
	t.insert(2);
	t.insert(3);
	t.insert(4);
	t.insert(5);
	t.insert(6);
	t.insert(39);
	t.insert(40);
	t.insert(41);
	t.insert(42);
	t.insert(43);
	t.insert(44);
	t.insert(45);
	t.insert(46);
	t.insert(47);
	t.insert(48);

	
	
	
	
	t.deletion(983);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(8);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(9);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(10);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(11);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(30);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(31);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(32);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(33);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(34);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(35);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(36);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(38);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(15);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(16);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(17);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(18);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(20);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(23);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(24);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(25);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(28);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(51);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(2);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(3);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(4);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(5);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(6);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(39);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(40);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(41);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(42);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(43);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(44);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(45);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(46);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(47);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();
	t.deletion(48);
	cout <<endl<< "The Btree is : ";
	t.traverse_pelyvala();*/

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

	
}
