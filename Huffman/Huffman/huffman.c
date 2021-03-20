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

#define letter_count 256

/// Liest aus der Wurzel eines `BTREE`s, welche Werte des Typs `FREQUENCY` halten, den "frequency count" aus.
/// @param btree Der zu lesende `BTREE`.
/// @return Liefert den Wert, den die Funktion `frequency_get_count` zurück gibt.
static int btree_get_frequency_count(BTREE *btree);

/// Vergleicht zwei `BTREE`s miteinander, auf Basis der im Root enthaltenen Frequencies.
/// @param btree1 Der zu vergleichende `BTREE`.
/// @param btree2 Der zu vergleichende `BTREE`.
/// @return Liefert '-1', wenn btree1 kleiner ist als btree2. Wenn beide gleich groß sind '0' und wenn btree2 größer ist als btree1, dann '1'.
static int btree_cmp(BTREE *btree1, BTREE *btree2);

/// Erzeugt mit Hilfe der Funktion `create_huffman_table_recusive` aus einem `huffman_tree` den `huffman_table`.
/// Jedes der 256 Felder steht für einen bestimmten Wert in der Ascii-Tabelle und jedes verwendete Feld beinhaltet den Code,
/// der verwendet wird, um einen Text zu komprimieren.
/// @param huffman_table Die Ausgabe des huffman tables.
/// @param huffman_tree Der Baum, ausdem `huffman_table` erstellt wird.
static void create_huffman_table(unsigned char *huffman_table[letter_count], BTREE *huffman_tree);

/// Erzeugt durch rekursive Aufrufe den huffman table.
/// @param node Der als nächstes zu lesende Baumknoten.
/// @param code Der erstellte Huffmancode.
/// @param huffman_table Ausgabe des Huffman Tabelle.
static void create_huffman_table_recusive(BTREE_NODE *node, DYN_STRING *code, unsigned char *huffman_table[letter_count]);

/// Erzeugt die Tabelle, die die Häufigkeiten der jeweiligen im Text vorkommenden zeichen angibt.
/// @param frequency_table Gibt eine Häufigkeitstabelle zurück.
/// @param frequency_count Gibt die Anzahl der "besetzten" Plätze in der Häufigkeitstabelle an.
static void create_frequency_table(struct FREQUENCY *frequency_table[letter_count], unsigned int *frequency_count);

/// Schreibt `frequency_table` in die Ausgabedatei.
/// @param frequency_table Die Tabelle, die in die Ausgabedatei geschrieben werden soll.
static void write_frequency_table(struct FREQUENCY *frequency_table[letter_count]);

/// Erzeugt eine Häufigkeitstabelle aus einer bereits komprimierten Datei.
/// @param frequency_table Ausgabe der Häufigkeitstabelle.
static void create_frequency_table_from_data(struct FREQUENCY *frequency_table[letter_count]);

/// Legt die Häufigkeiten in einen Heap ab.
/// @param frequency_table Tabelle, aus der die Häufigkeiten gelesen werden.
static void create_heap(struct FREQUENCY *frequency_table[letter_count]);

/// Erzeugt aus dem erstellten Heap den Huffman-Tree.
/// @return Liefert den erzeugten Huffman-Tree, der genutzt wird, um zu dekomprimieren.
static BTREE *create_huffman_tree(void);

/// Schreibt den komprimierten Text mit Hilfe der Huffman Tabelle in die Ausgabedatei.
/// @param huffman_table Die zum Komprimieren verwendet wird.
static void write_compressed_text(unsigned char *huffman_table[letter_count]);

/// Schreibt den dekomprimierten Text mit Hilfe des Huffman-Baumes in die Ausgabedatei.
/// @param huffman_tree Der zum Dekomprimieren verwendet wird.
/// @param null_byte_count Anzahl der '\0' characters im Text.
static void write_decompressed_text(BTREE *huffman_tree, unsigned int null_byte_count);


extern void compress(char in_filename[], char out_filename[])
{
    open_infile(in_filename);
    open_outfile(out_filename);

    struct FREQUENCY *frequency_table[letter_count] = {NULL};
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

    unsigned char *huffman_table[letter_count] = {NULL};
    
    create_huffman_table(huffman_table, huffman_tree);
    
    write_compressed_text(huffman_table);
    
    close_infile();
    close_outfile();
    
    heap_destroy();
    btree_destroy(&huffman_tree, true);
}

extern void decompress(char in_filename[], char out_filename[])
{
    open_infile(in_filename);
    open_outfile(out_filename);
    
    struct FREQUENCY *frequency_table[letter_count] = {NULL};
    
    create_frequency_table_from_data(frequency_table);
    
    create_heap(frequency_table);
    
    BTREE *huffman_tree = create_huffman_tree();
    
    unsigned int null_byte_count = frequency_get_count(frequency_table['\0']);
    
    write_decompressed_text(huffman_tree, null_byte_count);
    
    close_infile();
    close_outfile();
    
    btree_destroy(&huffman_tree, true);
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

static void create_huffman_table(unsigned char *huffman_table[letter_count], BTREE *huffman_tree)
{
    if (huffman_tree != NULL)
    {
        DYN_STRING *code = dynstring_create();
        create_huffman_table_recusive(btree_get_root(huffman_tree), code, huffman_table);
    }
}

static void create_huffman_table_recusive(BTREE_NODE *node, DYN_STRING *code, unsigned char *huffman_table[letter_count])
{
    BTREE_NODE *left = btreenode_get_left(node);
    BTREE_NODE *right = btreenode_get_right(node);
    
    if (btreenode_is_leaf(node))
    {
        unsigned char character = btreenode_get_frequency_word(node);
        huffman_table[character] = (unsigned char*) dynstring_get_text(code);
        dynstring_destroy(&code, false);
        return;
    }
    
    if (left != NULL)
    {
        DYN_STRING *code_copy = dynstring_copy(code);
        dynstring_append_character('0', code_copy);
        create_huffman_table_recusive(left, code_copy, huffman_table);
    }
    
    if (right != NULL)
    {
        DYN_STRING *code_copy = dynstring_copy(code);
        dynstring_append_character('1', code_copy);
        create_huffman_table_recusive(right, code_copy, huffman_table);
    }
    
    dynstring_destroy(&code, true);
}

static void write_frequency_table(struct FREQUENCY *frequency_table[letter_count])
{
    int i;
    struct FREQUENCY *frequency;
    
    for (i = 0; i < letter_count; i++)
    {
        frequency = frequency_table[i];
        
        if (frequency != NULL)
        {
            write_char(frequency_get_char(frequency));
            write_int(frequency_get_count(frequency));
        }
    }
}

static void create_frequency_table(struct FREQUENCY *frequency_table[letter_count], unsigned int *frequency_count)
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

static void create_frequency_table_from_data(struct FREQUENCY *frequency_table[letter_count])
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

static void create_heap(struct FREQUENCY *frequency_table[letter_count])
{
    int i;
    BTREE *btree;
    
    heap_init((HEAP_ELEM_COMP) btree_cmp, (HEAP_ELEM_PRINT) frequency_print);

    for (i = 0; i < letter_count; i++)
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

static void write_code(unsigned char *code)
{
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

static void write_compressed_text(unsigned char *huffman_table[letter_count])
{
    unsigned char character;
    
    while (has_next_char())
    {
        character = read_char();
        write_code(huffman_table[character]);
    }
    
    write_code(huffman_table['\0']);
}

static void write_decompressed_text(BTREE *huffman_tree, unsigned int null_byte_count)
{
    BTREE_NODE *current_node = btree_get_root(huffman_tree);
    
    struct FREQUENCY *frequency;
    
    unsigned char current_char;
    
    while (has_next_bit())
    {
        if (read_bit() == ZERO)
        {
            current_node = btreenode_get_left(current_node);
        }
        else
        {
            current_node = btreenode_get_right(current_node);
        }
        
        if (btreenode_is_leaf(current_node))
        {
            frequency = btreenode_get_data(current_node);
            current_char = frequency_get_char(frequency);
            
            if (current_char == '\0')
            {
                null_byte_count--;
            }
            
            if (null_byte_count > 0)
            {
                write_char(current_char);
                current_node = btree_get_root(huffman_tree);
            }
            else
            {
                break;
            }
        }
    }
}
