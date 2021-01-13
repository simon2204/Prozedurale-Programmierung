//
//  huffman_common.h
//  Huffman
//
//  Created by Simon Schöpke on 03.12.20.
//

#ifndef huffman_common_h
#define huffman_common_h

/// Repräsentiert die beiden Bitzustände 0 und 1.
typedef enum {
    ZERO,
    ONE
} BIT;

typedef enum {
    SUCCESS = 0,
    UNKNOWN_ERROR,
    COMMANDLINEARGUMENT_ERROR,
    IO_ERROR,
    COMPRESS_ERROR,
} EXITCODE;

#ifdef DEBUG
#include <stdio.h>
/**
 * Debug-Ausgabe von Ausdrücken, die eine ganze Zahl liefern
 */
#define DPRINT(P) printf(#P "= %d\n", P);

/**
 * Debug-Ausgabe von Ausdrücken, die eine Zeichenkette liefern
 */
#define SPRINT(P) printf(#P "= \"%s\"\n", P);

/**
 * Debug-Ausgabe von Ausdrücken, die ein Zeichen liefern
 */
#define CPRINT(P) printf(#P "= %c\n", P);

/**
 * Debug-Ausgabe von Ausdrücken, die eine ganze Zahl liefern
 * (hexadezimale Ausgabe)
 */
#define XPRINT(P) printf(#P "= %x\n", P);

#endif /* DEBUG */
#endif /* huffman_common_h */


