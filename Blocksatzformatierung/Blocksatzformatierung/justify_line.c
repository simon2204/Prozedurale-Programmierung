//
//  justify_line.c
//  Blocksatzformatierung
//
//  Created by Simon Schöpke on 28.12.20.
//

#include "justify_line.h"

/// Hilfsfunktion für `justify_line`.
/// @param p_line Pointer zur Zeile, die formatiert werden soll.
/// @param p_justified_line Formatierte Zeile als Rückgabe.
static void justify_line_helper(char *p_line, char *p_justified_line);

/// Zählt die Anzahl an Token und die Anzahl an Zeichen, die in der Zeile vorkommen.
/// Dabei zählen die Leerzeichen als Trennzeichen und werden nicht mitgezählt.
/// @param p_line Pointer zur Zeile.
/// @param token_count Anzahl der Token, als Rückgabe.
/// @param char_count Anzahl der Zeichen, als Rückgabe.
static void line_info(char *p_line, int* token_count, int* char_count);

/// Überspringt die nächste Folge von Leerzeichen.
/// @param p_line Pointer auf den Pointer der Zeile.
static void skip_white_spaces(char** p_line);

/// Anzahl der Token in einer Zeile.
static int token_count;

/// Anzahl der Zeichen in einer Zeile.
static int char_count;

/// Anzahl der zu einfügenden Zwischenräume in einer Zeile.
static int gap_count;

/// Breite eines einzelnen Zwischenraums. Breite als Anzahl von Leerzeichen.
static int gap_width;

/// Anzahl an zu aufteilenden Leerzeichen.
static int whitespace_count;

/// Anzahl der Leerzeichen, die nach gleichmäßiger Verteilung auf den Zwischenräumen ürig geblieben sind.
static int whitespace_remainder;

/// Leerzeichen
#define WHITESPACE ' '

/// Zeilenende
#define END_OF_LINE '\0'

extern void justify_line(char *p_line, int target_line_length, char *p_justified_line)
{
    token_count = 0;
    char_count = 0;
    
    line_info(p_line, &token_count, &char_count);
    
    gap_count = token_count - 1;
    whitespace_count = target_line_length - char_count;
    
    if (gap_count != 0)
    {
        gap_width = whitespace_count / gap_count;
        whitespace_remainder = whitespace_count % gap_count;
    }
    
    justify_line_helper(p_line, p_justified_line);
}

static void justify_line_helper(char *p_line, char *p_justified_line)
{
    int i;
    int additional_whitespace;
    
    skip_white_spaces(&p_line);
    
    while (*p_line != END_OF_LINE)
    {
    
        while (*p_line != WHITESPACE && *p_line != END_OF_LINE)
        {
            *p_justified_line = *p_line;
            p_line++;
            p_justified_line++;
        }
        
        if (gap_count > 0)
        {
            additional_whitespace = whitespace_remainder > 0 ? 1 : 0;
            
            for (i = 0; i < gap_width + additional_whitespace; i++)
            {
                *p_justified_line = WHITESPACE;
                p_justified_line++;
            }
            whitespace_remainder--;
            gap_count--;
        }
        
        skip_white_spaces(&p_line);
    }
    
    *p_justified_line = END_OF_LINE;
}

static void line_info(char *p_line, int* token_count, int* char_count)
{
    skip_white_spaces(&p_line);

    while (*p_line != END_OF_LINE)
    {
        while (*p_line != WHITESPACE && *p_line != END_OF_LINE)
        {
            (*char_count)++;
            p_line++;
        }

        skip_white_spaces(&p_line);

        (*token_count)++;
    }
}

static void skip_white_spaces(char** p_line)
{
    while (**p_line == WHITESPACE && **p_line != END_OF_LINE)
    {
        (*p_line)++;
    }
}
