/* ============================================================================
 * Header-Dateien 
 * ========================================================================= */

#include "compare.h"
#include <stdlib.h>
#include <float.h>


/* ============================================================================
 * Funktionsdefinitionen
 * ========================================================================= */

/* --------------------------------------------------------------------------
 * Funktion: numerical_strcmp
 * ------------------------------------------------------------------------ */
extern int numerical_strcmp(char *p_string1, char *p_string2)
{
    /* Wandelt beide Zeichenketten in Gleitpunktzahlen um und vergleicht die
     * Zahlen dann numerisch */

    double double1;
    double double2;

    double1 = atof(p_string1);
    double2 = atof(p_string2);

    if (double2 - double1 > DBL_EPSILON)
    {
        /* double1 < double2 */
        return -1;
    }
    else if (double1 - double2 > DBL_EPSILON)
    {
        /* double1 > double2 */
        return 1;
    }
    else
    {
        return 0;
    }
}

/* --------------------------------------------------------------------------
 * Funktion: chrcmp
 * ------------------------------------------------------------------------ */
extern int chrcmp(char *p_char1, char *p_char2)
{
    /* Vergleich der beiden Zeichen erfolgt direkt auf den Werten */

    if (*p_char1 < *p_char2)
    {
        return -1;
    }
    else if (*p_char1 > *p_char2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* --------------------------------------------------------------------------
 * Funktion: numcmp
 * ------------------------------------------------------------------------ */
extern int numcmp(int *p_int1, int *p_int2)
{
    /* Vergleich der beiden Zahlen erfolgt direkt auf den Werten */

    if (*p_int1 < *p_int2)
    {
        return -1;
    }
    else if (*p_int1 > *p_int2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
