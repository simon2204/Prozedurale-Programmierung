/* ===========================================================================
 * Header-Dateien einbinden
 * ======================================================================== */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "frequency.h"


/* ===========================================================================
 * Makros
 * ======================================================================== */

/**
 * Makro zur Prüfung ob die Speicherallokation erfolgreich war: Ist die
 * übergebene Variable NULL, wird das Programm mit einer Fehlermeldung
 * abgebrochen.
 */
#define ASSERT_NOT_NULL(VAR) \
{if (VAR == NULL) { \
    fprintf(stderr, "%s:%d: error: %s\n", __FILE__, __LINE__, strerror(errno));\
    exit(EXIT_FAILURE); \
}}


/* ===========================================================================
 * Strukturdefinitionen
 * ======================================================================== */

/**
 * Setzt Wörter mit einer Häufigkeit in Beziehung
 */
struct FREQUENCY
{
    /**
     * Komponente für das Wort
     */
    unsigned char word;
    /**
     * Komponente für die Anzahl der Wortvorkommen
     */
    int count;
};


/* ===========================================================================
 * Funktionsdefinitionen
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Funktion: frequency_create
 * ------------------------------------------------------------------------ */
extern struct FREQUENCY *frequency_create(const unsigned char word, const int count)
{
    /* Speicher für die Struktur allokieren */
    struct FREQUENCY *p_frequency = malloc(sizeof (struct FREQUENCY));
    ASSERT_NOT_NULL(p_frequency);

    /* Komponenten der Struktur initialisieren */
    p_frequency->word = word;
    p_frequency->count = count;

    return p_frequency;
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_destroy
 * ------------------------------------------------------------------------ */
extern void frequency_destroy(struct FREQUENCY **pp_frequency)
{
    if (pp_frequency != NULL && *pp_frequency != NULL)
    {

#ifdef DEBUG
        /* Ausgabe der zu löschenden Daten zu Debugzwecken */
        printf("- Loesche struct Frequency");
        frequency_print(*pp_frequency);
        printf(" \n");
#endif

        free(*pp_frequency);
        *pp_frequency = NULL;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_get_char
 * ------------------------------------------------------------------------ */
extern unsigned char frequency_get_char(const struct FREQUENCY *p_frequency)
{
    unsigned char copied_string = '\0';

    if (p_frequency != NULL)
    {
        copied_string = p_frequency->word;
    }

    return copied_string;
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_get_count
 * ------------------------------------------------------------------------ */
extern int frequency_get_count(const struct FREQUENCY *p_frequency)
{
    int count = -1;

    if (p_frequency != NULL)
    {
        count = p_frequency->count;
    }

    return count;
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_set_word
 * ------------------------------------------------------------------------ */
extern void frequency_set_word(struct FREQUENCY *p_frequency, const unsigned char word)
{
    if (p_frequency == NULL)
    {
        return;
    }

    /* Benötigten Speicherplatz abhängig vom übergebenen Wort ermitteln.
     * Wurde kein Wort angegeben, wird das alte Wort gelöscht. */
    p_frequency->word = word;
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_set_count
 * ------------------------------------------------------------------------ */
extern void frequency_set_count(struct FREQUENCY *p_frequency, 
                                const int count)
{
    if (p_frequency != NULL)
    {
        p_frequency->count = count;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_increase_by_one
 * ------------------------------------------------------------------------ */
extern void frequency_increase_by_one(struct FREQUENCY *p_frequency)
{
    if (p_frequency != NULL)
    {
        p_frequency->count += 1;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_compare
 * ------------------------------------------------------------------------ */
extern int frequency_compare(const struct FREQUENCY *p_frequency1, 
        const struct FREQUENCY *p_frequency2)
{
    if (p_frequency1 != NULL && p_frequency2 != NULL)
    {
        return p_frequency1->count < p_frequency2->count ? -1 : p_frequency1->count > p_frequency2->count ? 1 : 0;
    }
    else 
    {
        return 0;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: frequency_print
 * ------------------------------------------------------------------------ */
extern void frequency_print(const struct FREQUENCY *p_frequency)
{
    if (p_frequency != NULL)
    {
        printf("[%c: %d]", p_frequency->word, p_frequency->count);
    }
}
