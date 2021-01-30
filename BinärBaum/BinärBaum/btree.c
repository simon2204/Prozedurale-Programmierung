//
//  btree.c
//  BinärBaum
//
//  Created by Simon Schöpke on 26.01.21.
//

#include <stdlib.h>
#include "btree.h"
#include "binary_tree_common.h"
#include "btreenode.h"

static void btree_print_preoder(BTREE_NODE *node, PRINT_DATA_FCT print_data, unsigned int depth);
static bool btree_equals_recursive(BTREE_NODE *node1, BTREE_NODE *node2);
static void btree_destroy_recursive(BTREE_NODE **node, DESTROY_DATA_FCT destroy_data);
static void btree_clone_recursive(BTREE_NODE *node1, BTREE_NODE *node2);

extern BTREE *btree_new(void *data,
                        DESTROY_DATA_FCT destroy_data,
                        PRINT_DATA_FCT print_data)
{
    BTREE *btree = malloc(sizeof(BTREE));
    ENSURE_ENOUGH_MEMORY(btree, "btree_new");
    btree->root = btreenode_new(data);
    btree->destroy_data = destroy_data;
    btree->print_data = print_data;
    return btree;
}

extern BTREE *btree_clone(BTREE *tree)
{
    BTREE *clone = NULL;
    
    if (tree != NULL && tree->root != NULL)
    {
        clone = btree_new(tree->root->value, tree->destroy_data, tree->print_data);
        btree_clone_recursive(tree->root, clone->root);
    }
    
    return clone;
}

static void btree_clone_recursive(BTREE_NODE *node1, BTREE_NODE *node2)
{
    if (node1->left_child != NULL)
    {
        node2->left_child = btreenode_clone(node1->left_child);
        btree_clone_recursive(node1->left_child, node2->left_child);
    }
    
    if (node1->right_child != NULL)
    {
        node2->right_child = btreenode_clone(node1->right_child);
        btree_clone_recursive(node1->right_child, node2->right_child);
    }
}

extern void btree_destroy(BTREE **tree, bool destroy_data)
{
    if (tree != NULL && *tree != NULL)
    {
        btree_destroy_recursive(&((*tree)->root), destroy_data ? (*tree)->destroy_data : NULL);
        FREE_NULL(*tree);
    }
}

static void btree_destroy_recursive(BTREE_NODE **node, DESTROY_DATA_FCT destroy_data)
{
    if (node != NULL && *node != NULL)
    {
        btree_destroy_recursive(&((*node)->left_child), destroy_data);
        btree_destroy_recursive(&((*node)->right_child), destroy_data);
        
        if (destroy_data != NULL)
        {
            destroy_data(&(*node)->value);
        }
        
        free(*node);
        *node = NULL;
    }
}

extern bool btree_equals(BTREE *tree1, BTREE *tree2)
{
    if (tree1 == NULL && tree2 == NULL)
    {
        return true;
    }
    
    if (tree1 != NULL && tree2 != NULL)
    {
        return btree_equals_recursive(tree1->root, tree2->root);
    }
    
    return false;
}

static bool btree_equals_recursive(BTREE_NODE *node1, BTREE_NODE *node2)
{
    if (node1 == NULL && node2 == NULL)
    {
        return true;
    }
    
    if (node1 != NULL && node2 != NULL)
    {
        return node1->value == node2->value
        && btree_equals_recursive(node1->left_child, node2->left_child)
        && btree_equals_recursive(node1->right_child, node2->right_child);
    }
    
    return false;
}

extern BTREE_NODE *btree_get_root(BTREE *tree)
{
    BTREE_NODE *root = NULL;
    
    if (tree != NULL)
    {
        root = tree->root;
    }
    
    return root;
}

extern BTREE *btree_merge(BTREE *left, BTREE *right, void *data)
{
    BTREE *merge = NULL;
    
    if (left != NULL && right != NULL)
    {
        merge = btree_new(data, left->destroy_data, left->print_data);
        merge->root->left_child = left->root;
        merge->root->right_child = right->root;
        free(left);
        free(right);
    }
    
    return merge;
}

extern void btree_print(BTREE *tree)
{
    if (tree != NULL && tree->print_data != NULL)
    {
        btree_print_preoder(tree->root, tree->print_data, 0);
    }
}

static void btree_print_preoder(BTREE_NODE *node, PRINT_DATA_FCT print_data, unsigned int depth)
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
        btree_print_preoder(node->left_child, print_data, depth + 1);
    }
    
    if (node->right_child != NULL)
    {
        btree_print_preoder(node->right_child, print_data, depth + 1);
    }
}
