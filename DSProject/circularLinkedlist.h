#pragma once
#include<iostream>
using namespace std;
template <class T>
class Node
{
public:
	T data;
	Node<T>* next;
	int getData()
	{
		return data;
	}
	Node<T>* getNext()
	{
		return next;
	}
	void setData(T x)
	{
		data = x;
	}
	void setNext(Node<T>* n)
	{
		next = n;
	}
	Node()
	{
		next = NULL;
		data = -1;
	}
	Node(T data, Node<T>* next)
	{
		this->data = data;
		this->next = next;
	}
};
template<class T>
class CircularLinkedList
{
	Node<T>* head;
public:
	Node<T>* getHead()
	{
		return head;
	}
	CircularLinkedList()
	{
		head = NULL;
	}
	bool isEmpty()
	{
		return (head == NULL);
	}
	void insert(T x)
	{
		Node<T>* node = new Node<T>(x, NULL);
		if (isEmpty())
		{
			head = node;
			head->setNext(head);
		}
		else
		{
			Node<T>* temp = head;
			while (temp->getNext() != head)
			{
				temp = temp->getNext();
			}
			temp->setNext(node);
			node->setNext(head);
		}
	}
	bool search(T x)
	{
		bool check = false;
		Node<T>* temp = head;
		while (temp->getNext() != head)
		{
			if (temp->getData() == x)
			{
				check = true;
				break;
			}
			temp = temp->getNext();
		}
		return check;
	}
	void update(T x, T replace)
	{
		Node<T>* temp = head;
		while (temp->getNext() != head)
		{
			if (temp->getData() == x)
			{
				temp->setData(replace);
				break;
			}
			temp = temp->getNext();
		}
	}
	void insertAtIndex(T x, int place)
	{
		Node<T>* temp = head;
		Node<T>* prev = head;
		int reach = 0;
		while (temp->getNext() != head && reach != place)
		{
			prev = temp;
			temp = temp->getNext();
			reach++;
		}
		Node<T>* node = new Node(x, NULL);
		prev->setNext(node);
		node->setNext(temp);
	}
	void deleteData(int x)
	{
		if (search(x))
		{
			Node<T>* temp = head;
			Node<T>* prev = NULL;
			while (temp->getNext() != head)
			{
				if (temp->getData() == x)
				{
					prev->setNext(temp->getNext());
					delete temp;
					temp = NULL;
					break;
				}
				prev = temp;
				temp = temp->getNext();
			}
		}
	}
	void print()
	{
		Node<T>* temp = head;
		do
		{
			cout << temp->getData() << " ";
			temp = temp->getNext();
		} while (temp != head);
		cout << endl;
	}
};

