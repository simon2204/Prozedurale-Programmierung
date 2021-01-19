//
//  Huffman.c
//  Huffman
//
//  Created by Simon Schöpke on 03.12.20.
//

#include "huffman.h"


extern void test_rd_chars_wr_bits(char in_filename[], char out_filename[])
{
    clock_t prg_start;
    clock_t prg_end;
    
    prg_start = clock();
    
    open_infile(in_filename);
    open_outfile(out_filename);
    
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
    
    close_infile();
    close_outfile();
    
    prg_end = clock();
    
    if (wants_verbose_info())
    {
        printf(" - Die Laufzeit betrug %.2f Sekunden\n",
        (float) (prg_end - prg_start) / CLOCKS_PER_SEC);
    }
}


extern void test_rd_bits_wr_chars(char in_filename[], char out_filename[])
{
    clock_t prg_start;
    clock_t prg_end;
    
    prg_start = clock();
    
    open_infile(in_filename);
    open_outfile(out_filename);
    
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
    
    close_infile();
    close_outfile();
    
    prg_end = clock();
    
    if (wants_verbose_info())
    {
        printf(" - Die Laufzeit betrug %.2f Sekunden\n",
        (float) (prg_end - prg_start) / CLOCKS_PER_SEC);
    }
}
