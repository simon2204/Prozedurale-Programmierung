//
//  aufgabe5_2_b.c
//  Präprozessor
//
//  Created by Simon Schöpke on 10.12.20.
//

#include "aufgabe5_2_b.h"

static const int SIZE_OF_BYTE = 8;
static char phrase[] = "Hello, World!";
static const char FIRST_LETTER_OF_LATIN_ALPHABET = 'A';
static const int CORNFLOWER_BLUE = 6395373;

#define DPRINT(P) printf(#P " = %d\n", P);
#define SPRINT(P) printf(#P " = \"%s\"\n", P);
#define CPRINT(P) printf(#P " = '%c'\n", P);
#define XPRINT(P) printf(#P " = 0x%x\n", P);

extern void aufgabe5_2_b(void)
{
    printf("Aufgabe 5.2 b)\n");

    DPRINT(SIZE_OF_BYTE)
    SPRINT(phrase)
    CPRINT(FIRST_LETTER_OF_LATIN_ALPHABET)
    XPRINT(CORNFLOWER_BLUE)
}
