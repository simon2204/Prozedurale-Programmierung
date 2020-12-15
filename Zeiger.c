Aufgabe 6.1 (Umgang mit Zeigern)

a) Welchen Fehler enthält das folgende Code-Fragment?
1 int ival;
2 int *ptr;
3 ptr = ival; // ptr = &ival;
4 *ptr = 255;


b) Welche Werte werden mit den beiden printf-Anweisungen in den Zeilen 7 und 8 ausgegeben?
1 int *ptr = NULL;
2 int ival;
3 ptr = &ival;
4 ival = 9876;
5 *ptr = 1234;
6
7 printf("%d\n", *ptr); // Prints "1234"
8 printf("%d\n", ival); // Prints "1234"


c) Was geben die printf-Anweisungen in den Zeilen 10 bis 14 aus?
1 int vector[] = {12, 34, 56, 78, 90, 23, 45};
2 int *ptr1;
3 int *ptr2;
4
5 ptr1 = vector;     // *ptr1: 12
6 ptr2 = &vector[4]; // *ptr2: 90
7 ptr1 += 2;         // *ptr1: 56
8 ptr2++;            // *ptr2: 23
9
10 printf("%d\n", *ptr1);         // Prints "56"
11 printf("%d\n", *ptr2);         // Prints "23"
12 printf("%d\n", ptr2 - ptr1);   // Prints "3"
13 printf("%d\n", ptr1 < ptr2);   // Prints "1"
14 printf("%d\n", *ptr1 < *ptr2); // Prints "0"


d) Das folgende Listing soll in einem String einen bestimmten Buchstaben suchen und
ab dieser Fundstelle eine Adresse auf dem String zurückgeben. Im Beispiel wird
mit dem Aufruf der Funktion search() im String "Hallo Welt!" nach dem
Buchstaben ’W’ gesucht. Die Funktion gibt den String ab der Anfangsadresse
von ’W’ zurück. Im Beispiel müsste die printf-Ausgabe somit Welt! lauten.
Es werden allerdings nur unsinnige Zeichen ausgegeben.
Wo liegt der Fehler? Wie würden Sie den Fehler korrigieren?

1   #define MAX 10
2
3   char *search(char *text, char c)
4   {
5     char buffer[MAX] = "";
6     int i = 0;
7
8     while (text[i] != '\0' && text[i] != c)
9     {
10      i++;
11    }
12    strncpy(buffer, &text[i], MAX);
13
14    return buffer;
15  }
16
17  int main(void)
18  {
19    char *text = search("Hallo Welt!", 'W');
20    printf("%s\n", text);
21
22    return EXIT_SUCCESS;
23  }

// Lösungsvorschlag:
char *search(char *text, char c)
{
    while (*text != '\0' && *text != c)
    {
        text++;
    }

    return text;
}

int main(void)
{
    char *text = search("Hallo Welt!", 'W');
    printf("%s\n", text);
    return 0;
}


e) Wo ist der Unterschied zwischen den folgenden beiden Deklarationen?
// Elemente können verändert werden.
// Feste Größe des Vektors.
// Keine neue Zuweisung eines Strings möglich.
1 char str1[] = "Hallo Welt!";

// Kann durch Zuweisung auf einen anderen String zeigen, der belibig lang sein darf.
// Elemente können nicht verändert werden.
2 char *str2 = "Hallo Welt!";

Aufgabe 6.2 (Effizienz durch Zeigerarithmetik)
Betrachten Sie die beiden folgenden Funktionen, die beide über die Elemente des Vektors
'vector' iterieren und diese mit 0 belegen.

#define MAX 100
int vector[MAX];

void initUsingIndexoperator(void)
{
    int i;

    for (i = 0; i < MAX; i++)
    {
        // Es wird immer wieder von der Startadresse von 'vector' ausgegangen
        // und der Index 'i' wird aufaddiert.
        vector[i] = 0; // *(vector + i) = 0;
    }
}

void initUsingPointer(void)
{
    int i;
    int *p = vector;

    for (i = 0; i < MAX; i++)
    {
        // Es wird immer von der vorherigen Startadresse ausgegangen.
        *p = 0;
        p++;
    }
}
