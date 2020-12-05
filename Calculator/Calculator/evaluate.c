/* ===========================================================================
 * Header-Dateien einbinden
 * ======================================================================== */

#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#include "evaluate.h"
#include "stack.h"
#include "parse.h"
#include "read.h"


/* ===========================================================================
 * Symbolische Konstanten
 * ======================================================================== */

/**
 * Fehlermeldung, wenn ein Operator erwartet, aber nicht erhalten wird
 */
#define MSG_OP_EXPECTED "error: operand or operator expected, but got: %s\n"

/**
 * Fehlermeldung bei Division durch 0
 */
#define MSG_DIV_0 "error: division by zero\n"


/* ===========================================================================
 * Funktionsprototypen (static)
 * ======================================================================== */

/**
 * Wandelt einen String in eine Gleitpunktzahl um.
 *
 * Es wird davon ausgegangen, dass der im String dargestellte
 * Gleitpunktwert korrekt ist und dass er den Bereich für double-Werte nicht
 * übersteigt.
 *
 * @param string - Zeichenkette, die umgewandelt werden soll
 * @return Der dargestelle Gleitpunktwert.
 */
static double convert_string_to_double(char string[]);


/* ===========================================================================
 * Funktionsdefinitionen
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Funktion: evaluate
 * ------------------------------------------------------------------------ */
extern double evaluate(void)
{
    /*
     * Die Token werden nacheinander vom Modul 'parse' geliefert, bis kein
     * Token mehr vorhanden ist. Ist das aktuelle Token eine Gleitpunktzahl,
     * wird diese auf dem Stack abgelegt. Ist das Token ein Operator, werden
     * die obersten beiden Zahlen vom Stack geholt und mit dem Operator
     * ausgewertet. Das Ergebnis der Auswertung wird oben auf dem Stack
     * abgelegt.
     * Gibt es keine weiteren Token, ist das einzige Stackelement das Ergebnis
     * des Gesamtausdrucks. */

    /* Zeichenkette mit dem jeweils aktuellen Token der Postfixdarstellung */
    char next_postfix_token[MAX_TOKEN_LENGTH];

    /* Operanden der binären arithmetischen Operationen */
    double operand1;
    double operand2;

    /* Stack leeren */
    stack_init();

    /* Lese nacheinander alle Token bis zum Ende */
    while (get_next_postfix_token(next_postfix_token))
    {
        if (IS_DIGIT(next_postfix_token[0]) || IS_DOT(next_postfix_token[0]))
        {
            /* String der Gleitpunktzahl in eine Gleitpunktzahl umwandeln */
            stack_push(convert_string_to_double(next_postfix_token));

        }
        else
        {
            /* Operator gefunden: werte die obersten Stackelemente gemäß des
             * Operators aus und lege das Ergebnis auf dem Stack ab */
            operand2 = stack_pop();
            operand1 = stack_pop();
            if (next_postfix_token[0] == PLUS_OP)
            {
                stack_push(operand1 + operand2);

            }
            else if (next_postfix_token[0] == MINUS_OP)
            {
                stack_push(operand1 - operand2);

            }
            else if (next_postfix_token[0] == TIMES_OP)
            {
                stack_push(operand1 * operand2);

            }
            else if (next_postfix_token[0] == DIVIDE_OP)
            {
                if (operand2 > DBL_EPSILON || -operand2 > DBL_EPSILON)
                {
                    stack_push(operand1 / operand2);

                }
                else
                {
                    printf(MSG_DIV_0);
                    return 0.0;
                }
            }
            else
            {
                printf(MSG_OP_EXPECTED, next_postfix_token);
            }
        }
    }

    /* Einziges Stackelement am Schluss ist Endergebnis */
    return stack_pop();
}

/* ---------------------------------------------------------------------------
 * Funktion: convert_string_to_double
 * ------------------------------------------------------------------------ */
static double convert_string_to_double(char string[])
{
    double number; /* Der zu berechnende Gleitpunktwert */
    double fractional; /* Faktor für Nachkommastellen */
    double exponent; /* Exponent */
    int index;

    number = 0;

    index = 0;
    /* Vorkommanteil berechnen */
    while (IS_DIGIT(string[index]))
    {
        number = (number * 10) + (string[index] - '0');
        index++;
    }

    /* Nachkommanteil berechnen, falls Punkt vorhanden */
    if (IS_DOT(string[index]))
    {
        index++;
        fractional = 1;
        while (IS_DIGIT(string[index]))
        {
            fractional *= 0.1;
            number = number + (fractional * (string[index] - '0'));
            index++;
        }
    }

    /* Exponent berechnen, falls 'e' oder 'E' vorhanden */
    if (IS_EXPONENT(string[index]))
    {
        index++;
        exponent = 0;
        while (IS_DIGIT(string[index]))
        {
            exponent = exponent * 10 + (string[index] - '0');
            index++;
        }
        while (exponent > 0)
        {
            number *= 10;
            exponent--;
        }
    }

    return number;
}
