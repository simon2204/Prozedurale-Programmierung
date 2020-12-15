//
//  aufgabe5_2_a.c
//  Präprozessor
//
//  Created by Simon Schöpke on 10.12.20.
//

#include "aufgabe5_2_a.h"

static const char SINN_DES_LEBENS = 42;

//#undef DEBUG

#ifdef DEBUG
#define DPRINT(P) printf(#P " = %d\n", P);
#endif

extern void aufgabe5_2_a(void)
{
    printf("Aufgabe 5.2 a)\n");
    
#ifdef DEBUG
    DPRINT(SINN_DES_LEBENS)
#endif
}
