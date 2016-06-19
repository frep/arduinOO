/*
 * Observable.h
 *
 *  Created on: 09.11.2015
 *      Author: frehnerp
 */

#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_


#include "arduino.h"

#include "Observer.h"
#include "LinkedList.h"
#include "ListIterator.h"

template <class T> class Observer;

template <class T> class Observable {
public:
  Observable(){}
  virtual ~Observable(){}

  void addObserver(Observer<T> &observer){
     m_observers.push_last(&observer);
   }

   void notifyObservers() {
     ListIterator<Observer<T> *> iterator;
     iterator.set_begin(m_observers.begin());
     while(!iterator.isDone()){
       Observer<T>* obs = iterator.nextNode()->data;
       obs->update(static_cast<T *>(this));
     }
   }

private:
  LinkedList<Observer<T> *> m_observers;
};


#endif /* OBSERVABLE_H_ */
