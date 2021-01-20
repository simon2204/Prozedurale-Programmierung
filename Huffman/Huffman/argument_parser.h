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
#include <stdarg.h>
#include "huffman_common.h"

#define FILE_NAME_LENGTH 1028

extern void parse_argv(int argc, char **argv);

extern void get_infile(char infile_name[]);

extern void get_outfile(char outfile_name[]);

extern HUFFMAN_MODE huffman_mode(void);

extern bool wants_verbose_info(void);

#endif /* argument_parser_h */
