//
//  justify_line.h
//  Blocksatzformatierung
//
//  Created by Simon Schöpke on 28.12.20.
//

#ifndef justify_line_h
#define justify_line_h

/// Maximale Länge einer Zeile.
#define MAX_LINE_LENGTH 100

/// Formatiert eine Ausgangszeile mit einer entsprechenden Zielzeilenlänge in eine blocksatzformatierte Zeile.
/// @param p_line Pointer zur Zeile, die formatiert werden soll.
/// @param target_line_length Zielzeilenlänge
/// @param p_justified_line Formatierte Zeile als Rückgabe.
extern void justify_line(char *p_line, int target_line_length, char *p_justified_line);

#endif /* justify_line_h */
