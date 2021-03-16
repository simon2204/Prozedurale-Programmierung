//
//  dyn_string.h
//  Huffman
//
//  Created by Simon Schöpke on 15.03.21.
//

#ifndef dyn_string_h
#define dyn_string_h

#include <stdio.h>
#include <stdbool.h>

typedef struct _DYN_STRING DYN_STRING;

DYN_STRING *dynstring_create(void);

void dynstring_destroy(DYN_STRING **dynstring, bool destroy_text);

void dynstring_append_character(char character, DYN_STRING *dynstring);

DYN_STRING *dynstring_copy(DYN_STRING *dynstring);

char *dynstring_get_text(DYN_STRING *dynstring);

#endif /* dyn_string_h */
