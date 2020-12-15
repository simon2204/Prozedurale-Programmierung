//
//  aufgabe5_1.c
//  Präprozessor
//
//  Created by Simon Schöpke on 10.12.20.
//

#include "aufgabe5_1.h"

#define SWAP(A, B) typeof(A) temp = A; A = B; B = temp;

extern void aufgabe5_1(void)
{
    printf("Aufgabe 5.1\n");
    
    char a = 'a';
    char b = 'b';
    
    SWAP(a, b)
    
    printf("a = '%c'\nb = '%c'\n", a, b);
}
