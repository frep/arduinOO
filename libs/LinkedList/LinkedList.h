/*
 * LinkedList.h
 *
 *  Created on: 09.11.2015
 *      Author: frehnerp
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "arduino.h"
#include "Node.h"
#include "ListIterator.h"

template<class T> class LinkedList
{
public:

	LinkedList()
	{
		first = 0;
		last = 0;
		nodeCount = 0;
	}

	virtual ~LinkedList()
	{
		Node<T>* temp = first;
		while(temp != 0)
		{
			temp = temp->next;
			delete(first);
			first = temp;
		}
	}

	bool isEmpty()
	{
		if(last == 0)
		{
			return true;
		}
		return false;
	}

	int size()
	{
		return nodeCount;
	}

	void insertAtBack(T valueToInsert)
	{
		Node<T>* newNode = new Node<T>(valueToInsert);
		if(isEmpty())
		{
			first = newNode;
			last = newNode;
		}
		else
		{
			last->next = newNode;
			newNode->previous = last;
			last = newNode;
		}
		nodeCount++;
		Serial.print(" added Node Nr: ");
		Serial.println(nodeCount);
	}

	bool removeFromBack()
	{
		if(isEmpty())
		{
			return false;
		}
		else
		{
			Node<T>* temp = last;
			last = last->previous;
			last->next = 0;
			delete(temp);
			return true;
		}
	}

	bool remove(T valueToRemove)
	{
		ListIterator<T>* riterator = new ListIterator<T>(first);
		while(true)
		{
			if(riterator->currentData() == valueToRemove)
			{
				// node found -> remove it!
				if(riterator->currentNode() == first)
				{
					remove_first();
				}
				else if(riterator->currentNode() == last)
				{
					remove_last();
				}
				else
				{
					Node<T>* temp = riterator->currentNode();
					temp->previous->next = temp->next;
					temp->next->previous = temp->previous;
					delete temp;
				}
				delete riterator;
				nodeCount--;
				return true;
			}

			if(riterator->isDone())
			{
				// no node found -> exit
				return false;
			}
			else
			{
				riterator->nextNode();
			}
		}
	}

	void remove_last()
	{
		Node<T>* temp = last;
		last = last->previous;
		last->next = 0;
		delete temp;
		nodeCount--;
	}

	void remove_first()
	{
		Node<T>* temp = first;
		first = first->next;
		first->previous = 0;
		delete temp;
		nodeCount--;
	}

	Node<T>* firstNode()
	{
		return first;
	}

	Node<T>* lastNode()
	{
		return last;
	}

protected:
    Node<T>* first;
    Node<T>* last;
    int nodeCount;
};

#endif /* LINKEDLIST_H_ */
