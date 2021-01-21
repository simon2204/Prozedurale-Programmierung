//
//  main.c
//  Bubblesort
//
//  Created by Simon Schöpke on 06.01.21.
//

#include <stdio.h>

#define MAX_LENGTH 100

void bubblesort_v2(int **a, int length)
{
    int i;
    int j;
    for (i = 0; i < length - 1; i++)
    {
        for (j = 0; j < length - i - 1; j++)
        {
            if (*a[j] > *a[j + 1])
            {
                int *tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
}

void init_ptrs_v2(int **ptrs, int *ints, int count)
{
    int i;
    for (i = 0; i < count; i++)
    {
        ptrs[i] = &ints[i];
    }
}

int main(int argc, const char * argv[]) {
    
    int ints[] = {1,9,2,8,4,5,6,3,7,0};
    int count = 10;
    int i;
    
    int *ptrs[MAX_LENGTH] = {NULL};
    init_ptrs_v2(ptrs, ints, count);
    
    bubblesort_v2(ptrs, count);
    for (i = 0; i < count; i++)
    {
        printf("%d ", *ptrs[i]);
    }
    printf("\n");

    return 0;
}
