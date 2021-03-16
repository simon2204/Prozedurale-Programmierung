//
//  io.h
//  Huffman
//
//  Created by Simon Schöpke on 03.12.20.
//

/**
 * @file
 *
 * In diesem Modul werden die Funktionen zum byte- sowie bitweisen Lesen und Schreiben definiert.
 *
 * @author Simon Schöke
 * @date   2020-12-03
 */

#ifndef io_h
#define io_h

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "huffman_common.h"
#include "argument_parser.h"

/// Öffnet die Eingabedatei `in_filename`
extern void open_infile(char in_filename[]);

/// Öffnet die Ausgabedatei `out_filename`
extern void open_outfile(char out_filename[]);

/// Schließt die zuvor geöffnete Datei von `open_infile`
extern void close_infile(void);

/// Schließt die zuvor geöffnete Datei von `open_outfile`
extern void close_outfile(void);

/// Gibt an, ob noch weitere Zeichen aus dem Eingabepuffer mit read_char gelesen werden können.
/// @return liefert true, wenn sich noch ein weiteres Zeichen zum Lesen im Eingabepuffer befindet.
extern bool has_next_char(void);

/// Liefert mit jedem Aufruf das nächste Zeichen aus dem Eingabepuffer.
/// Darf nur aufgerufen werden, wenn noch ein weiteres Zeichen vorhanden ist.
/// @return liefert das nächste Zeichen.
extern unsigned char read_char(void);

/// Schreibt den Wert von 'c' an die nächste freie Position in den Ausgabepuffer.
/// @param c - Das Zeichen, welches an die nächste freie Position des Ausgabepuffers geschrieben werden soll.
extern void write_char(unsigned char c);

/// Gibt an, ob noch weitere Bits aus dem Eingabepuffer gelesen werden können.
/// @return liefert true, wenn sich noch ein weiteres Bit zum Lesen im Eingabepuffer befindet.
extern bool has_next_bit(void);

/// Liefert mit jedem Aufruf das nächste Bit aus dem Eingabepuffer.
/// @return liefert das nächste Bit.
extern BIT read_bit(void);

/// Schreibt den Wert von 'c' an die nächste freie Position in den Ausgabepuffer.
/// @param c - Das Bit, welches an die nächste freie Position des Ausgabepuffers geschrieben werden soll.
extern void write_bit(BIT c);

extern unsigned int read_int(void);

extern void write_int(unsigned int i);

#endif /* io_h */
