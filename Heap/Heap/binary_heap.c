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

#define HAS_LEFT_CHILD(INDEX) (LEFT_CHILD_INDEX(INDEX) < count)
#define HAS_RIGHT_CHILD(INDEX) (RIGHT_CHILD_INDEX(INDEX) < count)
#define HAS_PARENT(INDEX) (PARENT_INDEX(INDEX) >= 0)

#define LEFT_CHILD(INDEX) items[LEFT_CHILD_INDEX(INDEX)]
#define RIGHT_CHILD(INDEX) items[RIGHT_CHILD_INDEX(INDEX)]
#define PARENT(INDEX) items[PARENT_INDEX(INDEX)]

#define SWAP_ITEMS(IDX1, IDX2) void *temp = items[IDX1]; items[IDX1] = items[IDX2]; items[IDX2] = temp;

#define IS_ROOT(INDEX) (INDEX == 0)

/* ============================================================================
 * Symbolische Konstanten
 * ========================================================================= */

#define INITIAL_CAPACITY 4
#define MSG_NOT_ENOUGH_MEMORY "ERROR: nicht genügend Speicher vorhanden\n"

/* ============================================================================
 * Typdefinitionen
 * ========================================================================= */

typedef bool (*HEAP_ELEM_COMP) (void* first_element, void* second_element);

/* ============================================================================
 * Funktionsprototypen
 * ========================================================================= */

static void heap_expand(void);

static void heap_shrink(void);

static void heap_upwards(int start_idx);

static void heap_downwards(int start_idx);

/* ============================================================================
 * Globale Variablen
 * ========================================================================= */

static unsigned int capacity = INITIAL_CAPACITY;
static unsigned int count = 0;
static void **items;

static HEAP_ELEM_COMP are_in_increasing_order;

/* ============================================================================
 * Funktionsdefinitionen
 * ========================================================================= */

extern void heap_init(HEAP_ELEM_COMP comp)
{
    items = malloc(INITIAL_CAPACITY * sizeof(void *));
    if (items == NULL)
    {
        printf(MSG_NOT_ENOUGH_MEMORY);
        exit(EXIT_FAILURE);
    }
    are_in_increasing_order = comp;
}

extern void heap_destroy(void)
{
    free(items);
    items = NULL;
    capacity = INITIAL_CAPACITY;
    count = 0;
}

extern void heap_insert(void *element)
{
    if (count == capacity)
    {
        heap_expand();
    }
    items[count] = element;
    heap_upwards(count);
    count++;
}

extern bool heap_extract_min(void **min_element)
{
    bool can_extract_min = count > 0;
    
    if (can_extract_min && ((count << 2) == capacity))
    {
        heap_shrink();
    }
    
    if (can_extract_min)
    {
        min_element = items[0];
        count--;
        items[0] = items[count];
        heap_downwards(0);
    }
    
    return can_extract_min;
}

static void heap_upwards(int start_idx)
{
    int parent_index;
    
    if (IS_ROOT(start_idx))
    {
        return;
    }
    
    parent_index = PARENT_INDEX(start_idx);
    
    if (are_in_increasing_order(items[start_idx], PARENT(start_idx)))
    {
        SWAP_ITEMS(start_idx, parent_index)
        heap_upwards(parent_index);
    }
}

static void heap_downwards(int start_idx)
{
    void *parent = items[start_idx];
    void *left_child;
    void *right_child;
    
    if (HAS_RIGHT_CHILD(start_idx))
    {
        left_child = LEFT_CHILD(start_idx);
        right_child = RIGHT_CHILD(start_idx);
        
        if (are_in_increasing_order(left_child, right_child))
        {
            if (are_in_increasing_order(left_child, parent))
            {
                SWAP_ITEMS(LEFT_CHILD_INDEX(start_idx), start_idx)
                heap_downwards(LEFT_CHILD_INDEX(start_idx));
            }
        }
        else
        {
            if (are_in_increasing_order(right_child, parent))
            {
                SWAP_ITEMS(RIGHT_CHILD_INDEX(start_idx), start_idx)
                heap_downwards(RIGHT_CHILD_INDEX(start_idx));
            }
        }
    }
    else if (HAS_LEFT_CHILD(start_idx))
    {
        if (are_in_increasing_order(LEFT_CHILD(start_idx), parent))
        {
            SWAP_ITEMS(LEFT_CHILD_INDEX(start_idx), start_idx)
            heap_downwards(LEFT_CHILD_INDEX(start_idx));
        }
    }
}

static void heap_expand(void)
{
    capacity <<= 1;
    items = realloc(items, capacity);
    if (items == NULL)
    {
        printf(MSG_NOT_ENOUGH_MEMORY);
        exit(EXIT_FAILURE);
    }
}

static void heap_shrink(void)
{
    capacity >>= 1;
    items = realloc(items, capacity);
    if (items == NULL)
    {
        printf(MSG_NOT_ENOUGH_MEMORY);
        exit(EXIT_FAILURE);
    }
}
