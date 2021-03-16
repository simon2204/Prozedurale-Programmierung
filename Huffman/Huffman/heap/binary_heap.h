//
//  binary_heap.h
//  Heap
//
//  Created by Simon Schöpke on 22.01.21.
//

#ifndef binary_heap_h
#define binary_heap_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* ============================================================================
 * Typdefinitionen
 * ========================================================================= */

typedef int (*HEAP_ELEM_COMP) (void* first_element, void* second_element);

typedef void (*HEAP_ELEM_PRINT) (void* element);

/* ============================================================================
 * Funktionsprototypen
 * ========================================================================= */

/// Initialisiert den Heap.
extern void heap_init(HEAP_ELEM_COMP comp, HEAP_ELEM_PRINT print);

/// Löscht den Heap, d.h., sie gibt den Speicher frei.
extern void heap_destroy(void);

/// Fügt ein neues Element in den Heap ein und sorgt dafür, dass die Heap-Eigenschaft aufrechterhalten bleibt.
extern void heap_insert(void *element);

/// Entfernt das kleinste Element aus dem Heap und liefert es im Parameter min_element zurück.
extern bool heap_extract_min(void **min_element);

/// Gibt den Heap auf dem Bildschirm aus.
extern void heap_print(void);

#endif /* min_heap_h */
