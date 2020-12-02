//
//  main.c
//  Wertebreiche
//
//  Created by Simon Schöpke on 28.11.20.
//

#include <stdio.h>
#include <limits.h>

extern unsigned char machine_state;
extern void dispatch(unsigned char pressed_buttons);

int main(int argc, const char * argv[]) {
    
    printf("a)\n");
    printf("Signed char Wertebereich von %d bis %d\n", CHAR_MIN, CHAR_MAX);
    printf("Unsigned char Wertebereich von %u bis %u\n\n", 0, UCHAR_MAX);
    
    printf("Signed short Wertebereich von %d bis %d\n", SHRT_MIN, SHRT_MAX);
    printf("Unsigned short Wertebereich von %u bis %u\n\n", 0, USHRT_MAX);
    
    printf("Signed int Wertebereich von %d bis %d\n", INT_MIN, INT_MAX);
    printf("Unsigned int Wertebereich von %u bis %u\n\n", 0, UINT_MAX);
    
    printf("Signed long Wertebereich von %ld bis %ld\n", LONG_MIN, LONG_MAX);
    printf("Unsigned long Wertebereich von %d bis %lu\n\n", 0, ULONG_MAX);
    
    printf("b)\n");
    
    char char_min = (char) (0x01 << 7);
    char char_max = ~char_min;
    printf("Signed char Wertebereich von %d bis %d\n", char_min, char_max);
    unsigned char uchar_max = ~(0x00);
    printf("Unsigned char Wertebereich von %u bis %u\n\n", 0, uchar_max);
    
    short short_min = (short) (0x01 << 15);
    short short_max = ~short_min;
    printf("Signed short Wertebereich von %d bis %d\n", short_min, short_max);
    unsigned short ushort_max = ~(0x00);
    printf("Unsigned short Wertebereich von %u bis %u\n\n", 0, ushort_max);
    
    int int_min = (0x01 << 31);
    int int_max = ~int_min;
    printf("Signed short Wertebereich von %d bis %d\n", int_min, int_max);
    unsigned int uint_max = ~(0x00);
    printf("Unsigned short Wertebereich von %u bis %u\n\n", 0, uint_max);
    
    long long_min = (0x01L << 63);
    long long_max = ~long_min;
    printf("Signed short Wertebereich von %ld bis %ld\n", long_min, long_max);
    unsigned long ulong_max = ~(0x00LU);
    printf("Unsigned short Wertebereich von %u bis %lu\n\n", 0, ulong_max);
    
    
    unsigned char pressed_buttons;

    printf("Teste dispatch "
           "ohne gedrueckte OK-Taste ...\n");
    machine_state = 0x00; /* alles vorhanden */
    pressed_buttons = 0x06; /* OK-Taste nicht gedrückt */
    dispatch(pressed_buttons); /* OK-Taste nicht gedrückt */
    printf("\n");

    printf("Teste dispatch fuer "
           "fuer starken Kaffee mit Zucker "
           "ohne Milch...\n");
    machine_state = 0x02; /* Milch fehlt */
    pressed_buttons = 0x0d; /* starker Kaffee mit Zucker */
    dispatch(pressed_buttons); /* Mahle Kaffee...
                                 * Koche starken Kaffee...
                                 * Füge Zucker hinzu... */
    printf("\n");

    printf("Teste dispatch "
           "fuer normalen Kaffee mit Milch und Zucker\n"
           "ohne Milch...\n");
    machine_state = 0x02; /* Milch fehlt */
    pressed_buttons = 0x0e; /* normaler Kaffee mit Milch und Zucker */
    dispatch(pressed_buttons); /* Es sind nicht alle Zutaten vorhanden. */
    printf("\n");

    printf("Teste dispatch "
           "fuer normalen Kaffee mit Milch "
           "ohne Zucker...\n");
    machine_state = 0x04; /* Zucker fehlt */
    pressed_buttons = 0x0a; /* normaler Kaffee mit Milch */
    dispatch(pressed_buttons); /* Mahle Kaffee...
                                 * Koche normalen Kaffee...
                                 * Füge Milch hinzu... */
    printf("\n");

    printf("Teste dispatch fuer normalen Kaffee mit Milch und Zucker\n"
           "ohne Milch und Zucker...\n");
    machine_state = 0x06; /* Zucker und Milch fehlen */
    pressed_buttons = 0x0e; /* normaler Kaffee mit Milch und Zucker */
    dispatch(pressed_buttons); /* Es sind nicht alle Zutaten vorhanden. */
    printf("\n");

    return 0;
}
