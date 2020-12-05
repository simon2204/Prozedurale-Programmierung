/**
 * @file
 * In diesem Modul werden die vom Modul read.h eingelesenen Tokens
 * geparst und in Postfix-Notation überführt.
 *
 * @author  Ulrike Griefahn
 * @date    2019-11-07
 */

/* ------------------------------------------------------------------------ */
#ifndef _PARSER_H
#define _PARSER_H
/* ------------------------------------------------------------------------ */


/* ===========================================================================
 * Header-Dateien einbinden
 * ======================================================================== */

#include "calculator_common.h"


/* ===========================================================================
 * Symbolische Konstanten
 * ======================================================================== */

/**
 * Maximale Anzahl Zeichen eines Tokens
 */
#define MAX_TOKEN_LENGTH 32


/* ===========================================================================
 * Funktionensprototypen
 * ======================================================================== */

/**
 * Parst die Tokens des arithmetischen Ausdrucks, die durch das Modul read.h
 * eingelesen werden.
 */
extern void parse(void);

/**
 * Liefert das nächste Token der Postfixdarstellung als Zeichenkette.
 *
 * Es wird davon ausgegangen, dass das übergebene Zeichenarray groß genug
 * ist, um das nächste Token aufzunehmen.
 *
 * @param next_postfix_token das naechste Token
 * @return TRUE, wenn es noch ein Token gab, FALSE sonst
 */
extern BOOL get_next_postfix_token(/*@out@*/ char next_postfix_token[]);

 /**
  * Gibt die Tokens in Postfixnotation auf dem Bildschirm aus.
  */
extern void print_postfix_tokens(void);

/* ------------------------------------------------------------------------ */
#endif /* _PARSER_H */
