/**
 * @file
 * In diesem Modul werden allgemein verwendete Makros, Typen etc definiert.
 * 
 * @author  Ulrike Griefahn
 * @date    2019-11-07
 */

/* ------------------------------------------------------------------------ */
#ifndef _COMMON_H
#define _COMMON_H
/* ------------------------------------------------------------------------ */


/* ===========================================================================
 * Typdefinitionen
 * ======================================================================== */

/**
 * Wahrheitswerte
 */
typedef enum {
   FALSE, 
   TRUE 
} BOOL;


/* ===========================================================================
 * Makros zum Debuggen
 * ======================================================================== */

/**
 * Debug-Ausgabe von Ausdrücken, die eine ganze Zahl liefern
 */
#define DPRINT(P) printf(#P "= %d\n", P)

/**
 * Debug-Ausgabe von Ausdrücken, die eine Zeichenkette liefern
 */
#define SPRINT(P) printf(#P "= \"%s\"\n", P)

/**
 * Debug-Ausgabe von Ausdrücken, die ein Zeichen liefern
 */
#define CPRINT(P) printf(#P "= %c\n", P)

/**
 * Debug-Ausgabe von Ausdrücken, die eine ganze Zahl liefern
 * (hexadezimale Ausgabe)
 */
#define XPRINT(P) printf(#P "= %x\n", P)

/* ------------------------------------------------------------------------ */
#endif /* _COMMON_H */
