/**
 * @file bubblesort
 * 
 * Das Modul stellt eine Funktion zum Sortieren von int-Vektoren nach dem 
 * Bubble-Sort zur Verfügung. 
 */

/* ============================================================================
 * Includes
 * ========================================================================= */

#include <stdlib.h>
#include <stdio.h>

/* ============================================================================
 * Konstanten
 * ========================================================================= */

#define MAX_SIZE 50

/* ============================================================================
 * Funktionsprototypen
 * ========================================================================= */

/**
 * Die Funktion sortiert die Elemente des Vektors a aufsteigen. Zum Sortieren
 * wird der Bubble-Sort eingesetzt.
 * 
 * @param a         zu sortierender Vektor
 * @param length    Anzahl der Elemente im Vektor a
 */
void bubblesort(int *a, int length);

/* ============================================================================
 * Funktionsdefinitionen
 * ========================================================================= */

void bubblesort(int *a, int length)
{
    int i;
    int j;
    for (i = 0; i < length - 1; i++) 
    {
        for (j = 0; j < length - i - 1; j++) 
        {
            if (a[j] > a[j + 1]) 
            {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
}

/* ============================================================================
 * Für Testzwecke
 * ========================================================================= */

/**
 * Testet die Funktion bubblesort
 * 
 * @return 
 */
int main_v1(void)
{
    int i;
    
    printf("\nBubblesort (v1)\n");
        
    {
        int ints[] = {1,9,2,8,4,5,6,3,7,0};
        int size = 10;

        bubblesort(ints, size);
    
        for (i = 0; i < size; i++)
        {
            printf("%d ", ints[i]);
        }
        printf("\n");
    }
    
    return (EXIT_SUCCESS);
}