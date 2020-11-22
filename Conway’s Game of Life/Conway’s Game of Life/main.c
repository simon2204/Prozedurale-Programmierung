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

bool is_set(short pos);
char char_in_field(short row, short column);
void set_bit(short pos);
void delete_bit(short pos);
void invert_bits(short pos);
void rotate_bits(short count);
bool is_power_of_two(unsigned int n);

#define ALL_ROWS 5
#define ALL_COLS 6
#define ALL_FIELDS (ALL_ROWS * ALL_COLS)

unsigned long long generation;

int main(int argc, const char * argv[]) {
    
    set_generation_from_string("111000001000010111000100000010");
    char string[ALL_ROWS * ALL_COLS];
    
    get_generation_as_string(string);
    printf("%s\n", string);
        
    print_generation();
        
    return 0;
}

void set_generation_from_string(char string[ALL_ROWS * ALL_COLS])
{
    int i = 0;
    char charakter = string[i];
    while (charakter != '\0') {
        generation <<= 1;
        if (charakter == '1')
        {
            generation |= 0x1;
        }
        i++;
        charakter = string[i];
    }
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
            printf("| %c\t", char_in_field(i, j));
        }
        printf("|\n");
        
        for (int j = 0; j < ALL_COLS; j++)
        {
            printf("+---");
        }
        printf("+\n");
    }
}

bool set_next_generation()
{
    return false;
}

void get_generation_as_string(char string[ALL_ROWS * ALL_COLS]) {
    unsigned long long generationCopy = generation;
    for (int i = ALL_FIELDS - 1; i >= 0; i--)
    {
        string[i] = (generationCopy & 0x1) > 0 ? '1' : '0';
        generationCopy >>= 1;
    }
}

char char_in_field(short row, short column)
{
    short pos = (row * ALL_COLS) + column;
    pos = (ALL_FIELDS - 1) - pos;
    return is_set(pos) ? 'o' : ' ';
}

bool is_set(short pos)
{
    return ((0x01 << pos) & generation) > 0;
}

void set_bit(short pos)
{
    generation = (0x01 << pos) | generation;
}

void delete_bit(short pos)
{
    generation = ~(0x01 << pos) & generation;
}

void invert_bits(short pos)
{
    generation = ~(0x01 << pos) ^ generation;
}

void rotate_bits(short count)
{
    generation = (generation >> count) | (generation << (64 - count));
}

bool is_power_of_two(unsigned int n)
{
    return ((n & (n - 1)) == 0) && (n != 0);
}
