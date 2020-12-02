//
//  main.c
//  Conway’s Game of Life
//
//  Created by Simon Schöpke on 21.11.20.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

enum neighbour: int {
    topLeft, topRight,
    bottomLeft, bottomRight,
    top, bottom,
    left, right,
    all_neighbours
};

// MARK: Required functions

void print_generation(void);
void set_generation_from_string(char string[]);
void get_generation_as_string(char string[]);
bool set_next_generation(void);
void game_of_life(int max_generations);

// MARK: Custom functions

char char_in_field(short row, short column);
bool is_set(short index, unsigned char generation[]);
bool is_set_for_cell(short row, short column, unsigned char generation[]);
bool is_set_for_neighbour(enum neighbour n, short center_index, unsigned char generation[]);
void set_bit(short index, unsigned char generation[]);
void set_bit_for_field(short row, short column);
void delete_bit(short index, unsigned char generation[]);
void delete_bit_for_field(short row, short column);
short count_neighbours(short index, unsigned char generation[]);

#define ALL_ROWS 10
#define ALL_COLS 10
#define ALL_CELLS (ALL_ROWS * ALL_COLS)
#define ALL_CELLS_IN_BYTE (ALL_CELLS / 8)
#define SEGMENTS (ALL_CELLS_IN_BYTE + 1)

unsigned char generation[SEGMENTS];
unsigned char generation_copy[SEGMENTS];

// MARK: MAIN

int main(int argc, const char * argv[]) {
    
    char glider[] =
    "0000000100"
    "0000000101"
    "0010000110"
    "0010100000"
    "0011000000"
    "0000000000"
    "0000000000"
    "0000000000"
    "0000000000"
    "0000000000";
    
    char sonne[] =
    "0001100000"
    "0010010000"
    "0100001000"
    "1000000100"
    "1000000100"
    "0100001000"
    "0010010000"
    "0001100000"
    "0000000000"
    "0000000000";
    
    set_generation_from_string(glider);
    print_generation();
    game_of_life(500000);
    
    return 0;
}

// MARK: Initialisierung

void game_of_life(int max_generations)
{
    int i;
    bool isMutating = true;
    for (i = 0; i < max_generations && isMutating; i++)
    {
        isMutating = set_next_generation();
        system("clear");
        printf("%d\n", i);
        print_generation();
        usleep(1000000 / 3);
    }
}

bool set_next_generation()
{
    bool did_mutate = false;
    short n_count;
    int i;
    int j;
    
    for(j = 0; j < SEGMENTS; j++)
    {
        generation_copy[j] = generation[j];
    }
    
    for (i = 0; i < ALL_CELLS; i++)
    {
        n_count = count_neighbours(i, generation_copy);
        
        if (is_set(i, generation_copy))
        {
            if (n_count < 2 || n_count > 3)
            {
                delete_bit(i, generation);
                did_mutate = true;
            }
        }
        else
        {
            if (n_count == 3)
            {
                set_bit(i, generation);
                did_mutate = true;
            }
        }
    }
    
    return did_mutate;
}

void set_generation_from_string(char string[ALL_CELLS])
{
    int i = 0;
    char charakter = string[i];
    while (charakter != '\0')
    {
        if (charakter == '0')
        {
            delete_bit(i, generation);
        }
        else
        {
            set_bit(i, generation);
        }
        
        i++;
        charakter = string[i];
    }
}

void get_generation_as_string(char string[ALL_CELLS])
{
    int i;
    for (i = 0; i < ALL_CELLS; i++)
    {
        string[i] = is_set(i, generation) ? '1' : '0';
    }
}

// MARK: Set and delete Bit

void delete_bit(short index, unsigned char generation[SEGMENTS])
{
    if (index < 0 || index >= ALL_CELLS)
    {
        return;
    }
    short segment = index / 8;
    short element = index % 8;
    generation[segment] &= ~(0x80u >> element);
}

void set_bit(short index, unsigned char generation[SEGMENTS])
{
    if (index < 0 || index >= ALL_CELLS)
    {
        return;
    }
    short segment = index / 8;
    short element = index % 8;
    generation[segment] |= (0x80u >> element);
}

// MARK: Is bit set?

bool is_set(short index, unsigned char generation[SEGMENTS])
{
    if (index < 0 || index >= ALL_CELLS)
    {
        return false;
    }
    short segment = index / 8;
    short element = index % 8;
    return ((0x80u >> element) & generation[segment]) > 0;
}

bool is_set_for_cell(short row, short column, unsigned char generation[SEGMENTS])
{
    if (row < 0 || column < 0 || row >= ALL_ROWS || column >= ALL_COLS)
    {
        return false;
    }
    return is_set((row * ALL_COLS) + column, generation);
}

bool is_set_for_neighbour(enum neighbour n, short center_index, unsigned char generation[])
{
    short row = center_index / ALL_COLS;
    short column = center_index % ALL_COLS;
    switch (n) {
        case topLeft:
            return is_set_for_cell(row - 1, column - 1, generation);
        case topRight:
            return is_set_for_cell(row - 1, column + 1, generation);
        case bottomLeft:
            return is_set_for_cell(row + 1, column - 1, generation);
        case bottomRight:
            return is_set_for_cell(row + 1, column + 1, generation);
        case top:
            return is_set_for_cell(row - 1, column + 0, generation);
        case bottom:
            return is_set_for_cell(row + 1, column + 0, generation);
        case left:
            return is_set_for_cell(row + 0, column - 1, generation);
        case right:
            return is_set_for_cell(row + 0, column + 1, generation);
        default:
            return false;
    }
}

// MARK: Count neighbours

short count_neighbours(short center_index, unsigned char generation[SEGMENTS])
{
    short n_count = 0;
    enum neighbour n;
    
    for (n = 0; n < all_neighbours; n++)
    {
        if (is_set_for_neighbour(n, center_index, generation))
        {
            n_count++;
        }
    }
    
    return n_count;
}

// MARK: Print Generation

void print_generation()
{
    int i;
    int j;
    for (i = 0; i < ALL_COLS; i++)
    {
        printf("+---");
    }
    
    if (ALL_COLS > 0)
    {
        printf("+\n");
    }
    
    for (i = 0; i < ALL_ROWS; i++)
    {
        for (j = 0; j < ALL_COLS; j++)
        {
            printf("| %c ", char_in_field(i, j));
        }
        printf("|\n");
        
        for (j = 0; j < ALL_COLS; j++)
        {
            printf("+---");
        }
        printf("+\n");
    }
}

char char_in_field(short row, short column)
{
    return is_set_for_cell(row, column, generation) ? 'o' : ' ';
}
