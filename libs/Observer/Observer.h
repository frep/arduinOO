/*
 * Observer.h
 *
 *  Created on: 09.11.2015
 *      Author: frehnerp
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

#include "arduino.h"
#include "Observable.h"

template <class T> class Observable;

template <class T>class Observer {
public:
  Observer() {}
  virtual ~Observer() {}
  virtual void update(T *observable) = 0;
};

#endif /* OBSERVER_H_ */
