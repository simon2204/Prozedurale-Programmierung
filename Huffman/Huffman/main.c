//
//  main.c
//  Huffman
//
//  Created by Simon Schöpke on 03.12.20.
//

#include <stdio.h>
#include <string.h>
#include "huffman.h"

int main(int argc, const char * argv[]) {
    char in[] = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxX";
    char out[50] = {0};
    test_rd_chars_wr_bits(in, out);
    int cmp = strcmp(out, "UUUUUU");
    printf("%d\n", cmp);
    
    char in2[] = {0b10000000, 0b00000001, 0b00000000};
    char out2[50] = {0};
    
    test_rd_bits_wr_chars(in2, out2);
    printf("%s\n", out2);
    return 0;
}

