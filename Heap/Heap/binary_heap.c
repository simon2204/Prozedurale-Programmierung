//
//  binary_heap.c
//  Heap
//
//  Created by Simon Schöpke on 22.01.21.
//

/* ============================================================================
 * Header-Dateien
 * ========================================================================= */

#include "binary_heap.h"

/* ============================================================================
 * Makros
 * ========================================================================= */

#define LEFT_CHILD_INDEX(PARENT_INDEX) (2 * PARENT_INDEX + 1)
#define RIGHT_CHILD_INDEX(PARENT_INDEX) (2 * PARENT_INDEX + 2)
#define PARENT_INDEX(CHILD_INDEX) ((CHILD_INDEX - 1) / 2)

#define HAS_LEFT_CHILD(INDEX) (INDEX < count)
#define HAS_RIGHT_CHILD(INDEX) (INDEX < count)

#define LEFT_CHILD(INDEX) elements[INDEX]
#define RIGHT_CHILD(INDEX) elements[INDEX]
#define PARENT(INDEX) elements[INDEX]

#define SWAP_ELEMENTS(IDX1, IDX2) {void *temp = elements[IDX1]; elements[IDX1] = elements[IDX2]; elements[IDX2] = temp;}

#define ARE_IN_INCREASING_ORDER(FIRST, SECOND) (cmp(FIRST, SECOND) == -1)

#define IS_ROOT(INDEX) (INDEX == 0)

/* ============================================================================
 * Symbolische Konstanten
 * ========================================================================= */

#define INITIAL_CAPACITY 4
#define MSG_NOT_ENOUGH_MEMORY "ERROR: nicht genügend Speicher vorhanden\n"

/* ============================================================================
 * Funktionsprototypen
 * ========================================================================= */

static void heap_expand(void);

static void heap_shrink(void);

static void heap_swim(int start_idx);

static void heap_sink(int start_idx);

/* ============================================================================
 * Globale Variablen
 * ========================================================================= */

static unsigned int capacity = INITIAL_CAPACITY;
static unsigned int count = 0;
static void **elements;
static HEAP_ELEM_COMP cmp;
static HEAP_ELEM_PRINT print_element;

static void *parent;
static void *child;
static void *left_child;
static void *right_child;
static unsigned int parent_idx;
static unsigned int child_idx;
static unsigned int left_child_idx;
static unsigned int right_child_idx;

/* ============================================================================
 * Funktionsdefinitionen
 * ========================================================================= */

extern void heap_init(HEAP_ELEM_COMP comp, HEAP_ELEM_PRINT print)
{
    elements = malloc(INITIAL_CAPACITY * sizeof(void *));
    if (elements == NULL)
    {
        printf(MSG_NOT_ENOUGH_MEMORY);
        exit(EXIT_FAILURE);
    }
    cmp = comp;
    print_element = print;
}

extern void heap_destroy(void)
{
    free(elements);
    elements = NULL;
    capacity = INITIAL_CAPACITY;
    count = 0;
}

extern void heap_insert(void *element)
{
    if (count == capacity)
    {
        heap_expand();
    }
    elements[count] = element;
    heap_swim(count);
    count++;
}

extern bool heap_extract_min(void **min_element)
{
    bool can_extract_min = count > 0;
    
    if (can_extract_min && (count == (capacity >> 2)))
    {
        heap_shrink();
    }
    
    if (can_extract_min)
    {
        *min_element = elements[0];
        count--;
        elements[0] = elements[count];
        heap_sink(0);
    }
    
    return can_extract_min;
}

static void heap_swim(int start_idx)
{
    if (IS_ROOT(start_idx))
    {
        return;
    }
    
    parent_idx = PARENT_INDEX(start_idx);
    child_idx = start_idx;
    child = elements[start_idx];
    
    if (ARE_IN_INCREASING_ORDER(child, PARENT(parent_idx)))
    {
        SWAP_ELEMENTS(child_idx, parent_idx)
        heap_swim(parent_idx);
    }
}

static void heap_sink(int start_idx)
{
    parent = elements[start_idx];
    parent_idx = start_idx;
    left_child_idx = LEFT_CHILD_INDEX(parent_idx);
    right_child_idx = RIGHT_CHILD_INDEX(parent_idx);
    
    // Wenn es ein rechtes Kind gibt, dann gibt es auch ein linkes.
    if (HAS_RIGHT_CHILD(right_child_idx))
    {
        left_child = LEFT_CHILD(left_child_idx);
        right_child = RIGHT_CHILD(right_child_idx);
        
        if (ARE_IN_INCREASING_ORDER(left_child, right_child)
            && ARE_IN_INCREASING_ORDER(left_child, parent))
        {
            SWAP_ELEMENTS(left_child_idx, parent_idx)
            heap_sink(left_child_idx);
        }
        else if (ARE_IN_INCREASING_ORDER(right_child, parent))
        {
            SWAP_ELEMENTS(right_child_idx, parent_idx)
            heap_sink(right_child_idx);
        }
    }
    else if (HAS_LEFT_CHILD(left_child_idx)
             && ARE_IN_INCREASING_ORDER(LEFT_CHILD(left_child_idx), parent))
    {
        SWAP_ELEMENTS(left_child_idx, parent_idx)
        heap_sink(left_child_idx);
    }
}

static void heap_expand(void)
{
    capacity <<= 1;
    elements = realloc(elements, capacity * sizeof(void *));
    if (elements == NULL)
    {
        printf(MSG_NOT_ENOUGH_MEMORY);
        exit(EXIT_FAILURE);
    }
}

static void heap_shrink(void)
{
    capacity >>= 1;
    elements = realloc(elements, capacity * sizeof(void *));
    if (elements == NULL)
    {
        printf(MSG_NOT_ENOUGH_MEMORY);
        exit(EXIT_FAILURE);
    }
}

extern void heap_print(void)
{
    printf("heap_print is not yet implemented");
}
