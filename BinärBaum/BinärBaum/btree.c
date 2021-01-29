//
//  btree.c
//  BinärBaum
//
//  Created by Simon Schöpke on 26.01.21.
//

#include "btree.h"
#include <stdlib.h>

extern BTREE *btree_new(void *data,
                        DESTROY_DATA_FCT destroy_data,
                        PRINT_DATA_FCT print_data)
{
    BTREE *btree = malloc(sizeof(BTREE));
    // ENSURE_ENOUGH_MEMORY(list, "linked_list_create");
    btree->root = NULL;
}

extern BTREE *btree_clone(BTREE *tree)
{
    
}

extern void btree_destroy(BTREE **tree, bool destroy_data)
{
    
}

extern bool btree_equals(BTREE *tree1, BTREE *tree2)
{
    
}

extern BTREE_NODE *btree_get_root(BTREE *tree)
{
    
}

extern BTREE *btree_merge(BTREE *left, BTREE *right, void *data)
{
    
}

extern void btree_print(BTREE *tree)
{
    
}
