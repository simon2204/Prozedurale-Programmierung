//
//  huffman_common.h
//  Huffman
//
//  Created by Simon Schöpke on 03.12.20.
//

#ifndef huffman_common_h
#define huffman_common_h

typedef enum: int {
    ZERO = 0,
    ONE = 1
} BIT;


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

#endif /* huffman_common_h */


