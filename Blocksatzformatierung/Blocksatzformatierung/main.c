//
//  main.c
//  Blocksatzformatierung
//
//  Created by Simon Schöpke on 17.12.20.
//

#include "justify_line.h"

#if DEBUG
#include <assert.h>
#include <string.h>
#include <stdio.h>
#endif


int main(int argc, const char * argv[]) {

#if DEBUG
    char line1[] = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
    char line2[] = "";
    char line3[] = "   1234567890123456789012345678901234567890123456789    ";
    char line4[] = "123456789 123456789 123456789 123456789 123456789 123456789 123456789 1234567890";
    char line5[] = "123456789 345678901 567890123 789012345 901234567 123456789 234567890";
    char line6[] = " 1234567 3456789 4567890 56789012 78901234 901234567 234567890";
    char line7[] = "   1234567 3456789 4567890 56789012 78901234 901234567 234567890";
    char line8[] = "123456789 345678901 567890123 789012345 901234567 123456789 234567890 ";
    char line9[] = "123456789 345678901 567890123 789012345 901234567 123456789 234567890     ";
    char line10[] = "123456789 345678901   567890123 789012345     901234567 123456789 234567890";
    char line11[] = "123456789 567890123 890123456 123456789 456789012 789012345 0";
    char line12[] = "123456789 567890123 901234567 345678901 789012345 1234567890";
    char line13[] = "123456789 12345678901  4567890123 56789012345  8901234567  0123456789  234567890123456";
    
    char line1Soll[] = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
    char line2Soll[] = "";
    char line3Soll[] = "1234567890123456789012345678901234567890123456789";
    char line4Soll[] = "123456789 123456789 123456789 123456789 123456789 123456789 123456789 1234567890";
    char line5Soll[] = "123456789   345678901   567890123   789012345   901234567   123456789  234567890";
    char line6Soll[] = "1234567     3456789    4567890    56789012    78901234    901234567    234567890";
    char line7Soll[] = "1234567     3456789    4567890    56789012    78901234    901234567    234567890";
    char line8Soll[] = "123456789   345678901   567890123   789012345   901234567   123456789  234567890";
    char line9Soll[] = "123456789   345678901   567890123   789012345   901234567   123456789  234567890";
    char line10Soll[] = "123456789   345678901   567890123   789012345   901234567   123456789  234567890";
    char line11Soll[] = "123456789     567890123    890123456    123456789    456789012    789012345    0";
    char line12Soll[] = "123456789     567890123     901234567     345678901     789012345     1234567890";
    char line13Soll[] = "123456789 12345678901 4567890123 56789012345 8901234567 0123456789 234567890123456";
    
    char justified_line1[MAX_LINE_LENGTH] = "";
    char justified_line2[MAX_LINE_LENGTH] = "";
    char justified_line3[MAX_LINE_LENGTH] = "";
    char justified_line4[MAX_LINE_LENGTH] = "";
    char justified_line5[MAX_LINE_LENGTH] = "";
    char justified_line6[MAX_LINE_LENGTH] = "";
    char justified_line7[MAX_LINE_LENGTH] = "";
    char justified_line8[MAX_LINE_LENGTH] = "";
    char justified_line9[MAX_LINE_LENGTH] = "";
    char justified_line10[MAX_LINE_LENGTH] = "";
    char justified_line11[MAX_LINE_LENGTH] = "";
    char justified_line12[MAX_LINE_LENGTH] = "";
    char justified_line13[MAX_LINE_LENGTH] = "";
    
    int target_line_length = 80;
    
    justify_line(line1, target_line_length, justified_line1);
    assert(strcmp(line1Soll, justified_line1) == 0);

    justify_line(line2, target_line_length, justified_line2);
    assert(strcmp(line2Soll, justified_line2) == 0);

    justify_line(line3, target_line_length, justified_line3);
    assert(strcmp(line3Soll, justified_line3) == 0);

    justify_line(line4, target_line_length, justified_line4);
    assert(strcmp(line4Soll, justified_line4) == 0);

    justify_line(line5, target_line_length, justified_line5);
    assert(strcmp(line5Soll, justified_line5) == 0);

    justify_line(line6, target_line_length, justified_line6);
    assert(strcmp(line6Soll, justified_line6) == 0);

    justify_line(line7, target_line_length, justified_line7);
    assert(strcmp(line7Soll, justified_line7) == 0);

    justify_line(line8, target_line_length, justified_line8);
    assert(strcmp(line8Soll, justified_line8) == 0);

    justify_line(line9, target_line_length, justified_line9);
    assert(strcmp(line9Soll, justified_line9) == 0);

    justify_line(line10, target_line_length, justified_line10);
    assert(strcmp(line10Soll, justified_line10) == 0);

    justify_line(line11, target_line_length, justified_line11);
    assert(strcmp(line11Soll, justified_line11) == 0);

    justify_line(line12, target_line_length, justified_line12);
    assert(strcmp(line12Soll, justified_line12) == 0);
    
    justify_line(line13, target_line_length, justified_line13);
    assert(strcmp(line13Soll, justified_line13) == 0);
    
#endif
    
    return 0;
}

