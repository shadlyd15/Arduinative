/* -*- mode: jde; c-basic-offset: 2; indent-tabs-mode: nil -*- */

/*
  Part of the Wiring project - http://wiring.uniandes.edu.co

  Copyright (c) 2004-05 Hernando Barragan

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
  
  Modified 24 November 2006 by David A. Mellis
  Modified 1 August 2010 by Mark Sproul
*/

#include <inttypes.h>
#include <stdio.h>

#include "wiring_private.h"

static void nothing(void) {

}

static volatile voidFuncPtr intFunc[EXTERNAL_NUM_INTERRUPTS] = {
#if EXTERNAL_NUM_INTERRUPTS > 8
    #warning There are more than 8 external interrupts. Some callbacks may not be initialized.
    nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 7
    nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 6
    nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 5
    nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 4
    nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 3
    nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 2
    nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 1
    nothing,
#endif
#if EXTERNAL_NUM_INTERRUPTS > 0
    nothing,
#endif
};
// volatile static voidFuncPtr twiIntFunc;

void attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode) {

}

void detachInterrupt(uint8_t interruptNum) {

}

/*
void attachInterruptTwi(void (*userFunc)(void) ) {
  twiIntFunc = userFunc;
}
*/

#define IMPLEMENT_ISR(vect, interrupt)

// #endif

/*
ISR(TWI_vect) {
  if(twiIntFunc)
    twiIntFunc();
}
*/

