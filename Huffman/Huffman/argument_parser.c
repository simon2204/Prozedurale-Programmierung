//
//  argument_parser.c
//  Huffman
//
//  Created by Simon Schöpke on 09.01.21.
//

#include "argument_parser.h"

static bool c;
static bool d;
static bool v;
static bool h;
static int l;
static char *o;
static char *filename;

extern void parse_argv(int argc, char **argv)
{
    c = false;
    d = false;
    v = false;
    h = false;
    l = 2;
    o = NULL;
    filename = NULL;
    
    int i;
    
    for (i = 1; i < argc; i++)
    {
        // Start einer Option
        if (*argv[i] == '-')
        {
            // Wenn nach einem '-' das Ende erreicht wurde
            if (*(argv[i] + 1) == '\0')
            {
                printf("Nach '-' wird eine Option erwartet.\n");
                exit(COMMANDLINEARGUMENT_ERROR);
            }
            
            switch (*(argv[i] + 1)) {
                case 'c':
                    c = true;
                    d = false;
                    break;
                case 'd':
                    d = true;
                    c = false;
                    break;
                case 'v':
                    v = true;
                    break;
                case 'h':
                    h = true;
                    break;
                case 'l':
                    // Erster Character nach '-l'
                    l = *(argv[i] + 2);
                    
                    // Wenn nach '-l' nichts mehr folgt.
                    if (l == '\0')
                    {
                        printf("Es wurde kein Argument für <level> übergeben.\n");
                        exit(COMMANDLINEARGUMENT_ERROR);
                    }
                    // Wenn das Argument von '-l' nicht zwischen '1' und '9' liegt
                    // oder wenn das Argument zweistellig ist
                    if (l < '1' || l > '9' || *(argv[i] + 3) != '\0')
                    {
                        printf("<level> muss zwischen 1 und 9 liegen.\n");
                        exit(COMMANDLINEARGUMENT_ERROR);
                    }
                    break;
                case 'o':
                    // Wenn es nach '-o' ein weiteres Argument gibt
                    if (i + 1 < argc)
                    {
                        o = argv[i + 1];
                    }
                    // Beim nächsten Durchlauf soll das Argument von '-o' übersprungen werden.
                    i++;
                    // 
                    if (o != NULL && *o == '-')
                    {
                        printf("Es wurde kein Argument für <outfile> übergeben.\n");
                        exit(COMMANDLINEARGUMENT_ERROR);
                    }
                    break;
                default:
                    printf("Ungültige Option '-%c'.\n", *(argv[i] + 1));
                    exit(COMMANDLINEARGUMENT_ERROR);
                    break;
            }
        }
        else
        {
            if (filename != NULL)
            {
                printf("'%s' wurde bereits als Name der Eingabedatei übergeben.\n", filename);
                exit(COMMANDLINEARGUMENT_ERROR);
            }
            filename = argv[i];
        }
    }
    
    if (filename == NULL)
    {
        printf("Es wurde kein Argument für <filename> übergeben.\n");
        exit(COMMANDLINEARGUMENT_ERROR);
    }
    
    if (o != NULL && strcmp(o, filename) == 0)
    {
        printf("<outfile> und <filename> dürfen nicht den selben Namen haben.\n");
        exit(COMMANDLINEARGUMENT_ERROR);
    }
    
    if (!c && !d)
    {
        printf("Es muss mindestens '-c' oder '-d' als Option übergeben werden.\n");
        exit(COMMANDLINEARGUMENT_ERROR);
    }
}
