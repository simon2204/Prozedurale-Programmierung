/**
 * @mainpage 
 *
 * <h1>Projekt Kaffeemaschine</h1>
 *
 * In diesem Projekt wird die Steuerung einer Kaffeemaschine realisiert.
 *
 * @file
 * In diesem Modul wird die Steuerung der Kaffeemaschine realisiert.
 *
 * Die gedrückten Tasten werden in einem Byte wie folgt dargestellt: (Die 
 * Bitnummerierung erfolgt vom niederwertigsten Bit zum höchstwertigsten Bit):
 * <ul>
 * <li> Bit 0 hat den Wert 1, wenn die Taste für starken Kaffee 
 *      gedrückt wurde, 0 sonst.
 * <li> Bit 1 hat den Wert 1, wenn die Taste für Milch gedrückt 
 *      wurde, 0 sonst.
 * <li> Bit 2 hat den Wert 1, wenn die Taste für Zucker gedrückt 
 *      wurde, 0 sonst.
 * <li> Bit 3 hat den Wert 1, wenn die OK-Taste gedrückt wurde, 
 *      0 sonst.
 * <li> Die restlichen Bits 4-7 werden nicht benutzt.
 * </ul>
 * 
 * @author  Ulrike Griefahn
 * @date    2019-10-25
 */

/* ============================================================================
 * Header-Dateien 
 * ========================================================================= */

#include <stdio.h>
#include <stdbool.h>


/* ============================================================================
 * Typdefinitionen
 * ========================================================================= */

/**
 * Ein Element dieses Aufzählungstyps repräsentiert das Fehlen einer Zutat im 
 * Maschinenstatus #machine_state. Ist das Bit gesetzt, fehlt die Zutat.
 */
enum STATES
{
    WATER_EMPTY  = 0x01u,
    MILK_EMPTY   = 0x02u,
    SUGAR_EMPTY  = 0x04u,
    COFFEE_EMPTY = 0x08u
};

/**
 * Ein Element dieses Aufzählungstyps repräsentiert, dass eine Zutat für das 
 * Erstellen des gewünschten Kaffee benötigt wird. Ist das Bit gesetzt, wird
 * die Zutat benötigt
 */
enum NEEDED_INGREDIENTS
{
    WATER_NEEDED  = 0x01u,
    MILK_NEEDED   = 0x02u,
    SUGAR_NEEDED  = 0x04u,
    COFFEE_NEEDED = 0x08u
};

/**
 * Ein Element dieses Aufzählungstyps repräsentiert das Gedrücktsein jeweils 
 * einer Taste des Kaffeautomats. Ist das Bit gesetzt, ist die Taste gedrückt.
 */
enum BUTTONS
{
    STRONG_BUTTON = 0x01u,
    MILK_BUTTON   = 0x02u,
    SUGAR_BUTTON  = 0x04u,
    OK_BUTTON     = 0x08u
};


/* ============================================================================
 * Globale Variablen
 * ========================================================================= */

/**
 * Der Status der Kaffeemaschine wird in einem Status-Byte repräsentiert. (Die 
 * Numerierung der Bits erfolgt vom niederwertigsten zum höherwertigsten Bit.)
 * <ul>
 * <li> Bit 0 hat den Wert 1, wenn zu wenig Wasser enthalten ist, 0 sonst.
 * <li> Bit 1 hat den Wert 1, wenn zu wenig Milch enthalten ist, 0 sonst.
 * <li> Bit 2 hat den Wert 1, wenn zu wenig Zucker enthalten ist, 0 sonst.
 * <li> Bit 3 hat den Wert 1, wenn zu wenig Kaffee enthalten ist, 0 sonst.
 * <li> Die restlichen Bits 4-7 werden nicht benutzt.
 * </ul>
 */
unsigned char machine_state;


/* ============================================================================
 * Funktionsprototypen
 * ========================================================================= */

/**
 * Prüft, ob alle benötigten Zutaten vorhanden sind.
 *
 * @param pressed_buttons - Bytedarstellung der gedrückten Tasten.
 *                  Beschreibung der Bits - siehe coffee_machine.c
 * @return true, wenn alle benötigten Zutaten vorhanden sind,
 *                  false, sonst.
 */
bool check_ingredients(unsigned char pressed_buttons);

/**
 * Initiiert die Bereitstellung des Kaffees entsprechend der gedrückten Tasten.
 * Liefert ggf. Bildschirmausgaben, wenn der Kaffee nicht gekocht werden kann.
 *
 * @param pressed_buttons - Bytedarstellung der gedrückten Tasten.
 *                      Beschreibung der Bits - siehe coffee_machine.c
 */
void dispatch(unsigned char pressed_buttons);


/* ============================================================================
 * Funktionsdefinitionen
 * ========================================================================= */

/* ----------------------------------------------------------------------------
 * Funktion: check_ingredients
 * ------------------------------------------------------------------------- */
bool check_ingredients(unsigned char pressed_buttons)
{
    /* Enstprechend der gedrückten Tasten werden die Bits in der Variablen
     * #needed_ingredients so gesetzt, dass sie für alle benötigten Zutaten
     * ein 1-Bit an der für die Zutat entsprechenden Position des
     * Maschinenstatus hat. Alle anderen Bits haben den Wert 0. Ein bitweises
     * "und" mit dem Maschinenstatus liefert den Wert 0x00, wenn alle 
     * benötigten Zutaten vorhanden sind.
     *
     * <ul>
     * <li> Maschinenstatus: 0 & neededIngredients: 1 == 0: Benötigte Zutat vorhanden
     * <li> Maschinenstatus: 0 & neededIngredients: 0 == 0: Zutat nicht benötigt
     * <li> Maschinenstatus: 1 & neededIngredients: 1 == 1: Benötigte Zutat fehlt
     * <li> Maschinenstatus: 1 & neededIngredients: 0 == 0: Fehlende Zutat nicht benötigt
     * </ul>
     */
    unsigned char needed_ingredients;

    /* Wasser und Kaffee werden immer benötigt. */
    needed_ingredients = WATER_NEEDED | COFFEE_NEEDED;

    /* Wenn nötig, prüfe auch Milch und Zucker */
    if ((pressed_buttons & MILK_BUTTON) == MILK_BUTTON)
    {
        needed_ingredients |= MILK_NEEDED;
    }
    if ((pressed_buttons & SUGAR_BUTTON) == SUGAR_BUTTON)
    {
        needed_ingredients |= SUGAR_NEEDED;
    }
    /* Prüfe, ob benötigte Zutaten vorhanden sind. */
    return ((machine_state & needed_ingredients) == 0x00);
}

/* ----------------------------------------------------------------------------
 * Funktion: dispatch
 * ------------------------------------------------------------------------- */
void dispatch(unsigned char pressed_buttons)
{
    if ((pressed_buttons & OK_BUTTON) == OK_BUTTON)
    {
        if (check_ingredients(pressed_buttons))
        {
            /* Alle Zutaten vorhanden: Kaffee zubereiten */
            printf("Mahle Kaffee...\n");

            /* Starken oder normalen Kaffee kochen */
            if ((pressed_buttons & STRONG_BUTTON) == STRONG_BUTTON)
            {
                printf("Koche starken Kaffee...\n");
            }
            else
            {
                printf("Koche normalen Kaffee...\n");
            }
            /* ggf. Milch hinufügen */
            if ((pressed_buttons & MILK_BUTTON) == MILK_BUTTON)
            {
                printf("Fuege Milch hinzu...\n");
            }
            /* ggf. Zucker hinufügen */
            if ((pressed_buttons & SUGAR_BUTTON) == SUGAR_BUTTON)
            {
                printf("Fuege Zucker hinzu...\n");
            }
        }
        else
        {
            printf("Es sind nicht alle Zutaten vorhanden.\n");
        }
    }
    else
    {
        printf("OK-Taste nicht gedrueckt.\n");
    }
}


/* ============================================================================
 * main-Funktion
 * ========================================================================= */

