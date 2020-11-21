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

int main(int argc, const char * argv[]) {
    
    printf("Hello, World!\n");
    return 0;
}
