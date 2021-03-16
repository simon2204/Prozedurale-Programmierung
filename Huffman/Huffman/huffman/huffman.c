//
//  Huffman.c
//  Huffman
//
//  Created by Simon Schöpke on 03.12.20.
//

#include "huffman.h"
#include "frequency.h"
#include "binary_heap.h"
#include "btree.h"
#include "btreenode.h"
#include "dyn_string.h"

static int btree_get_frequency_count(BTREE *btree);

static int btree_cmp(BTREE *btree1, BTREE *btree2);

static void create_huffman_table(unsigned char *bits[], BTREE *btree);

static void create_huffman_table_recusive(BTREE_NODE *node, DYN_STRING *code, unsigned char *bits[]);

static void write_frequency_table(struct FREQUENCY *table[256]);

static void create_frequency_table(struct FREQUENCY *frequency_table[256], unsigned int *frequency_count);

static void create_frequency_table_from_data(struct FREQUENCY *frequency_table[256]);

static void create_heap(struct FREQUENCY *frequency_table[256]);

static BTREE *create_huffman_tree(void);

static void write_compressed_text(unsigned char *huffman_table[256]);

extern void compress(char in_filename[], char out_filename[])
{
    clock_t prg_start;
    clock_t prg_end;

    prg_start = clock();

    open_infile(in_filename);
    open_outfile(out_filename);

    struct FREQUENCY *frequency_table[256] = {NULL};
    unsigned int frequency_count;
    
    struct FREQUENCY *end_of_file = frequency_create('\0', 1);
    
    frequency_table['\0'] = end_of_file;
    
    create_frequency_table(frequency_table, &frequency_count);
    
    frequency_count++;
    
    write_int(frequency_count);
    
    write_frequency_table(frequency_table);
    
    close_infile();
    
    open_infile(in_filename);
    
    create_heap(frequency_table);
    
    BTREE *huffman_tree = create_huffman_tree();

    unsigned char *huffman_table[256] = {NULL};
    
    create_huffman_table(huffman_table, huffman_tree);
    
    write_compressed_text(huffman_table);
    
    close_infile();
    close_outfile();
    
    heap_destroy();
    btree_destroy(&huffman_tree, true);
    
    prg_end = clock();
    
    if (wants_verbose_info())
    {
        printf(" - Die Laufzeit betrug %.2f Sekunden\n",
        (float) (prg_end - prg_start) / CLOCKS_PER_SEC);
    }
}

extern void decompress(char in_filename[], char out_filename[])
{
    clock_t prg_start;
    clock_t prg_end;
    
    prg_start = clock();
    
    open_infile(in_filename);
    open_outfile(out_filename);
    
    struct FREQUENCY *frequency_table[256] = {NULL};
    
    create_frequency_table_from_data(frequency_table);
    
    create_heap(frequency_table);
    
    BTREE *huffman_tree = create_huffman_tree();
    
    BTREE_NODE *current_node = btree_get_root(huffman_tree);
    
    while (has_next_bit())
    {
        if (btreenode_is_leaf(current_node))
        {
            struct FREQUENCY *frequency = btreenode_get_data(current_node);
            
            unsigned char current_char = frequency_get_char(frequency);
            
            if (current_char == '\0')
            {
                break;
            }
            else
            {
                write_char(current_char);
                current_node = btree_get_root(huffman_tree);
            }
        }
        
        if (read_bit() == ZERO)
        {
            current_node = btreenode_get_left(current_node);
        }
        else
        {
            current_node = btreenode_get_right(current_node);
        }
    }
    
    close_infile();
    close_outfile();
    
    btree_destroy(&huffman_tree, true);
    
    prg_end = clock();
    
    if (wants_verbose_info())
    {
        printf(" - Die Laufzeit betrug %.2f Sekunden\n",
        (float) (prg_end - prg_start) / CLOCKS_PER_SEC);
    }
}

static int btree_get_frequency_count(BTREE *btree)
{
    if (btree == NULL)
    {
        return 0;
    }
    
    BTREE_NODE *btree_root_node = btree_get_root(btree);
    struct FREQUENCY *frequency = btreenode_get_data(btree_root_node);
    return frequency_get_count(frequency);
}

static unsigned char btreenode_get_frequency_word(BTREE_NODE *node)
{
    if (node == NULL)
    {
        return 0;
    }
    
    struct FREQUENCY *frequency = btreenode_get_data(node);
    return frequency_get_char(frequency);
}

static int btree_cmp(BTREE *btree1, BTREE *btree2)
{
    BTREE_NODE *btree_root_node1 = btree_get_root(btree1);
    BTREE_NODE *btree_root_node2 = btree_get_root(btree2);
    struct FREQUENCY *data1 = btreenode_get_data(btree_root_node1);
    struct FREQUENCY *data2 = btreenode_get_data(btree_root_node2);
    return frequency_compare(data1, data2);
}

static void create_huffman_table(unsigned char *huffman_table[], BTREE *huffman_tree)
{
    if (huffman_tree != NULL)
    {
        DYN_STRING *code = dynstring_create();
        create_huffman_table_recusive(btree_get_root(huffman_tree), code, huffman_table);
    }
}

static void create_huffman_table_recusive(BTREE_NODE *node, DYN_STRING *code, unsigned char *bits[])
{
    BTREE_NODE *left = btreenode_get_left(node);
    BTREE_NODE *right = btreenode_get_right(node);
    
    if (btreenode_is_leaf(node))
    {
        unsigned char character = btreenode_get_frequency_word(node);
        bits[character] = (unsigned char*) dynstring_get_text(code);
        dynstring_destroy(&code, false);
        return;
    }
    
    if (left != NULL)
    {
        DYN_STRING *code_copy = dynstring_copy(code);
        dynstring_append_character('0', code_copy);
        create_huffman_table_recusive(left, code_copy, bits);
    }
    
    if (right != NULL)
    {
        DYN_STRING *code_copy = dynstring_copy(code);
        dynstring_append_character('1', code_copy);
        create_huffman_table_recusive(right, code_copy, bits);
    }
    
    dynstring_destroy(&code, true);
}

static void write_frequency_table(struct FREQUENCY *table[256])
{
    int i;
    struct FREQUENCY *frequency;
    
    for (i = 0; i < 256; i++)
    {
        frequency = table[i];
        
        if (frequency != NULL)
        {
            write_char(frequency_get_char(frequency));
            write_int(frequency_get_count(frequency));
        }
    }
}

static void create_frequency_table(struct FREQUENCY *frequency_table[256], unsigned int *frequency_count)
{
    unsigned int count = 0;
    
    while (has_next_char())
    {
        unsigned char character = read_char();
        
        if (frequency_table[character] == NULL)
        {
            frequency_table[character] = frequency_create(character, 1);
            count++;
        }
        else
        {
            frequency_increase_by_one(frequency_table[character]);
        }
    }
    
    *frequency_count = count;
}

static void create_frequency_table_from_data(struct FREQUENCY *frequency_table[256])
{
    int i;
    
    unsigned int frequency_tuple_count = read_int();
    
    unsigned char character;
    unsigned int frequency_count;
    
    for (i = 0; i < frequency_tuple_count; i++)
    {
        character = read_char();
        frequency_count = read_int();
        
        struct FREQUENCY *frequency = frequency_create(character, frequency_count);
        frequency_table[character] = frequency;
    }
}

static void create_heap(struct FREQUENCY *frequency_table[256])
{
    int i;
    BTREE *btree;
    
    heap_init((HEAP_ELEM_COMP) btree_cmp, (HEAP_ELEM_PRINT) frequency_print);

    for (i = 0; i < 256; i++)
    {
        if (frequency_table[i] != NULL)
        {
            btree = btree_new(frequency_table[i],
                              (DESTROY_DATA_FCT) frequency_destroy,
                              (PRINT_DATA_FCT) frequency_print);
            heap_insert(btree);
        }
    }
}

static BTREE *create_huffman_tree(void)
{
    void *btree1 = NULL;
    void *btree2 = NULL;
    BTREE *huffman_tree = NULL;
    
    int sum;
    struct FREQUENCY *frequency;

    while (heap_extract_min(&btree1) && heap_extract_min(&btree2))
    {
        sum = btree_get_frequency_count(btree1) + btree_get_frequency_count(btree2);
        frequency = frequency_create('\0', sum);
        BTREE *merged = btree_merge(btree1, btree2, frequency);
        heap_insert(merged);
    }
    
    if (btree_get_frequency_count(btree1) > btree_get_frequency_count(btree2))
    {
        huffman_tree = btree1;
    }
    else
    {
        huffman_tree = btree2;
    }
    
    return huffman_tree;
}

static void write_compressed_text(unsigned char *huffman_table[256])
{
    unsigned char character;
    unsigned char *code;
    
    while (has_next_char())
    {
        character = read_char();
        code = huffman_table[character];

        while (*code != '\0')
        {
            if (*code == '0')
            {
                write_bit(ZERO);
            }
            else
            {
                write_bit(ONE);
            }
            code++;
        }
    }
    
    character = '\0';
    code = huffman_table[character];
    
    while (*code != '\0')
    {
        if (*code == '0')
        {
            write_bit(ZERO);
        }
        else
        {
            write_bit(ONE);
        }
        code++;
    }
}
