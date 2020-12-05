//
//  Huffman.c
//  Huffman
//
//  Created by Simon Schöpke on 03.12.20.
//

#include "huffman.h"

extern void test_rd_chars_wr_bits(char in[], char out[])
{
    init_in(in);
    init_out();
    
    unsigned char next_byte;
    while (has_next_char()) {
        next_byte = read_char();
        
        if (next_byte < 'a')
        {
            write_bit(ONE);
        }
        else
        {
            write_bit(ZERO);
        }
    }
    
    get_out_buffer(out);
}

extern void test_rd_bits_wr_chars(char in[], char out[])
{
    init_in(in);
    init_out();
    
    unsigned char next_bit;
    while (has_next_bit()) {
        next_bit = read_bit();
        
        if (next_bit == ONE)
        {
            write_char('1');
        }
        else
        {
            write_char('0');
        }
    }
    
    get_out_buffer(out);
}
