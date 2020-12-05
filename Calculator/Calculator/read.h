/**
 * @file
 * In diesem Modul wird der arithmetische Ausdruck von der Tastatur
 * eingelesen. Der Parser kann die Tokens des Ausdrucks nacheinander
 * anfordern. Die Tokens, d.h. Zahlen, Operatoren oder Klammern, werden
 * als Zeichenketten repräsentiert.
 *
 * @author  Ulrike Griefahn
 * @date    2019-11-07
 */

/* ------------------------------------------------------------------------ */
#ifndef _READ_H
#define _READ_H
/* ------------------------------------------------------------------------ */


/* ===========================================================================
 * Header-Dateien einbinden
 * ======================================================================== */

#include "calculator_common.h"


/* ===========================================================================
 * Symbolische Konstanten
 * ======================================================================== */

/**
 * Konstante für das Additionszeichen
 */
#define PLUS_OP      '+'

/**
 * Konstante für das Minuszeichen
 */
#define MINUS_OP     '-'

/**
 * Konstante für das Multiplikationszeichen
 */
#define TIMES_OP     '*'

/**
 * Konstante für das Divisionszeichen
 */
#define DIVIDE_OP    '/'

/**
 * Konstante für die öffnende Klammer
 */
#define L_BRACKET    '('

/**
 * Konstante für die schließende Klammer
 */
#define R_BRACKET    ')'

/**
 * Makro zur Überprüfung von Ziffern
 */
#define IS_DIGIT(CHAR)    (CHAR >= '0' && CHAR <= '9')

/**
 * Makro zur Überprüfung des Punkts
 */
#define IS_DOT(CHAR)      (CHAR == '.')

/**
 * Makro zur Überprüfung des Exponentszeichnes
 */
#define IS_EXPONENT(CHAR) (CHAR == 'e' || CHAR == 'E')


/* ===========================================================================
 * Externe Funktionen
 * ======================================================================== */

/**
 * Liest das nächste Token von der Standardeingabe und schreibt es in den
 * Parameter 'next_token'. Ein Token ist eine Zeichenkette, die eine
 * Ganzzahl, eine Gleitpunktzahl, einen Operator ("+", "-", "*", "/") oder
 * eine Klammer ("(", ")")) darstellt.
 *
 * @param next_token - Zeichenvektor, in dem das nächste Token geliefert wird.
 * @return TRUE, wenn ein Token gelesen werden konnte, und FALSE, wenn das Ende
 *          der Eingabe erreicht ist.
 */
extern BOOL get_next_token(char next_token[]);

/* ------------------------------------------------------------------------ */
#endif /* _READ_H */


