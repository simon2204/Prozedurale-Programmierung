//
//  io.c
//  Huffman
//
//  Created by Simon Schöpke on 03.12.20.
//

#include "io.h"

#define BYTE_SIZE 8

#define BUF_SIZE 4096

/// Gibt das Bit an der Position 'POS' im übergebenen 'BYTE' zurück.
/// Liefert ONE, wenn das Bit an der entsprechenden Stelle gesetzt ist und ZERO, wenn es nicht gesetzt ist.
#define GET_BIT(BYTE, POS) ((0x80u >> POS & BYTE) > 0 ? ONE : ZERO)

/// Setzt, wenn 'BIT' ONE oder löscht wenn 'BIT' ZERO ist, ein Bit an Position 'POS' in dem übergebenen 'BYTE'
/// und gibt ein neues BYTE mit dem gesetzten bzw. geöschten Bit zurück.
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

static FILE *input_stream;

static FILE *output_stream;

extern void open_infile(char in_filename[])
{
    input_stream = fopen(in_filename, "rb");
    
    if (input_stream == NULL)
    {
        printf("Die Datei konnte nicht geöffnet werden.");
        exit(IO_ERROR);
    }
    
    init_in();
    
    read_infile();
}

extern void open_outfile(char out_filename[])
{
    output_stream = fopen(out_filename, "wb");
    
    if (input_stream == NULL)
    {
        printf("Die Datei konnte nicht geöffnet werden.");
        exit(IO_ERROR);
    }
    
    init_out();
    
//    fwrite(out_buffer, sizeof(char), BUF_SIZE, output_stream);
}

static void read_infile(void)
{
    size_t read_count;
    
    read_count = fread(in_buffer, sizeof(char), BUF_SIZE, input_stream);
    
    in_buffer_size = (unsigned int) read_count * BYTE_SIZE;
}

extern void close_infile(void)
{
    fclose(input_stream);
}

extern void close_outfile(void)
{
    fclose(output_stream);
}

extern void init_in(void)
{
    lese_position = 0;
    in_buffer_size = 0;
}

extern void init_out(void)
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
    text[i] = '\0';
}

extern bool has_next_char(void)
{
    return lese_position < in_buffer_size;
}

extern unsigned char read_char(void)
{
    unsigned int segment = lese_position / BYTE_SIZE;
    unsigned char next_char = in_buffer[segment];
    lese_position += BYTE_SIZE;
    
    if (lese_position == in_buffer_size)
    {
        lese_position = 0;
        read_infile();
    }
    
    return next_char;
}

extern void write_char(unsigned char c)
{
    unsigned int segment = schreib_position / BYTE_SIZE;
    out_buffer[segment] = c;
    schreib_position += BYTE_SIZE;
    out_buffer_size += BYTE_SIZE;
}

extern bool has_next_bit(void)
{
    return lese_position < in_buffer_size;
}

extern BIT read_bit(void)
{
    unsigned int segment = lese_position / BYTE_SIZE;
    unsigned int pos = lese_position % BYTE_SIZE;
    BIT next_bit = GET_BIT(in_buffer[segment], pos);
    lese_position++;
    
    if (lese_position == in_buffer_size)
    {
        lese_position = 0;
        read_infile();
    }
    
    return next_bit;
}

extern void write_bit(BIT c)
{
    unsigned int segment = schreib_position / BYTE_SIZE;
    unsigned int pos = schreib_position % BYTE_SIZE;
    out_buffer[segment] = PUT_BIT(out_buffer[segment], c, pos);
    schreib_position++;
    out_buffer_size++;
}
