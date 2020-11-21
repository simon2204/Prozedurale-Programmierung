//
//  main.c
//  Bitmanipulation
//
//  Created by Simon Schöpke on 19.11.20.
//

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

void print_binary(unsigned char byte);
bool is_set(unsigned char byte, short pos);
unsigned char set_bit(unsigned char byte, short pos);
unsigned char delete_bit(unsigned char byte, short pos);
unsigned char invert_bits(unsigned char byte, short pos);
unsigned char rotate_bits(unsigned char byte, short count);
bool is_power_of_two(unsigned int n);

int main(int argc, const char * argv[]) {
    
    // Testing delete_bit
    assert(delete_bit(0b11011010, 0) == 0b11011010);
    assert(delete_bit(0b11011010, 1) == 0b11011000);
    assert(delete_bit(0b11011010, 2) == 0b11011010);
    assert(delete_bit(0b11011010, 3) == 0b11010010);
    assert(delete_bit(0b11011010, 4) == 0b11001010);
    assert(delete_bit(0b11011010, 5) == 0b11011010);
    assert(delete_bit(0b11011010, 6) == 0b10011010);
    assert(delete_bit(0b11011010, 7) == 0b01011010);
    
    // Testing invert_bits
    assert(invert_bits(0b11011010, 0) == 0b00100100);
    assert(invert_bits(0b11011010, 1) == 0b00100111);
    assert(invert_bits(0b11011010, 2) == 0b00100001);
    assert(invert_bits(0b11011010, 3) == 0b00101101);
    assert(invert_bits(0b11011010, 4) == 0b00110101);
    assert(invert_bits(0b11011010, 5) == 0b00000101);
    assert(invert_bits(0b11011010, 6) == 0b01100101);
    assert(invert_bits(0b11011010, 7) == 0b10100101);
    
    // Testing rotate_bits
    assert(rotate_bits(0b11011010, 0) == 0b11011010);
    assert(rotate_bits(0b11011010, 1) == 0b01101101);
    assert(rotate_bits(0b11011010, 2) == 0b10110110);
    assert(rotate_bits(0b11011010, 3) == 0b01011011);
    assert(rotate_bits(0b11011010, 4) == 0b10101101);
    assert(rotate_bits(0b11011010, 5) == 0b11010110);
    assert(rotate_bits(0b11011010, 6) == 0b01101011);
    assert(rotate_bits(0b11011010, 7) == 0b10110101);
    assert(rotate_bits(0b11011010, 8) == 0b11011010);
    
    // Testing is_power_of_two
    for (unsigned int i = 1; i <= 0x80000000u && i > 0; i *= 2)
    {
        assert(is_power_of_two(i));
    }
    assert(!is_power_of_two(0));
    assert(!is_power_of_two(3));
    assert(!is_power_of_two(5));
    assert(!is_power_of_two(6));
    assert(!is_power_of_two(36));
    assert(!is_power_of_two(100));
    
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
    return ~(0x01 << pos) & byte;
}

unsigned char invert_bits(unsigned char byte, short pos)
{
    return ~(0x01 << pos) ^ byte;
}

unsigned char rotate_bits(unsigned char byte, short count)
{
    return (byte >> count) | (byte << (8 - count));
}

bool is_power_of_two(unsigned int n)
{
    return ((n & (n - 1)) == 0) && (n != 0);
}
