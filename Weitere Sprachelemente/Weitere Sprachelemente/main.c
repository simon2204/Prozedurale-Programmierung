//
//  main.c
//  Weitere Sprachelemente
//
//  Created by Simon Schöpke on 27.01.21.
//

#include <stdio.h>
#include <stdarg.h>

typedef union {
    int int_wert;
    char char_vektor[4];
} HI;

double average(int n1, ...);

int main(int argc, const char * argv[])
{
    int i;
    HI hi;
    
    hi.int_wert = 0x11223344;
    
    for (i = 0; i < 4; i++)
    {
        printf("%2x\n", hi.char_vektor[i]);
    }
    
    for (i = 0; i < 4; i++)
    {
        hi.char_vektor[i] = i;
    }
    
    printf("%d\n", hi.int_wert);
    
    double avg = average(2, -1, -1);
    
    printf("%f\n", avg);
    
    return 0;
}


double average(int n1, ...)
{
    int count = 1;
    int sum = n1;
    
    va_list p_args;
    
    int current_number;
    
    va_start(p_args, n1);
    
    while ((current_number = va_arg(p_args, int)) != -1)
    {
        sum += current_number;
        count++;
    }
    
    va_end(p_args);

    return (double) sum / count;
}
