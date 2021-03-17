//
//  main.c
//  Huffman
//
//  Created by Simon Schöpke on 03.12.20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
#include "argument_parser.h"
#include "io.h"

int main(int argc, char * argv[]) {
    clock_t prg_start;
    clock_t prg_end;

    prg_start = clock();

    parse_argv(argc, argv);

    char in_filename[FILE_NAME_LENGTH];
    char out_filename[FILE_NAME_LENGTH];

    get_infile(in_filename);
    get_outfile(out_filename);

    if (huffman_mode() == COMPRESS)
    {
        compress(in_filename, out_filename);
    }
    else if (huffman_mode() == DECOMPRESS)
    {
        decompress(in_filename, out_filename);
    }

    prg_end = clock();

    if (wants_verbose_info())
    {
        printf(" - Die Laufzeit betrug %.2f Sekunden\n",
        (float) (prg_end - prg_start) / CLOCKS_PER_SEC);
    }
    
    return 0;
}
