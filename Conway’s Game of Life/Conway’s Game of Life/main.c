//
//  main.c
//  Conway’s Game of Life
//
//  Created by Simon Schöpke on 21.11.20.
//

#include <stdio.h>
#include <stdbool.h>

void print_generation(void);
void set_generation_from_string(char string[]);
void get_generation_as_string(char string[]);
bool set_next_generation(void);
void game_of_life(int max_generations);

char char_in_field(short row, short column);
bool is_set(unsigned char generation[], short pos);
bool is_set_for_field(unsigned char generation[], short row, short column);
void set_bit(unsigned char generation[], short pos);
void set_bit_for_field(short row, short column);
void delete_bit(unsigned char generation[], short pos);
void delete_bit_for_field(short row, short column);
short neighbours_count(unsigned char generation[], short pos);

#define ALL_ROWS 5
#define ALL_COLS 6
#define ALL_FIELDS (ALL_ROWS * ALL_COLS)
#define ALL_FIELDS_IN_BYTE (ALL_FIELDS / 8)
#define SEGMENTS (ALL_FIELDS_IN_BYTE + 1)

#define UP -1
#define DOWN 1
#define LEFT -1
#define RIGHT 1
#define ZERO 0

unsigned char generation[SEGMENTS];

int main(int argc, const char * argv[]) {
    
    set_generation_from_string("111000001000010111000100000010");
    game_of_life(5000);
    
    return 0;
}

void game_of_life(int max_generations)
{
    int i;
    int j;
    bool isMutating = true;
    for (i = 0; i < max_generations && isMutating; i++)
    {
        isMutating = set_next_generation();
        printf("%d\n", i);
        print_generation();
        for(j = 0; j < 100000000; j++);
    }
}

bool set_next_generation()
{
    unsigned char generation_copy[SEGMENTS];
    short n_count;
    int i;
    int j;
    
    for(j = 0; j < SEGMENTS; j++)
    {
        generation_copy[j] = generation[j];
    }
    
    for (i = 0; i < ALL_FIELDS; i++)
    {
        n_count = neighbours_count(generation_copy, i);
        
        if (is_set(generation_copy, i))
        {
            if (n_count < 2 || n_count > 3)
            {
                delete_bit(generation, i);
                return true;
            }
        }
        else
        {
            if (n_count == 3)
            {
                set_bit(generation, i);
                return true;
            }
        }
    }
    
    return false;
}

void set_generation_from_string(char string[ALL_FIELDS])
{
    int i = 0;
    char charakter = string[i];
    while (charakter != '\0')
    {
        if (charakter == '0') {
            delete_bit(generation, i);
        }
        else
        {
            set_bit(generation, i);
        }
        
        i++;
        charakter = string[i];
    }
}

void get_generation_as_string(char string[ALL_FIELDS]) {
    for (int i = 0; i < ALL_FIELDS; i++)
    {
        printf("%c", is_set(generation, i) ? '1' : '0');
    }
    printf("\n");
}

void delete_bit(unsigned char generation[SEGMENTS], short pos)
{
    if (pos < 0 || pos >= ALL_FIELDS) { return; }
    short segment = pos / 8;
    short element = pos % 8;
    generation[segment] &= ~(0x80u >> element);
}

void set_bit(unsigned char generation[SEGMENTS], short pos)
{
    if (pos < 0 || pos >= ALL_FIELDS) { return; }
    short segment = pos / 8;
    short element = pos % 8;
    generation[segment] |= (0x80u >> element);
}

bool is_set(unsigned char generation[SEGMENTS], short pos)
{
    if (pos < 0 || pos >= ALL_FIELDS)
    {
        return false;
    }
    short segment = pos / 8;
    short element = pos % 8;
    return ((0x80u >> element) & generation[segment]) > 0;
}

bool is_set_for_field(unsigned char generation[SEGMENTS], short row, short column)
{
    if (row < 0 || column < 0 || row >= ALL_ROWS || column >= ALL_COLS)
    {
        return false;
    }
    return is_set(generation, (row * ALL_COLS) + column);
}

short neighbours_count(unsigned char generation[SEGMENTS], short pos)
{
    short row_directions[]    = {   UP, ZERO,   UP,   UP,  DOWN,  ZERO, DOWN,  DOWN };
    short column_directions[] = { ZERO, LEFT, LEFT, RIGHT, ZERO, RIGHT, LEFT, RIGHT };
    short own_row = pos / (ALL_COLS);
    short own_column = pos % (ALL_COLS);
    short count = 0;
    int i;
    
    for (i = 0; i < 9; i++)
    {
        if (is_set_for_field(generation, own_row + row_directions[i], own_column + column_directions[i]))
        {
            count++;
        }
    }
    
    return count;
}

char char_in_field(short row, short column)
{
    return is_set_for_field(generation, row, column) ? 'o' : ' ';
}

void print_generation()
{
    for (int j = 0; j < ALL_COLS; j++)
    {
        printf("+---");
    }
    
    if (ALL_COLS > 0)
    {
        printf("+\n");
    }
    
    for (int i = 0; i < ALL_ROWS; i++)
    {
        for (int j = 0; j < ALL_COLS; j++)
        {
            printf("| %c ", char_in_field(i, j));
        }
        printf("|\n");
        
        for (int j = 0; j < ALL_COLS; j++)
        {
            printf("+---");
        }
        printf("+\n");
    }
}
