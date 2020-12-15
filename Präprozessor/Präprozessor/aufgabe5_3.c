//
//  aufgabe5_3.c
//  Präprozessor
//
//  Created by Simon Schöpke on 10.12.20.
//

#include "aufgabe5_3.h"

#define NUM_TO_SQUARE 2 + 1

#define SQUARE(X) X * X

static int square(int x)
{
    return x * x;
}

extern void aufgabe5_3(void)
{
    printf("Soll: %d, Ist: %d\n",
           square(NUM_TO_SQUARE), SQUARE(NUM_TO_SQUARE));
}
