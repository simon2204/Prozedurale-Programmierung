/**
 * @file
 * In diesem Modul wird der Stack verwaltet, der bei der Bewertung des
 * arithmetischen Ausdrucks zugrundeliegt.
 *
 * @author  Ulrike Griefahn
 * @date    2019-11-07
 */

#ifndef _STACK_H
#define _STACK_H


/* ===========================================================================
 * Externe Funktionen
 * ======================================================================== */

/**
 * Setzt den Stack zurück und entfernt ggf. vorhandene Elemente
 */
extern void stack_init(void);


/**
 * Legt eine Gleitpunktzahl auf den Stack.
 *
 * @param value - Die Gleitpunktzahl, die auf den Stack gelegt werden soll.
 */
extern void stack_push(double value);


/**
 * Entfernt eine Gleitpunktzahl vom Stack.
 *
 * Es wird davon ausgegangen, dass auf dem Stack mindestens ein Element
 * vorhanden ist.
 * 
 * @return Die vom Stack entfernte Gleitpunktzahl
 */
extern double stack_pop(void);

/* ------------------------------------------------------------------------- */
#endif  /* _STACK_H */
