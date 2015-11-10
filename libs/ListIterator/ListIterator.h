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

template<class T> class ListIterator {
public:
  ListIterator(Node<T>* begin):current(begin), first(begin){}
  virtual ~ListIterator(){}
/*
  bool hasNext(){
    return current->next == 0? false : true;
  }
*/
  bool isDone(){
	return current->next == 0 ? true : false;
  }

  Node<T>* firstNode(){
	  return first;
  }

  Node<T>* nextNode(){
    current = current->next;
    return current;
  }

  Node<T>* currentNode(){
	  return current;
  }

  void set_begin(Node<T>* begin){
    current = begin;
  }
/*
  T next(){
    Node<T>* temp = new Node<T>;
    temp = current->next;
    current = temp;
    return current->data;
  }

  Node<T>* next_node(){
    Node<T>* temp = new Node<T>;
    temp = current->next;
    current = temp;
    return current;
  }
*/
protected:
  Node<T>* current;
  Node<T>* first;
};



#endif /* LISTITERATOR_H_ */
