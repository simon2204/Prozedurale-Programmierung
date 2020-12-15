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

/// Initialisiert den internen Eigabepuffer mit 'text'.
/// @param text - Der zu initialisiertende Text.
extern void init_in(char text[]);

/// Leert den Ausgabepuffer.
extern void init_out(void);

/// Der Ausgabepuffer wird Ausgelesen und in den Vektor 'text' kopiert.
/// @param text - Ausgabeparameter des Ausgabepuffers.
extern void get_out_buffer(char text[]);

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
extern enum BIT read_bit(void);

/// Schreibt den Wert von 'c' an die nächste freie Position in den Ausgabepuffer.
/// @param c - Das Bit, welches an die nächste freie Position des Ausgabepuffers geschrieben werden soll.
extern void write_bit(enum BIT c);

#endif /* io_h */
