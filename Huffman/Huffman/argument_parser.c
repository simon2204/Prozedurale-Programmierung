//
//  argument_parser.c
//  Huffman
//
//  Created by Simon Schöpke on 09.01.21.
//

#include "argument_parser.h"

static void show_help(void);
static void print_err(char *msg, ...);

static HUFFMAN_MODE mode;
static bool verbose;
static bool help;
static int level;
static char *outfile;
static char *filename;

extern void parse_argv(int argc, char **argv)
{
    mode = NOT_SET;
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
                print_err("Nach '-' wird eine Option erwartet.");
            }
            
            switch (*(argv[i] + 1)) {
                case 'c':
                    mode = COMPRESS;
                    break;
                case 'd':
                    mode = DECOMPRESS;
                    break;
                case 'v':
                    verbose = true;
                    break;
                case 'h':
                    help = true;
                    break;
                case 'l':
                    // Erster Character nach '-l9'
                    level = *(argv[i] + 2);
                    
                    // Wenn nach '-l' nichts mehr folgt.
                    if (level == '\0')
                    {
                        print_err("Es wurde kein Argument für <level> übergeben.");
                    }
                    // Wenn das Argument von '-l' nicht zwischen '1' und '9' liegt
                    // oder wenn das Argument zweistellig ist
                    if (level < '1' || level > '9' || *(argv[i] + 3) != '\0')
                    {
                        print_err("<level> muss zwischen 1 und 9 liegen.");
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

                    if (outfile != NULL && *outfile == '-')
                    {
                        print_err("Es wurde kein Argument für <outfile> übergeben.");
                    }
                    break;
                default:
                    print_err("Ungültige Option '-%c'.", *(argv[i] + 1));
                    break;
            }
        }
        else
        {
            if (filename != NULL)
            {
                print_err("'%s' wurde bereits als Name der Eingabedatei übergeben.", filename);
            }
            
            filename = argv[i];
            
            FILE *file_stream = fopen(filename, "r");
            
            if (file_stream == NULL)
            {
                printf("Die Datei konnte nicht geöffnet werden.\n");
                exit(IO_ERROR);
            }
            
            fclose(file_stream);
        }
    }
    
    if (help)
    {
        show_help();
    }
    
    if (filename == NULL)
    {
        print_err("Es wurde kein Argument für <filename> übergeben.");
    }
    
    if (outfile != NULL && strcmp(outfile, filename) == 0)
    {
        print_err("<outfile> und <filename> dürfen nicht den selben Namen haben.");
    }
    
    if (mode == NOT_SET)
    {
        print_err("Es muss mindestens '-c' oder '-d' als Option übergeben werden.");
    }
}

extern void get_infile(char infile_name[])
{
    strcpy(infile_name, filename);
}

extern void get_outfile(char outfile_name[])
{
    if (outfile == NULL)
    {
        strcpy(outfile_name, filename);
        
        if (mode == COMPRESS)
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

extern HUFFMAN_MODE huffman_mode(void)
{
    return mode;
}

extern bool wants_verbose_info(void)
{
    return verbose;
}

static void print_err(char *msg, ...)
{
    va_list args;
    
    va_start(args, msg);
    
    char *usage = "Usage: huffman <options> <filename>\n"
    "  See 'huffman -h' for more information.";
    
    printf("Error: ");
    
    vprintf(msg, args);
    
    printf("\n%s\n", usage);
    
    exit(COMMANDLINEARGUMENT_ERROR);
}

static void show_help(void)
{
    char *overview = "OVERVIEW: Komprimieren und Dekomprimieren einer Eingabedatei.\n\n";
    
    char *usage = "USAGE: huffman <options> <filename>\n\n";
    
    char *arguments = "ARGUMENTS:\n"
    "  <filename>       Name der Eingabedatei.\n\n";
    
    char *options = "OPTIONS:\n"
    "  -c               Die Eingabedatei wird komprimiert.\n"
    "  -d               Die Eingabedatei wird dekomprimiert.\n"
    "                   Sind im Aufruf beide Optionen -c und -d angegeben,\n"
    "                   bestimmt die letzte Angabe, ob komprimiert oder dekomprimiert wird.\n"
    "  -l<level>        Legt den Level der Komprimierung fest.\n"
    "                   Der Wert für den Level muss zwischen 1 und 9 liegen.\n"
    "                   Fehlt die Option, wird der Level standardmäßig auf 2 eingestellt.\n"
    "                   Der Parameter wird ignoriert, wenn die Option -d angegeben wurde.\n"
    "  -v               Gibt Informationen über die Komprimierung bzw. Dekomprimierung aus.\n"
    "  -o <outfile>     Legt den Namen der Ausgabedatei fest. Wird die Option weggelassen,\n"
    "                   wird der Name der Ausgabedatei standardmäßig festgelegt.\n"
    "  -h               Zeigt eine Hilfe an, die die Benutzung des Programms erklärt.\n";
    
    printf("%s%s%s%s", overview, usage, arguments, options);
    
    exit(SUCCESS);
}
