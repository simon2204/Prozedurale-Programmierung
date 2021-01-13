/**
 * @file
 * Dieses Modul stellt Vergleichsfunktionen zur Verf�gung. Alle Funktionen
 * erwarten die beiden zu vergleichenden Werte �ber Zeiger und liefern
 *     -1, wenn der erste Wert kleiner ist als der zweite
 *      1, wenn der erste Wert gr��er ist als der zweite
 *      0, wenn beide Werte gleich sind.
 *
 * @author  Ulrike Griefahn
 * @date    2015-12-04
 */

/* ------------------------------------------------------------------------- */
#ifndef _COMPARE_H
#define	_COMPARE_H
/* ------------------------------------------------------------------------- */

/* ============================================================================
 * Headaer-Dateien 
 * ========================================================================= */

/* string.h einf�gen, damit strcmp zur Verf�gung steht und exportiert wird */
#include <string.h>


/* ============================================================================
 * Funktionsprototypen
 * ========================================================================= */

/**
 * Nummerischer Vergleich zweier Zeichenketten
 * 
 * @param p_string1 - erste Zeichenkette
 * @param p_string2 - zweite Zeichenkette
 * @return <ul>
 *         <li> -1, wenn die erste Zeichenkette kleiner ist als die zweite
 *         <li>  1, wenn die erste Zeichenkette gr��er ist als die zweite
 *         <li>  0, wenn beide Zeichenketten gleich sind.
 *         </ul>
 */
extern int numerical_strcmp(char *p_string1, char *p_string2);

/**
 * Vergleich zweier Zeichen
 *
 * @param p_char1 - erstes Zeichen
 * @param p_char2 - zweites Zeichen
 * @return <ul>
 *         <li> -1, wenn das erste Zeichen kleiner ist als das zweite
 *         <li>  1, wenn die erste Zeichen gr��er ist als das zweite
 *         <li>  0, wenn beide Zeichen gleich sind.
 *        </ul>
 */
extern int chrcmp(char *p_char1, char *p_char2);

/**
 * Vergleich zweier Zahlen
 * @param p_int1 : erste Zahl
 * @param p_int2 : zweite Zahl
 * @return <ul>
 *         <li> -1, wenn die erste Zahl kleiner ist als die zweite
 *         <li>  1, wenn die erste Zahl gr��er ist als die zweite
 *         <li>  0, wenn beide Zahlen gleich sind.
 *         </ul>
 */
extern int numcmp(int *p_int1, int *p_int2);

/* ------------------------------------------------------------------------ */
#endif	/* _COMPARE_H */

