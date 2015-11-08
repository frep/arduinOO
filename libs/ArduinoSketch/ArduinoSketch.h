/*
 * ArduinoSketch.h
 *
 *  Created on: 08.11.2015
 *      Author: frehnerp
 */

#ifndef ARDUINOSKETCH_H_
#define ARDUINOSKETCH_H_

class ArduinoSketch
{

 public:

  virtual void setup() = 0;
  virtual void loop() = 0;
};


#endif /* ARDUINOSKETCH_H_ */
