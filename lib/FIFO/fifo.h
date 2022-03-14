/*
 * FIFO Buffer
 * Implementation uses arrays to conserve memory
 * 
 * The MIT License (MIT)
 * 
 * Copyright (c) 2015 Daniel Eisterhold
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
 
#ifndef __FIFO__
#define __FIFO__

#include "Arduino.h"

//#define FIFO_SIZE 64

template <class T=uint8_t, uint8_t N=32>
class FIFO {
  private:
    volatile int head;
    volatile int tail;
    volatile int numElements;
    volatile T buffer[N];
  public:
    FIFO();
    ~FIFO();
    void push(T data) volatile;
    T pop() volatile;
    int size() volatile;
};

template <class T, uint8_t N>
FIFO<T,N>::FIFO() {
  head = 0;
  tail = 0;
  numElements = 0;
}

template <class T, uint8_t N>
FIFO<T,N>::~FIFO() {
}

template <class T, uint8_t N>
void FIFO<T,N>::push(T data) volatile {
  if(numElements == N) {
//    Serial.println(F("Buffer full"));
    return;
  }
  else {
    //Increment size
    numElements++;

    //Only move the tail if there is more than one element
    if(numElements > 1) {
      //Increment tail location
      tail++;

      //Make sure tail is within the bounds of the array
      tail %= N;
    }
  
    //Store data into array
    buffer[tail] = data;
  }
}

template <class T, uint8_t N>
T FIFO<T,N>::pop() volatile {
  if(numElements == 0) {
//    Serial.println(F("Buffer empty"));
    return NULL;
  }
  else {
    //Decrement size
    numElements--;

    T data = buffer[head];

    if(numElements >= 1) {
      //Move head up one position
      head++;

      //Make sure head is within the bounds of the array
      head %= N;
    }

    return data;
  }
}

template <class T, uint8_t N>
int FIFO<T,N>::size() volatile {
  return numElements;
}



#endif