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


/// Komprimiert den Text der über den Dateinamen in `in_filename` angegeben wird und schreibt diesen in die Ausgabedatei `out_filename`.
/// @param in_filename Der Name der zu komprimierenden Datei.
/// @param out_filename Der Name der kompirierten Datei.
extern void compress(char in_filename[], char out_filename[]);

/// Dekomprimiert den Text der über den Dateinamen in `in_filename` angegeben wird und schreibt diesen in die Ausgabedatei `out_filename`.
/// @param in_filename Der Name der zu dekomprimierenden Datei.
/// @param out_filename Der Name der dekompirierten Datei.
extern void decompress(char in_filename[], char out_filename[]);

#endif /* huffman_h */


