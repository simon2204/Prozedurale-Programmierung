//
//  btreenode.c
//  BinärBaum
//
//  Created by Simon Schöpke on 26.01.21.
//

#include <stdlib.h>
#include "btreenode.h"
#include "binary_tree_common.h"

struct _BTREE_NODE {
    void *value;
    struct _BTREE_NODE *left_child;
    struct _BTREE_NODE *right_child;
};

static void btreenode_clone_recursive(BTREE_NODE *node1, BTREE_NODE *node2);
static void btreenode_print_preoder(BTREE_NODE *node, PRINT_DATA_FCT print_data, unsigned int depth);

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
        btreenode_clone_recursive(node, btreenode);
    }
    
    return btreenode;
}

static void btreenode_clone_recursive(BTREE_NODE *node1, BTREE_NODE *node2)
{
    if (node1->left_child != NULL)
    {
        node2->left_child = btreenode_clone(node1->left_child);
        btreenode_clone_recursive(node1->left_child, node2->left_child);
    }
    
    if (node1->right_child != NULL)
    {
        node2->right_child = btreenode_clone(node1->right_child);
        btreenode_clone_recursive(node1->right_child, node2->right_child);
    }
}

extern bool btreenode_equals(BTREE_NODE *node1, BTREE_NODE *node2)
{
    if (node1 == NULL && node2 == NULL)
    {
        return true;
    }
    
    if (node1 != NULL && node2 != NULL)
    {
        return node1->value == node2->value
        && btreenode_equals(node1->left_child, node2->left_child)
        && btreenode_equals(node1->right_child, node2->right_child);
    }
    
    return false;
}

extern void btreenode_destroy(BTREE_NODE **node,
                              DESTROY_DATA_FCT destroy_data)
{
    if (node != NULL && *node != NULL)
    {
        btreenode_destroy(&((*node)->left_child), destroy_data);
        btreenode_destroy(&((*node)->right_child), destroy_data);
        
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
        btreenode_print_preoder(node, print_data, 0);
    }
}

static void btreenode_print_preoder(BTREE_NODE *node, PRINT_DATA_FCT print_data, unsigned int depth)
{
    int i;
    
    for (i = 0; i < depth; i++)
    {
        printf("\t");
    }
    
    if (node->value != NULL)
    {
        printf("|-- ");
        print_data(node->value);
        printf("\n");
    }
    
    if (node->left_child != NULL)
    {
        btreenode_print_preoder(node->left_child, print_data, depth + 1);
    }
    
    if (node->right_child != NULL)
    {
        btreenode_print_preoder(node->right_child, print_data, depth + 1);
    }
}
