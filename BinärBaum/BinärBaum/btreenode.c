//
//  btreenode.c
//  BinärBaum
//
//  Created by Simon Schöpke on 26.01.21.
//

#include <stdlib.h>
#include "btreenode.h"
#include "binary_tree_common.h"

extern BTREE_NODE *btreenode_new(void *data)
{
    BTREE_NODE *btree_node = malloc(sizeof(BTREE_NODE));
    ENSURE_ENOUGH_MEMORY(btree_node, "btreenode_new");
    btree_node->value = data;
    btree_node->left_child = NULL;
    btree_node->right_child = NULL;
    return btree_node;
}

extern BTREE_NODE *btreenode_clone(BTREE_NODE *node)
{
    void *btreenode = NULL;
    
    if (node != NULL)
    {
        btreenode = btreenode_new(node->value);
    }
    
    return btreenode;
}

extern bool btreenode_equals(BTREE_NODE *node1, BTREE_NODE *node2)
{
    return node1 != NULL && node2 != NULL
        && node1->value == node2->value;
}

extern void btreenode_destroy(BTREE_NODE **node,
                              DESTROY_DATA_FCT destroy_data)
{
    if (node != NULL && *node != NULL)
    {
        if (destroy_data != NULL)
        {
            destroy_data(&(*node)->value);
        }
        FREE_NULL(*node);
    }
}

extern void *btreenode_get_data(BTREE_NODE *node)
{
    void *data = NULL;
    
    if (node != NULL)
    {
        data = node->value;
    }
    
    return data;
}

extern BTREE_NODE *btreenode_get_left(BTREE_NODE *node)
{
    void *left_child = NULL;
    
    if (node != NULL)
    {
        left_child = node->left_child;
    }
    
    return left_child;
}

extern BTREE_NODE *btreenode_get_right(BTREE_NODE *node)
{
    void *right_child = NULL;
    
    if (node != NULL)
    {
        right_child = node->right_child;
    }
    
    return right_child;
}

extern bool btreenode_is_leaf(BTREE_NODE *node)
{
    return node != NULL
    && node->left_child == NULL
    && node->right_child == NULL;
}

extern bool btreenode_set_left(BTREE_NODE *parent_node, BTREE_NODE *node)
{
    bool can_set_left = parent_node != NULL
                    && parent_node->left_child == NULL;
    
    if (can_set_left)
    {
        parent_node->left_child = node;
    }
    
    return can_set_left;
}

extern bool btreenode_set_right(BTREE_NODE *parent_node, BTREE_NODE *node)
{
    bool can_set_right = parent_node != NULL
                    && parent_node->right_child == NULL;
    
    if (can_set_right)
    {
        parent_node->right_child = node;
    }
    
    return can_set_right;
}

extern void btreenode_print(BTREE_NODE *node, PRINT_DATA_FCT print_data)
{
    if (node != NULL && print_data != NULL)
    {
        print_data(node->value);
    }
}
