//
//  huffman.h
//  huffman
//
//  Created by Simon Schöpke on 03.12.20.
//

#ifndef huffman_h
#define huffman_h

#include <stdio.h>
#include <time.h>
#include "io.h"


/// Testet die Funktionen 'read_char' und 'write_bit'.
extern void compress(char in_filename[], char out_filename[]);

/// Testet die Funktionen 'read_bit' und 'write_char'.
extern void decompress(char in_filename[], char out_filename[]);

#endif /* huffman_h */


