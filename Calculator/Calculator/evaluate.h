/**
 * @file
 * In diesem Modul wird der durch das Modul parse.h erzeugte
 * Postfix-Ausdruck ausgewertet.
 *
 * @author  Ulrike Griefahn
 * @date    2019-11-07
 */

/* ------------------------------------------------------------------------ */
#ifndef _EVALUATE_H
#define _EVALUATE_H
/* ------------------------------------------------------------------------ */

/* ===========================================================================
 * Funktionsprototypen
 * ======================================================================== */

/**
 * Wertet einen Ausdruck in Postfix-Notation aus.
 * Der auszuwertende Ausdruck liegt in Postfix-Notation vor. Die Tokens werden
 * nacheinander vom Modul 'parse' geliefert. Jedes Element des Vektors ist eine
 * Zeichenkette, die entweder einen Operanden (Ganzzahl oder Gleitkommazahl)
 * oder einen der Operatoren "+", "-", "*" oder "/" enthält.
 *
 * @return Der Gleitpunktwert des Ausdrucks.
 */
extern double evaluate(void);

/* ------------------------------------------------------------------------ */
#endif /* _EVALUATE_H */
