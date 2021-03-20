//
//  dyn_string.c
//  Huffman
//
//  Created by Simon Schöpke on 15.03.21.
//

#include "dyn_string.h"
#include <stdlib.h>
#include <string.h>

#define END_OF_STRING '\0'

struct _DYN_STRING
{
    char *text;
    int size;
};

DYN_STRING *dynstring_create(void)
{
    DYN_STRING *dyn_string = malloc(sizeof(struct _DYN_STRING));
    dyn_string->text = malloc(sizeof(char));
    *(dyn_string->text) = END_OF_STRING;
    dyn_string->size = 1;
    return dyn_string;
}

void dynstring_destroy(DYN_STRING **dynstring, bool destroy_text)
{
    if (dynstring != NULL && *dynstring != NULL)
    {
        if (destroy_text)
        {
            free((*dynstring)->text);
        }
        free(*dynstring);
        *dynstring = NULL;
    }
}

void dynstring_append_character(char character, DYN_STRING *dynstring)
{
    if (dynstring != NULL)
    {
        int new_size = dynstring->size + 1;
        dynstring->text = realloc(dynstring->text, new_size * sizeof(char));
        dynstring->text[dynstring->size - 1] = character;
        dynstring->text[dynstring->size] = END_OF_STRING;
        dynstring->size = new_size;
    }
}

DYN_STRING *dynstring_copy(DYN_STRING *dynstring)
{
    DYN_STRING *dynstring_copy = NULL;
    
    if (dynstring != NULL)
    {
        dynstring_copy = malloc(sizeof(struct _DYN_STRING));
        dynstring_copy->text = malloc(dynstring->size * sizeof(char));
        dynstring_copy->size = dynstring->size;
        strcpy(dynstring_copy->text, dynstring->text);
    }
    
    return dynstring_copy;
}

char *dynstring_get_text(DYN_STRING *dynstring)
{
    char *text = NULL;
    
    if (dynstring != NULL)
    {
        text = dynstring->text;
    }
    
    return text;
}
