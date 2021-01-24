//
//  main.c
//  Strukturen
//
//  Created by Simon Schöpke on 21.01.21.
//

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdalign.h>

// a)
typedef struct {
    unsigned short tag;
    unsigned short monat;
    unsigned short jahr;
} ERSCHEINUNGSDATUM;

typedef enum {
    ROCK, JAZZ, BLUES
} GENRE;

typedef struct {
    char titel[50];
    ERSCHEINUNGSDATUM erscheinungsdatum;
    GENRE genre;
} CD;

// d)
void print_cd(CD cd)
{
    char *genre;
    
    switch (cd.genre) {
        case ROCK:
            genre = "Rock";
            break;
        case JAZZ:
            genre = "Jazz";
            break;
        case BLUES:
            genre = "Blues";
            break;
        default:
            genre = "unknown genre";
            break;
    }
    
    printf("CD(titel: %s, genre: %s, erscheinungsdatum: Erscheinungsdatum(tag: %hu, monat: %hu, jahr: %hu))\n", cd.titel, genre, cd.erscheinungsdatum.tag, cd.erscheinungsdatum.monat, cd.erscheinungsdatum.jahr);
}

// e)
bool cmp_release_date(ERSCHEINUNGSDATUM *rd1, ERSCHEINUNGSDATUM *rd2)
{
    return (rd1->jahr == rd2->jahr) && (rd1->monat == rd2->monat) && (rd1->tag == rd2->tag);
}

bool cmp_cd(CD *cd1, CD *cd2)
{
    bool has_same_title = strcmp(cd1->titel, cd2->titel) == 0;
    bool has_same_genre = cd1->genre == cd2->genre;
    bool has_same_release_date = cmp_release_date(&cd1->erscheinungsdatum, &cd2->erscheinungsdatum);
    return has_same_title && has_same_genre && has_same_release_date;
}

int main(int argc, const char * argv[]) {
    
    // b)
    CD cd1;
    CD cd2;
    CD cd3;
    
    strcpy(cd1.titel, "Nirvana Smells Like Teen Spirit");
    cd1.genre = ROCK;
    cd1.erscheinungsdatum.jahr = 1991;
    cd1.erscheinungsdatum.monat = 9;
    cd1.erscheinungsdatum.tag = 10;

    strcpy(cd2.titel, "The Red Rooster");
    cd2.genre = BLUES;
    cd2.erscheinungsdatum.jahr = 1961;
    cd2.erscheinungsdatum.monat = 10;
    cd2.erscheinungsdatum.tag = 20;

    cd3 = cd1;
    
    printf("Alignment of CD: %lu\n", alignof(CD));
    printf("Alignment of Erscheinungsdatum: %lu\n", alignof(cd1.erscheinungsdatum));
    printf("Alignment of GENRE: %lu\n", alignof(cd1.genre));
    printf("Alignment of titel: %lu\n", alignof(cd1.titel));
    
    // c)
    printf("CD: %lu bytes\n", sizeof(CD));
    printf("Titel: %lu bytes\n", sizeof(cd1.titel));
    printf("GENRE: %lu bytes\n", sizeof(cd1.genre));
    printf("ERSCHEINUNGSDATUM: %lu bytes\n", sizeof(cd1.erscheinungsdatum));
    
    // d)
    print_cd(cd1);
    print_cd(cd2);
    print_cd(cd3);
    
    // e)
    printf("cd1 %s cd2\n", cmp_cd(&cd1, &cd2) == 0 ? "!=" : "==");
    printf("cd1 %s cd3\n", cmp_cd(&cd1, &cd3) == 0 ? "!=" : "==");
    printf("cd2 %s cd3\n", cmp_cd(&cd2, &cd3) == 0 ? "!=" : "==");
    
//    printf("%d\n", sizeof(unsigned short));
    
//    CD cd[2];
    
//    printf("%d\n", sizeof(cd));
    
    return 0;
}
