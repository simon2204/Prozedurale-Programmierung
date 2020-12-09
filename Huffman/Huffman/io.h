//
//  io.h
//  Huffman
//
//  Created by Simon Schöpke on 03.12.20.
//

#ifndef io_h
#define io_h

#include <stdbool.h>
#include "huffman_common.h"

extern void init_in(char text[]);
extern void init_out(void);
extern void get_out_buffer(char text[]);
extern bool has_next_char(void);
extern unsigned char read_char(void);
extern void write_char(unsigned char c);
extern bool has_next_bit(void);
extern BIT read_bit(void);
extern void write_bit(BIT c);

#endif /* io_h */
