/* ===========================================================================
 * Header-Dateien
 * ======================================================================== */

#include <stdio.h>
#include "stack.h"


/* ===========================================================================
 * Symbolische Konstanten
 * ======================================================================== */

/**
 * Die maximale Größe des Stacks
 */
#define MAX_ELEMENTS 100


/* ===========================================================================
 * Globale Variablen
 * ======================================================================== */

/**
 * Stack zur Speicherung von Gleitpunktzahlen
 */
static double stack[MAX_ELEMENTS];

/**
 * Die nächste freie Stackposition
 */
static int stack_position = 0;


/* ===========================================================================
 * Funktionsdefinitionen (extern)
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Funktion: stack_init
 * ------------------------------------------------------------------------ */
extern void stack_init(void)
{
    int index;

    for (index = 0; index < MAX_ELEMENTS; index++)
    {
        stack[index] = 0.0;
    }
    stack_position = 0;
}

/* ---------------------------------------------------------------------------
 * Funktion: stack_push
 * ------------------------------------------------------------------------ */
extern void stack_push(double value)
{
    if (stack_position < MAX_ELEMENTS)
    {
        stack[stack_position] = value;
        stack_position += 1;
    }
    else
    {
        printf("error: stack is full.\n");
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: stack_pop
 * ------------------------------------------------------------------------ */
extern double stack_pop()
{
    double value;

    if (stack_position > 0)
    {
        stack_position -= 1;
        value = stack[stack_position];
    }
    else
    {
        printf("error: stack is full.\n");
        value = 0;
    }

    return value;
}
