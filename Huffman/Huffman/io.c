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

static void read_infile(void);

static void write_outfile(void);

/// Eingabe Buffer
static unsigned char in_buffer[BUF_SIZE];
/// Ausgabe Buffer
static unsigned char out_buffer[BUF_SIZE];

/// Das nächst zulesende Bit
static int lese_position(void);

static unsigned int lese_segment;
static unsigned int lese_element;

/// Das nächst zuschreibende Bit
//static unsigned int schreib_position;

static unsigned int schreib_segment;
static unsigned int schreib_element;

/// Füllstand von `in_buffer` in Byte
static unsigned int in_buffer_size;
/// Füllstand von `out_buffer` in Byte
static int out_buffer_size(void);

static FILE *input_stream;

static FILE *output_stream;

static int out_buffer_size(void)
{
    return schreib_segment + (schreib_element > 0 ? 1 : 0);
}

static int lese_position(void)
{
    return lese_segment + (lese_element > 0 ? 1 : 0);
}

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
    
    if (output_stream == NULL)
    {
        printf("Die Datei konnte nicht geöffnet werden.");
        exit(IO_ERROR);
    }
    
    init_out();
}

static void read_infile(void)
{
    size_t read_count;
    
    read_count = fread(in_buffer, sizeof(char), BUF_SIZE, input_stream);
    
    in_buffer_size = (unsigned int) read_count;
}

static void write_outfile(void)
{
    fwrite(out_buffer, sizeof(char), out_buffer_size(), output_stream);
    init_out();
}

extern void close_infile(void)
{
    fclose(input_stream);
}

extern void close_outfile(void)
{
    if (out_buffer_size > 0)
    {
        write_outfile();
    }
    
    fclose(output_stream);
}

extern void init_in(void)
{
    lese_segment = 0;
    lese_element = 0;
}

extern void init_out(void)
{
    schreib_segment = 0;
    schreib_element = 0;
}

extern bool has_next_char(void)
{
    return lese_segment < in_buffer_size;
}

extern unsigned char read_char(void)
{
    unsigned char next_char = in_buffer[lese_segment];
    lese_segment++;
    
    if (lese_segment == in_buffer_size)
    {
        lese_segment = 0;
        read_infile();
    }
    
    return next_char;
}

extern void write_char(unsigned char c)
{
    out_buffer[schreib_segment] = c;
    schreib_segment++;
    
    if (out_buffer_size() == BUF_SIZE)
    {
        write_outfile();
    }
}

extern bool has_next_bit(void)
{
    return lese_position() < in_buffer_size;
}

extern BIT read_bit(void)
{
    BIT next_bit = GET_BIT(in_buffer[lese_segment], lese_element);
    lese_element++;
    
    if (lese_element == BYTE_SIZE)
    {
        lese_segment++;
        lese_element = 0;
    }
    
    if (lese_position() == in_buffer_size)
    {
        init_in();
        read_infile();
    }
    
    return next_bit;
}

extern void write_bit(BIT c)
{
    out_buffer[schreib_segment] = PUT_BIT(out_buffer[schreib_segment], c, schreib_element);
    
    schreib_element++;
    
    if (schreib_element == BYTE_SIZE)
    {
        schreib_segment++;
        schreib_element = 0;
    }
    
    if (out_buffer_size() == BUF_SIZE)
    {
        write_outfile();
    }

}
