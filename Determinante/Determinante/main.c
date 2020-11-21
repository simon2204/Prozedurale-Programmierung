//
//  main.c
//  Determinante
//
//  Created by Simon Schöpke on 13.11.20.
//

#include <stdio.h>

#define MAX_SIZE 10

/// Berechnet für eine n x n Matrix die Determinante,
/// wobei die Matrix eine maximale Größe von MAX_SIZE haben darf.
/// Liefert 0 bei ungüliger Eingabe.
/// @param matrix - Eingabe-Matrix.
/// @param size - Größe der Eingabe-Matrix
/// @return Determinante der Eingabe-Matrix.
double get_determinant(double matrix[MAX_SIZE][MAX_SIZE], int size);

/// Berechnet die Determinante einer 2 x 2 Matrix.
/// @param matrix - Eingabe-Matrix.
/// @return Determinante der Eingabe-Matrix.
double get_determinantFor2x2(double matrix[MAX_SIZE][MAX_SIZE]);

/// Stellt eine Matrix textuell dar.
/// @param matrix - Eingabe-Matrix.
/// @param size - Größe der Eingabe-Matrix
void print_matrix(double matrix[MAX_SIZE][MAX_SIZE], int size);

/// Verkleinert eine n x n Matrix in eine (n-1) x (n-1) Matrix,
/// durch entfernen einer übergebenen Zeile und Spalte,
/// wobei die Matrix eine maximale Größe von MAX_SIZE haben darf.
/// @param source - Ausgangs-Matrix, die verkleinert werden soll.
/// @param destination - Ziel-Matrix, die zurückgegeben wird.
/// @param size - Größe der Ausgangs-Matrix.
/// @param row - Nummer der zu entfernenden Zeile.
/// @param column - Nummer der zu entfernenden Spalte.
void reduce_matrix(double source[MAX_SIZE][MAX_SIZE],
                   double destination[MAX_SIZE][MAX_SIZE],
                   int size, int row, int column);


int main(int argc, const char * argv[])
{
    double matrix[MAX_SIZE][MAX_SIZE] =
    {
        {5.5, 1.0, 2.0},
        {3.0, 45.0, 1.0},
        {1.0, 1.0, 0.0}
    };

    int size = 3;

    printf("%f\n", get_determinant(matrix, size));

    return 0;
}

double get_determinant(double matrix[MAX_SIZE][MAX_SIZE], int size)
{
    int i;
    int sign = -1;
    double coefficient;
    double determinant = 0;
    double reduced_matrix[MAX_SIZE][MAX_SIZE];
    int reduced_matrix_size = size - 1;
    
    // Überprüfung auf ungültige Eingaben.
    if (size < 1 || size > MAX_SIZE)
    {
        return 0.0;
    }
    
    // Bei einer 1 × 1-Matrix wird das enthaltene Element zurückgegeben.
    if (size == 1)
    {
        return matrix[0][0];
    }
    
    // Bei einer 2 x 2-Matrix wird die Determinante direkt bestimmt.
    if (size == 2)
    {
        return get_determinantFor2x2(matrix);
    }
    
    // Es wird nach der 1. Zeile entwickelt.
    for (i = 0; i < size; i++)
    {
        // Erstellen der Matrix, die sich daraus ergibt,
        // wenn die 1. Zeile und die i-te Spalte wegfallen.
        reduce_matrix(matrix, reduced_matrix, size, 0, i);
        
        // Vorzeichenwechsel für die Faktoren, der (n-1) x (n-1)-Matrizen.
        sign *= -1;
        
        // Faktor einer Determinante.
        coefficient = matrix[0][i];
        
        // Rekursiver Aufruf zur Berechnung der Determinante.
        determinant += sign
                    * coefficient
                    * get_determinant(reduced_matrix,
                                      reduced_matrix_size);
    }
    
    return determinant;
}

double get_determinantFor2x2(double matrix[MAX_SIZE][MAX_SIZE])
{
    return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
}

void reduce_matrix(double source[MAX_SIZE][MAX_SIZE],
                   double destination[MAX_SIZE][MAX_SIZE],
                   int size, int row, int column)
{
    int s_row; /* Zeilennummer der Ausgangs-Matrix. */
    int s_column; /* Spaltennummer der Ausgangs-Matrix. */
    
    int d_row = 0; /* Zeilennummer der Ziel-Matrix. */
    int d_column = 0; /* Spaltennummer der Ziel-Matrix. */
    int d_columns_count = size - 1; /* Anzahl an Spalten der Ziel-Matrix. */

    // Es wird über alle Zellen der Ausgangs-Matrix iteriert.
    for (s_row = 0; s_row < size; s_row++)
    {
        for (s_column = 0; s_column < size; s_column++) {
            
            // Wenn sich die aktuelle Zelle nicht in der übergebenen
            // Zeile und auch nicht in der übergebenen Spalte befindet,
            // soll der Wert dieser Zelle der Ziel-Matrix übergeben werden.
            if (s_row != row && s_column != column)
            {
                destination[d_row][d_column] = source[s_row][s_column];
                
                // Erhöht die Spalte für die Ziel-Matrix um eins,
                // wenn ein neuer Wert in diese eingefügt wurde.
                // Überschreitet die Nummer der Spalte die Anzahl
                // der Spalten in der Ziel-Matrix, wird der Wert zurück auf 0 gesetzt.
                d_column = (d_column + 1) % d_columns_count;
                
                // Wenn die Spaltennummer wieder bei 0 beginnt,
                // wird die Zeilennummer für die Ziel-Matrix um 1 erhöht.
                if (d_column == 0)
                {
                    d_row = d_row + 1;
                }
            }
        }
    }
}

void print_matrix(double matrix[MAX_SIZE][MAX_SIZE], int size)
{
    int i;
    int j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            printf("%10.1f", matrix[i][j]);
        }
        printf("\n");
    }
}
