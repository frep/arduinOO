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

	LinkedList():_root(new Node<T>)
	{
		_root->next = 0;
		_root->previous = 0;
		_last = _root;
		nodeCount = 1;
	}

	virtual ~LinkedList() {}

	//Method for Push some Data at the End of the list
	void push_last(T data)
	{
	   Node<T>* temp = _last;
	   _last = new Node<T>(0, data);
	   temp->next = _last;
	   _last->previous = temp;
	   nodeCount++;
	}

	bool remove_data(T data)
	{
		ListIterator<T>* riterator = new ListIterator<T>(_root);
		while(true)
		{
			if(riterator->currentNode()->data == data)
			{
				// node found -> remove it!
				if(riterator->currentNode() == _root)
				{
					remove_first();
				}
				else if(riterator->currentNode() == _last)
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
		Node<T>* temp = _last;
		_last = _last->previous;
		_last->next = 0;
		delete temp;
		nodeCount--;
	}

	void remove_first()
	{
		Node<T>* temp = _root;
		_root = _root->next;
		_root->previous = 0;
		delete temp;
		nodeCount--;
	}

	int get_list_size()
	{
		return nodeCount;
	}

    //Get the First Node;
    Node<T>* begin()
	{
    	return _root;
	}

    //Get the Last Node;
    Node<T>* last()
    {
    	return _last;
    }

protected:
    Node<T>* _root;
    Node<T>* _last;
    int nodeCount;
};

#endif /* LINKEDLIST_H_ */
