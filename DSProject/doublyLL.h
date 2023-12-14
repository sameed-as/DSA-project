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
		size = 0;
	}
	DoublyNode(T data, DoublyNode<T>* prev, DoublyNode <T>* next)
	{
		this->data = data;
		this->next = next;
		this->prev = prev;
	}
	T getData()
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
	void setData(T x)
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
public:
	int size;
	DoublyNode <T>* head;
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
		DoublyNode<T>* node = new DoublyNode<T>(x, NULL, NULL);
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
		size++;
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
		int i = 0;
		do
		{
			cout <<i<<" " << temp->getData() << endl;
			temp = temp->getNext();
			i++;
		} while (temp != NULL);
		cout << endl;
	}
	void clear() {
		DoublyNode<T>* current = head;
		DoublyNode<T>* nextNode;

		while (current != nullptr) {
			nextNode = current->next;
			delete current;
			current = nextNode;
		}
		size = 0;
		head = nullptr;
	}
	DoublyLinkedList& operator=(const DoublyLinkedList& other) {
		if (this != &other) {
			clear();
			DoublyNode<T>* current = other.head;
			while (current != nullptr) {
				insert(current->data);
				current = current->next;
			}
		}
		return *this;
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

	void deleteData(int choice) {
		DoublyNode<T>* current = head;
		int i = 0;
		while (i < size) {
			if (i == choice) {
				if (current->getPrev()) {
					current->getPrev()->setNext(current->getNext());
				}
				else {
					head = current->getNext();
				}
				if (current->getNext()) {
					current->getNext()->setPrev(current->getPrev());
				}
				delete current;
				return;
			}
			current = current->getNext();
			i++;
		}
		size--;
	}
};
