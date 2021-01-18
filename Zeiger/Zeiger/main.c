//
//  main.c
//  Zeiger
//
//  Created by Simon Schöpke on 15.12.20.
//

#include <stdio.h>
#include <stdlib.h>

void xxx(void)
{
    char *lectures[] = {"SPIN", "TENI", "THI", "ADS", "SWT"};

    char *p;
    char **pp;

    p = lectures[1];
    pp = lectures;

    printf("1. %s\n", p);                 //1. Prints "TENI"

    printf("2. %s\n", p + 2);             //2. Prints "NI"

    printf("3. %s\n", *(pp + 2));         //3. Prints "THI"

    printf("4. %s\n", *pp + 2);           //4. Prints "IN"

    printf("5. %s\n", *(pp + 1) + 2);     //5. Prints "NI"

    printf("6. %s\n", *(lectures + 2));   //6. Prints "THI"

    printf("7. %s\n", (lectures[2] + 2)); //7. Prints "I"
}

char* irgendwas()
{
    char *helloWorld;
    
    helloWorld = "Hello, World!";

    return helloWorld;
}

int main(void)
{
    
//    xxx();

    
    return 0;
}
