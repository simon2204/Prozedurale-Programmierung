/* ===========================================================================
 * Header-Dateien einbinden
 * ======================================================================== */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "parse.h"
#include "read.h"


/* ===========================================================================
 * Symbolische Konstanten
 * ======================================================================== */

/**
 * Maximale Anzahl von Tokens, die verarbeitet werden können
 */
#define MAX_TOKENS 128


/* ===========================================================================
 * Globale Variablen
 * ======================================================================== */

/**
 * Das aktuelle Token, das vom Modul 'read' geliefert wird
 */
static char next_token[MAX_TOKEN_LENGTH];

/**
 * Enthält alle Tokens des arithmetischen Ausdrucks in Postfix-Reihenfolge
 */
static char postfix_tokens[MAX_TOKENS][MAX_TOKEN_LENGTH];

/**
 * Nächste freie Position in postfix_tokens
 */
static int token_position;


/* ===========================================================================
 * Funktionsprototypen (static)
 * ======================================================================== */


/**
 * Verarbeitet ab dem aktuellen Token eine längstmögliche Folge von Tokens,
 * die einen gültigen Ausdruck bildet und kopiert die Tokens in ihrer
 * Postfixdarstellung in die Tokenliste (postfix_tokens)
 *
 * Verändert die globale Variable postfix_tokens
 */
static void parse_expression(void);


/**
 * Verarbeitet ab dem aktuellen Token eine längstmögliche Folge von Tokens,
 * die einen gültigen Term bildet und kopiert die Tokens in ihrer
 * Postfixdarstellung in die Tokenliste (postfix_tokens)
 *
 * Verändert die globale Variable postfix_tokens
 */
static void parse_term(void);

/**
 * Verarbeitet ab dem aktuellen Token eine längstmögliche Folge von Tokens,
 * die einen gültigen Faktor bildet und kopiert die Tokens in ihrer
 * Postfixdarstellung in die Tokenliste (postfix_tokens)
 *
 * Verändert die globale Variable postfix_tokens
 */
static void parse_factor(void);

/**
 * Fügt das übergebene Token an das Ende der Tokenliste an. Bricht mit einer
 * Fehlermeldung ab, wenn kein Token mehr angefügt werden kann.
 *
 * Verändert die globale Variable postfix_tokens
 */
static void add_postfix_token(char token[]);


/* ===========================================================================
 * Funktionsdefinitionen (extern)
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Funktion: parse
 * ------------------------------------------------------------------------ */
extern void parse(void)
{
    token_position = 0;

    /* Erstes Token holen */
    if (get_next_token(next_token))
    {
        parse_expression();
    }
}

/* --------------------------------------------------------------------------
 * Funktion: get_next_postfix_token
 * ------------------------------------------------------------------------ */
extern BOOL get_next_postfix_token(/*@out@*/ char next_postfix_token[])
{
    /* Die statische Variable 'index' sorgt dafür, dass bei jedem Aufruf das
     * in der Tokenliste nächste Token aus der Postfixdarstellung in die
     * Variable next_postfix_token kopiert wird. */

    static int index = 0;
    if (index < token_position)
    {
        strncpy(next_postfix_token, postfix_tokens[index], MAX_TOKEN_LENGTH - 1);
        next_postfix_token[MAX_TOKEN_LENGTH] = '\0';
        
        index += 1;
        return TRUE;

    }
    else
    {
        next_postfix_token[0] = '\0';
        index = 0;
        return FALSE;
    }
}

/* --------------------------------------------------------------------------
 * Funktion: print_postfix_tokens
 * ------------------------------------------------------------------------ */
extern void print_postfix_tokens(void)
{
    int index;

    printf("Tokens: ");
    for (index = 0; index < token_position; index++)
    {
        printf("%s%s", postfix_tokens[index],
               (index < token_position - 1) ? ", " : "");
    }
    printf("\n");
}

/* ===========================================================================
 * Funktionsdefinitionen (static)
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Funktion: parse_expression
 * ------------------------------------------------------------------------ */
static void parse_expression(void)
{
    parse_term();

    while (next_token[0] == PLUS_OP || next_token[0] == MINUS_OP)
    {
        char op[2];
        op[0] = next_token[0]; /* akt. Operator sichern */
        op[1] = '\0';

        (void) get_next_token(next_token);
        parse_term();

        add_postfix_token(op);
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: parse_term
 * ------------------------------------------------------------------------- */
static void parse_term(void)
{
    parse_factor();

    while (next_token[0] == TIMES_OP || next_token[0] == DIVIDE_OP)
    {
        char op[2];
        op[0] = next_token[0]; /* akt. Operator sichern */
        op[1] = '\0';

        (void) get_next_token(next_token);
        parse_factor();

        add_postfix_token(op);
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: parse_factor
 * ------------------------------------------------------------------------- */
static void parse_factor(void)
{
    if (IS_DIGIT(next_token[0]) || IS_DOT(next_token[0]))
    {
        /* Gleitpunktzahl gefunden */
        add_postfix_token(next_token);
        (void) get_next_token(next_token);

    }
    else
    {
        /* Geklammerten Ausdruck gefunden */
        (void) get_next_token(next_token); /* '(' überlesen */
        parse_expression();
        (void) get_next_token(next_token); /* ')' überlesen */
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: add_postfix_token
 * ------------------------------------------------------------------------ */
static void add_postfix_token(char token[])
{
    if (token_position < MAX_TOKENS)
    {

        /* noch genug Platz --> Token in nächstes freie Feld kopieren */
        strncpy(postfix_tokens[token_position], token, MAX_TOKEN_LENGTH - 1);
        postfix_tokens[token_position][MAX_TOKEN_LENGTH] = '\0';
        token_position++;

    }
    else
    {
        printf("error: symbols array full, can't add %s\n", token);
        exit(EXIT_FAILURE);
    }
}
