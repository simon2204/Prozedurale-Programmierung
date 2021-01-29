/**
 * @file
 * In diesem Modul werden allgemein verwendbare Makros und Typen definiert.
 *
 * @author  Ulrike Griefahn
 * @date    2015-12-14
 */

/* ------------------------------------------------------------------------- */
#ifndef BINARY_TREE_COMMON_H
#define BINARY_TREE_COMMON_H
/* ------------------------------------------------------------------------- */

/* ========================================================================= *
 * Header-Dateien
 * ========================================================================= */

#include <stdbool.h>


/* ========================================================================= *
 * Makros und symbolische Konstanten
 * ========================================================================= */

/**
 * Makro zum Freigeben von Speicher und Setzen des Zeiger auf NULL
 */
#define FREE_NULL(VAR) {free(VAR); VAR = NULL;}

/**
 * Makro zur Prüfung, ob die Variable den Wert NULL hat: Ist die Bedingung
 * wahr, wird das Programm abgebrochen
 */
#define ENSURE_ENOUGH_MEMORY(VAR, FUNCTION) \
{if (VAR == NULL) { printf(FUNCTION ": not enough memory\n"); \
                    exit(EXIT_FAILURE); }}


/* ===========================================================================
 * Debug-Anweisungen
 * ======================================================================== */

#ifdef DEBUG
/** Präprozessor-Makro für Debugausgaben */
#include <stdio.h>
#define CPRINT(E) printf(#E " = %c\n", E)
#define DPRINT(E) printf(#E " = %d\n", E)
#define FPRINT(E) printf(#E " = %f\n", E)
#define SPRINT(E) printf(#E " = %s\n", E)
#define XPRINT(E) printf(#E " = %x\n", E)
#else
/** Präprozessor-Makro für Debugausgaben (nicht definiert) */
#define CPRINT(E)
#define DPRINT(E)
#define FPRINT(E)
#define SPRINT(E)
#define XPRINT(E)
#endif

/* ------------------------------------------------------------------------- */
#endif	/* BINARY_TREE_COMMON_H */

