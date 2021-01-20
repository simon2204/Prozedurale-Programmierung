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

/// Füllt das Byte `BYTE` mit Nullen auf, ab Position `POS`.
#define PADDING(BYTE, POS) ~(0xFF >> POS) & BYTE

/// Initialisiert den internen Eigabepuffer.
static void init_in(void);

/// Leert den Ausgabepuffer.
static void init_out(void);

/// Liest den Inhalt aus `input_stream` in den `in_buffer`
/// mit einer maximalen Anzahl von `BUF_SIZE` Bytes
static void read_infile(void);

/// Schreibt den Inhalt von `out_buffer` in den `output_stream`
/// mit einer maximalen Anzahl von `BUF_SIZE` Bytes
static void write_outfile(void);

/// Eingabe Buffer
static unsigned char in_buffer[BUF_SIZE];
/// Ausgabe Buffer
static unsigned char out_buffer[BUF_SIZE];

/// Zeigt auf das nächst zulesende Byte in `in_buffer`
static unsigned short lese_segment;
/// Zeigt auf das nächst zulesende Bit in `lese_segment`
static unsigned short lese_element;

/// Zeigt auf das nächst zuschreibende Byte in `out_buffer`
static unsigned short schreib_segment;
/// Zeigt auf das nächst zuschreibende Bit in `schreib_segment`
static unsigned short schreib_element;

/// Füllstand von `in_buffer` in Byte
static unsigned short in_buffer_size;

/// Die zu komprimierende oder zu dekomprimierende Datei
static FILE *input_stream;

/// Die komprimierte oder dekomprimierte Datei
static FILE *output_stream;

static void init_in(void)
{
    lese_segment = 0;
    lese_element = 0;
}

static void init_out(void)
{
    schreib_segment = 0;
    schreib_element = 0;
}

extern void open_infile(char in_filename[])
{
    input_stream = fopen(in_filename, "rb");
    
    if (input_stream == NULL)
    {
        printf("Die Datei konnte nicht geöffnet werden.\n");
        exit(IO_ERROR);
    }

    read_infile();
}

extern void open_outfile(char out_filename[])
{
    output_stream = fopen(out_filename, "wb");
    
    if (output_stream == NULL)
    {
        printf("Die Datei konnte nicht erstellt werden.\n");
        exit(IO_ERROR);
    }
    
    init_out();
}

static void read_infile(void)
{
    init_in();
    in_buffer_size = fread(in_buffer, sizeof(char), BUF_SIZE, input_stream);
}

static void write_outfile(void)
{
    // Wenn das letzte Byte im `out_buffer` nicht ganz aufgefüllt wurde
    if (schreib_element != 0)
    {
        // wird das letzte Byte mit Nullen aufgefüllt
        out_buffer[schreib_segment] = PADDING(out_buffer[schreib_segment], schreib_element);
    }
    
    // schreib_segment = 1; schreib_element = 4;
    // [0: [0,0,1,0,1,1,0,1], 1: [1,0,1,1,0,0,0,0]]
    unsigned int byte_count = schreib_segment + (schreib_element > 0 ? 1 : 0);
    
    fwrite(out_buffer, sizeof(char), byte_count, output_stream);
    
    // Nach dem Schreiben in den `output_stream`, soll der `out_buffer`
    // komplett "geleert" werden
    init_out();
}

extern bool has_next_char(void)
{
    return lese_segment < in_buffer_size;
}

extern bool has_next_bit(void)
{
    return lese_segment < in_buffer_size;
}

extern unsigned char read_char(void)
{
    unsigned char next_char = in_buffer[lese_segment];
    lese_segment++;
    
    if (lese_segment == in_buffer_size)
    {
        read_infile();
    }
    
    return next_char;
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
    
    if (lese_segment == in_buffer_size)
    {
        read_infile();
    }
    
    return next_bit;
}

extern void write_char(unsigned char c)
{
    out_buffer[schreib_segment] = c;
    schreib_segment++;
    
    if (schreib_segment == BUF_SIZE)
    {
        write_outfile();
    }
}

extern void write_bit(BIT c)
{
    out_buffer[schreib_segment] = PUT_BIT(out_buffer[schreib_segment], c, schreib_element);
    
    schreib_element++;
    
    // Wenn ein Byte mit Bits "vollgeschrieben" wurde
    if (schreib_element == BYTE_SIZE)
    {
        // dann wird das nächste Byte "gefüllt"
        schreib_segment++;
        schreib_element = 0;
    }
    
    // Wenn der out_buffer voll ist
    if (schreib_segment == BUF_SIZE)
    {
        // wird der Inhalt in den `output_stream` geschrieben
        write_outfile();
    }
}

extern void close_infile(void)
{
    fclose(input_stream);
}

extern void close_outfile(void)
{
    // Wenn noch etwas im out_buffer steht
    if (schreib_segment > 0 || schreib_element > 0)
    {
        // wird der restliche Inhalt in `output_stream` geschrieben
        write_outfile();
    }
    
    fclose(output_stream);
}
