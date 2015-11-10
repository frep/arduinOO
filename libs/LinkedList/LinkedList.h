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

template<class T> class LinkedList {
public:

  LinkedList():root(new Node<T>) {
    root->next = 0;
    root->previous = 0;
    _last = root;
    nodeCount = 1;
   }

   virtual ~LinkedList() {}

   //Method for Push some Data at the End of the list
   void push_last(T data) {
     Node<T>* temp = _last;
     _last = new Node<T>(0, data);
     temp->next = _last;
     _last->previous = temp;
     nodeCount++;
    }

   void remove_last(){
	 Node<T>* temp = _last;
	 _last = _last->previous;
	 _last->next = 0;
	 delete temp;
	 nodeCount--;
   }

   void remove_first(){
	   Node<T>* temp = root;
	   root = root->next;
	   root->previous = 0;
	   delete temp;
	   nodeCount--;
   }

   int get_list_size(){
	   return nodeCount;
   }

    void remove_index(int index){
    	if(index == (nodeCount - 1)){
    		remove_last();
    	}
    	else if(index == 0){
    		remove_first();
    	}
    	else if(index > 0 && index < (nodeCount - 1)){
    		int counter = 0;
            ListIterator<T>* riterator = new ListIterator<T>(root);
            Node<T>* temp = root;
            while(counter < index){
            	temp = riterator->nextNode();
            	counter++;
            }
            temp->previous->next = temp->next;
            temp->next->previous = temp->previous;
            delete temp;
            delete riterator;
            nodeCount--;
    	}
    	else{
    		// wrong index!
    	}
    }

  //Get the First Node;
  Node<T>* begin() {
    return root;
  }

  //Get the Last Node;
  Node<T>* last() {
    return _last;
  }

protected:
  Node<T>* root;
  Node<T>* _last;
  int nodeCount;
};

#endif /* LINKEDLIST_H_ */
