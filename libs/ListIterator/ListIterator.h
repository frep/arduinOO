/*
 * ListIterator.h
 *
 *  Created on: 09.11.2015
 *      Author: frehnerp
 */

#ifndef LISTITERATOR_H_
#define LISTITERATOR_H_

#include "arduino.h"
#include "Node.h"

template<class T> class ListIterator
{
public:
	ListIterator():_current(0), _first(0){}
	ListIterator(Node<T>* begin):_current(begin), _first(begin){}
	virtual ~ListIterator(){}

	bool hasNext()
	{
		return _current->next == 0? false : true;
	}

	bool isDone()
	{
		return _current->next == 0 ? true : false;
	}

	Node<T>* firstNode()
	{
		return _first;
	}

	Node<T>* nextNode()
	{
		_current = _current->next;
		return _current;
	}

	Node<T>* currentNode()
	{
		return _current;
	}

	void set_begin(Node<T>* begin)
	{
		_current = begin;
	}

protected:
	Node<T>* _current;
	Node<T>* _first;
};



#endif /* LISTITERATOR_H_ */
