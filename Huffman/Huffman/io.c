//
//  io.c
//  Huffman
//
//  Created by Simon Schöpke on 03.12.20.
//

#include "io.h"

#define BYTE_SIZE 8

#define BUF_SIZE 4096

#define GET_BIT(BYTE, POS) ((0x80u >> POS & BYTE) > 0 ? ONE : ZERO)

#define PUT_BIT(BYTE, BIT, POS) (BIT == ZERO ? ~(0x80u >> POS) & BYTE : (0x80u >> POS) | BYTE)

/// Eingabe Buffer
static unsigned char in_buffer[BUF_SIZE];
/// Ausgabe Buffer
static unsigned char out_buffer[BUF_SIZE];

/// Das nächst zulesende Bit
static unsigned int lese_position;
/// Das nächst zuschreibende Bit
static unsigned int schreib_position;

/// Füllstand von `in_buffer` in Bit
static unsigned int in_buffer_size;
/// Füllstand von `out_buffer` in Bit
static unsigned int out_buffer_size;

extern void init_in(char text[])
{
    lese_position = 0;
    unsigned int segment = 0;
    char buchstabe = text[0];
    while (buchstabe != '\0') {
        in_buffer[segment] = buchstabe;
        segment += 1;
        buchstabe = text[segment];
    }
    in_buffer_size = segment * BYTE_SIZE;
}

extern void init_out()
{
    schreib_position = 0;
    out_buffer_size = 0;
}

extern void get_out_buffer(char text[])
{
    unsigned int i;
    for (i = 0; i < out_buffer_size / BYTE_SIZE; i++)
    {
        text[i] = out_buffer[i];
    }
}

extern bool has_next_char()
{
    return lese_position < in_buffer_size;
}

extern unsigned char read_char()
{
    unsigned int segment = lese_position / BYTE_SIZE;
    unsigned char next_char = in_buffer[segment];
    lese_position += BYTE_SIZE;
    return next_char;
}

extern void write_char(unsigned char c)
{
    unsigned int segment = schreib_position / BYTE_SIZE;
    out_buffer[segment] = c;
    schreib_position += BYTE_SIZE;
    out_buffer_size += BYTE_SIZE;
}

extern bool has_next_bit()
{
    return lese_position < in_buffer_size;
}

extern enum BIT read_bit()
{
    unsigned int segment = lese_position / BYTE_SIZE;
    unsigned int pos = lese_position % BYTE_SIZE;
    enum BIT next_bit = GET_BIT(in_buffer[segment], pos);
    lese_position++;
    return next_bit;
}

extern void write_bit(enum BIT c)
{
    unsigned int segment = schreib_position / BYTE_SIZE;
    unsigned int pos = schreib_position % BYTE_SIZE;
    out_buffer[segment] = PUT_BIT(out_buffer[segment], c, pos);
    schreib_position++;
    out_buffer_size++;
}
