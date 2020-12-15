//
//  main.c
//  Präprozessor
//
//  Created by Simon Schöpke on 10.12.20.
//

#include <stdio.h>
#include "aufgabe5_1.h"
#include "aufgabe5_2_a.h"
#include "aufgabe5_2_b.h"
#include "aufgabe5_3.h"

#define NEW_LINE printf("\n");

int main(int argc, const char * argv[]) {

    aufgabe5_1();
    NEW_LINE
    aufgabe5_2_a();
    NEW_LINE
    aufgabe5_2_b();
    NEW_LINE
    aufgabe5_3();
    
    return 0;
}


