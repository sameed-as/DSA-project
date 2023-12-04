#pragma once
#include<iostream>
using namespace std;
template <class T>
class DoublyNode
{
public:
	T data;
	DoublyNode<T>* prev, * next;
	DoublyNode()
	{
		prev = NULL;
		next = NULL;
	}
	DoublyNode(T data, DoublyNode<T>* prev, DoublyNode <T>* next)
	{
		this->data = data;
		this->next = next;
		this->prev = prev;
	}
	int getData()
	{
		return data;
	}
	DoublyNode<T>* getNext()
	{
		return next;
	}
	DoublyNode<T>* getPrev()
	{
		return prev;
	}
	void setData(int x)
	{
		data = x;
	}
	void setNext(DoublyNode<T>* n)
	{
		next = n;
	}
	void setPrev(DoublyNode<T>* p)
	{
		prev = p;
	}
};
template <class T>
class DoublyLinkedList
{
	DoublyNode <T>* head;
public:
	DoublyNode<T>* getHead()
	{
		return head;
	}
	DoublyLinkedList()
	{
		head = NULL;
	}
	bool isEmpty()
	{
		return (head == NULL);
	}
	void insertToHead(T x)
	{
		DoublyNode<T>* node = new DoublyNode(x, NULL, head);
		head = node;
	}
	void insert(T x)
	{
		DoublyNode* node = new DoublyNode(x, NULL, NULL);
		if (isEmpty())
		{
			head = node;
		}
		else
		{
			DoublyNode<T>* temp = head;
			while (temp->getNext() != NULL)
			{
				temp = temp->getNext();
			}
			temp->setNext(node);
			node->setPrev(temp);
		}
	}
	bool search(T x)
	{
		bool check = false;
		DoublyNode<T>* temp = head;
		while (temp != NULL)
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
		DoublyNode<T>* temp = head;
		while (temp != NULL)
		{
			if (temp->getData() == x)
			{
				temp->setData(replace);
				break;
			}
			temp = temp->getNext();
		}
	}
	void print()
	{
		DoublyNode<T>* temp = head;
		do
		{
			cout << temp->getData() << " ";
			temp = temp->getNext();
		} while (temp != NULL);
		cout << endl;
	}
	void insertAtIndex(T x, int place)
	{
		DoublyNode<T>* temp = head;
		int reach = 0;
		while (temp && reach != place)
		{
			temp = temp->getNext();
			reach++;
		}
		DoublyNode<T>* node = new DoublyNode(x, NULL, NULL);
		node->setNext(temp);
		node->setPrev(temp->getPrev());
		temp->getPrev()->setNext(node);
		temp->setPrev(node);
	}
	void deleteData(T x)
	{
		if (search(x))
		{
			DoublyNode<T>* temp = head;
			while (temp != NULL)
			{
				if (temp->getData() == x)
				{
					temp->getPrev()->setNext(temp->getNext());
					temp->getNext()->setPrev(temp->getPrev());
					delete temp;
					temp = NULL;
					break;
				}
				temp = temp->getNext();
			}
		}
	}
};
