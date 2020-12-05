/* ===========================================================================
 * Header-Dateien einbinden
 * ======================================================================== */

#include <stdio.h>
#include <stdlib.h>

#include "read.h"


/* ===========================================================================
 * Symbolische Konstanten
 * ======================================================================== */

/**
 * Maximale Größe des Puffers, in den Eingabezeichen zurückgestellt werden
 * können
 */
#define BUFFER_SIZE 100


/* ===========================================================================
 * Makros
 * ======================================================================== */

/**
 * Überprüfung auf Zeilen- oder Dateiende
 */
#define IS_END_OF_INPUT(CHAR) (CHAR == '\n' || CHAR == EOF)

/**
 * Überprüfung auf Punkt
 */
#define IS_DOT(CHAR) (CHAR == '.')

/**
 * Überprüfung auf Exponentzeichen
 */
#define IS_EXPONENT(CHAR) (CHAR == 'e' || CHAR == 'E')

/**
 * Überprüfung auf Leer- oder Tabulatorzeichen
 */
#define IS_WHITESPACE(CHAR) (CHAR == ' ' || CHAR == '\t')

/**
 * Überprüfung auf runde Klammer
 */
#define IS_BRACKET(CHAR) (CHAR == L_BRACKET || CHAR == R_BRACKET)

/**
 * Überprüfung auf Operator
 */
#define IS_OP(CHAR) (CHAR == PLUS_OP || CHAR == MINUS_OP \
                     || CHAR == TIMES_OP || CHAR == DIVIDE_OP)


/* ===========================================================================
 * Globale Variablen
 * ======================================================================== */

/**
 * Puffer für zurückgestellte Zeichen
 */
static char buffer[BUFFER_SIZE];

/**
 *  Das nächste freie Position im Puffer
 */
static int buffer_position = 0;


/* ==========================================================================
 * Funktionsprototypen
 * ======================================================================= */

/**
 * Liefert das nächste Zeichen. Ist noch ein Zeichen im Puffer, wird dieses
 * aus dem Puffer gelöscht und zurückgegeben. Im anderen Fall, wird ein neues 
 * Zeichen von der Standardeingabe gelesen.
 *
 * Verändert die globalen Variablen 'buffer' und 'buffer_position'
 *
 * @return das nächste Zeichen
 */
static int get_buffered_char(void);

/**
 * Stellt das übergebene Zeichen in den Puffer zurück.
 *
 * Verändert die globalen Variablen 'buffer' und 'buffer_position'
 *
 * @param character - das zurückzustellende Zeichen
 */
static void unget_buffered_char(int character);


/* ==========================================================================
 * Funktionsdefinitionen (extern)
 * ======================================================================= */

/* --------------------------------------------------------------------------
 * Funktion: get_next_token
 * ----------------------------------------------------------------------- */
extern BOOL get_next_token(char next_token[])
{
    int current_char;
    BOOL return_state = FALSE;

    next_token[0] = '\0';

    /* Lese erstes Zeichen */
    current_char = get_buffered_char();

    /* Führende White-Spaces überlesen */
    while (IS_WHITESPACE(current_char))
    {
        current_char = get_buffered_char();
    }
    /* Prüfen, ob das Ende der Eingabe  erreicht ist. */
    if (!IS_END_OF_INPUT(current_char))
    {
        if (IS_BRACKET(current_char) || IS_OP(current_char))
        {
            /* Klammern und Operatoren sind vollständige Token */
            next_token[0] = current_char;
            next_token[1] = '\0';
            return_state = TRUE;
        }
        else
        {
            /* Lese Gleitkommazahl (ohne Fehlerprüfung, nur positive Zahlen */
            int index = 0;
            while (IS_DIGIT(current_char) || IS_DOT(current_char)
                    || IS_EXPONENT(current_char))
            {
                next_token[index] = current_char;
                index += 1;
                current_char = get_buffered_char();
            }
            next_token[index] = '\0'; /* Zeichenkette beenden */

            /* Zu viel gelesenes Zeichen in den Eingabepuffer zurückstellen */
            unget_buffered_char(current_char);

            return_state = TRUE;
        }
    }
    return return_state;
}

/* ==========================================================================
 * Funktionsdefinitionen (static)
 * ======================================================================= */

/* --------------------------------------------------------------------------
 * Funktion: get_buffered_char
 * ----------------------------------------------------------------------- */
static int get_buffered_char(void)
{
    if (buffer_position > 0)
    {
        /* Es ist noch ein Zeichen im Puffer, buffer_position vor dem Zugriff,
         * um 1 zurücksetzen, da der Wert auf die erste freie Position zeigt */
        buffer_position -= 1;
        return buffer[buffer_position];
    }
    else
    {
        /* Puffer leer, lese von der Standardeingabe */
        return getchar();
    }
}

/* --------------------------------------------------------------------------
 * Funktion: unget_buffered_char
 * ----------------------------------------------------------------------- */
static void unget_buffered_char(int character)
{
    if (buffer_position >= BUFFER_SIZE)
    {
        /* Puffer voll, breche ab mit Fehlermeldung */
        printf("unget_buffered_char: too many characters\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* Füge das Zeichen an der nächsten freien Position ein und erhöhe 
         * diese um 1 */
        buffer[buffer_position] = character;
        buffer_position += 1;
    }
}
