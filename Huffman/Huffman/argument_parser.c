//
//  argument_parser.c
//  Huffman
//
//  Created by Simon Schöpke on 09.01.21.
//

#include "argument_parser.h"

static bool compress;
static bool decompress;
static bool verbose;
static bool help;
static int level;
static char *outfile;
static char *filename;

extern void parse_argv(int argc, char **argv)
{
    compress = false;
    decompress = false;
    verbose = false;
    help = false;
    level = 2;
    outfile = NULL;
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
                    compress = true;
                    decompress = false;
                    break;
                case 'd':
                    decompress = true;
                    compress = false;
                    break;
                case 'v':
                    verbose = true;
                    break;
                case 'h':
                    help = true;
                    break;
                case 'l':
                    // Erster Character nach '-l'
                    level = *(argv[i] + 2);
                    
                    // Wenn nach '-l' nichts mehr folgt.
                    if (level == '\0')
                    {
                        printf("Es wurde kein Argument für <level> übergeben.\n");
                        exit(COMMANDLINEARGUMENT_ERROR);
                    }
                    // Wenn das Argument von '-l' nicht zwischen '1' und '9' liegt
                    // oder wenn das Argument zweistellig ist
                    if (level < '1' || level > '9' || *(argv[i] + 3) != '\0')
                    {
                        printf("<level> muss zwischen 1 und 9 liegen.\n");
                        exit(COMMANDLINEARGUMENT_ERROR);
                    }
                    break;
                case 'o':
                    // Wenn es nach '-o' ein weiteres Argument gibt
                    if (i + 1 < argc)
                    {
                        outfile = argv[i + 1];
                    }
                    // Beim nächsten Durchlauf soll das Argument von '-o' übersprungen werden.
                    i++;
                    // 
                    if (outfile != NULL && *outfile == '-')
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
    
    if (outfile != NULL && strcmp(outfile, filename) == 0)
    {
        printf("<outfile> und <filename> dürfen nicht den selben Namen haben.\n");
        exit(COMMANDLINEARGUMENT_ERROR);
    }
    
    if (!compress && !decompress)
    {
        printf("Es muss mindestens '-c' oder '-d' als Option übergeben werden.\n");
        exit(COMMANDLINEARGUMENT_ERROR);
    }
}


extern void get_outfile(char outfile_name[])
{
    if (outfile == NULL)
    {
        strcpy(filename, outfile_name);
        
        if (compress)
        {
            strcat(outfile_name, ".hc");
        }
        else
        {
            strcat(outfile_name, ".hd");
        }
    }
    else
    {
        strcpy(outfile_name, outfile);
    }
}

extern bool compress_file(void)
{
    return compress;
}

extern bool decompress_file(void)
{
    return decompress;
}

extern bool print_verbose_info(void)
{
    return verbose;
}

extern bool needs_help(void)
{
    return help;
}
