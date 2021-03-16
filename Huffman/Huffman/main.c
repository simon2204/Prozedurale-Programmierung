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
#include "dyn_string.h"

int main(int argc, char * argv[]) {

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
    
    return 0;
}
