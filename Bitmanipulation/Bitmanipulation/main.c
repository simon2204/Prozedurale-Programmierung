//
//  main.c
//  Bitmanipulation
//
//  Created by Simon Schöpke on 19.11.20.
//

#include <stdio.h>
#include <stdbool.h>

void print_binary(unsigned char byte);
bool is_set(unsigned char byte, short pos);
unsigned char set_bit(unsigned char byte, short pos);
unsigned char delete_bit(unsigned char byte, short pos);
unsigned char invert_bits(unsigned char byte, short pos);
unsigned char rotate_bits(unsigned char byte, short count);
bool is_power_of_two(unsigned int n);

int main(int argc, const char * argv[]) {
    
    return 0;
}

void print_binary(unsigned char byte)
{
    for (unsigned char mask = 0x80u; mask > 0; mask >>= 1)
    {
        printf("%d", ((byte & mask) == mask) ? 1 : 0);
    }
    printf("\n");
}

bool is_set(unsigned char byte, short pos)
{
    return ((0x01 << pos) & byte) > 0;
}

unsigned char set_bit(unsigned char byte, short pos)
{
    return (0x01 << pos) | byte;
}

unsigned char delete_bit(unsigned char byte, short pos)
{
    return ((0x01 << pos) ^ (0xFFu)) & byte;
}

unsigned char invert_bits(unsigned char byte, short pos)
{
    return ((0x01 << pos) ^ (0xFFu)) ^ byte;
}

unsigned char rotate_bits(unsigned char byte, short count)
{
    return (byte >> count) | (byte << (8 - count));
}

bool is_power_of_two(unsigned int n)
{
    return ((n & (n - 1)) == 0) && (n != 0);
}
