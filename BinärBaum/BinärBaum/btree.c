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
        clone->root->left_child = btreenode_clone(tree->root->left_child);
        clone->root->right_child = btreenode_clone(tree->root->right_child);
    }
    
    return clone;
}


extern void btree_destroy(BTREE **tree, bool destroy_data)
{
    if (tree != NULL && *tree != NULL)
    {
        btreenode_destroy(&((*tree)->root), destroy_data ? (*tree)->destroy_data : NULL);
        FREE_NULL(*tree);
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
        return btreenode_equals(tree1->root, tree2->root);
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
        btreenode_print(tree->root, tree->print_data);
    }
}
