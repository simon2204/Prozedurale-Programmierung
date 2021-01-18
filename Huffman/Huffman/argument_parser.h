//
//  argument_parser.h
//  Huffman
//
//  Created by Simon Schöpke on 09.01.21.
//

#ifndef argument_parser_h
#define argument_parser_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "huffman_common.h"

extern void parse_argv(int argc, char **argv);

extern void get_outfile(char outfile_name[]);

extern bool compress_file(void);

extern bool decompress_file(void);

extern bool print_verbose_info(void);

extern bool needs_help(void);

#endif /* argument_parser_h */
