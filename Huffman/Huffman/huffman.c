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
    
    while (has_next_char())
    {
        
        if (read_char() < 'a')
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
    
    while (has_next_bit())
    {
        
        if (read_bit() == ONE)
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
