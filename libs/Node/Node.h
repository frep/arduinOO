/*
 * Node.h
 *
 *  Created on: 09.11.2015
 *      Author: frehnerp
 */

#ifndef NODE_H_
#define NODE_H_

#include "Arduino.h"

template<class T> class Node
{
public:
	Node(Node <T>* _next, T _data): next(_next), previous(0), data(_data){};
	Node(Node <T>* _next, Node <T>* _previous, T _data): next(_next), previous(_previous), data(_data){};
	Node(T _data): next(0), previous(0), data(_data){};
	virtual ~Node(){};
	Node<T>* next;
	Node<T>* previous;
	T data;
};


#endif /* NODE_H_ */
