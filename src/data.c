#include <stdint.h>
#include "data.h"
#include "morsetree.h"

const char *morse_codes[] = {
    ".-",   //A
    "-...", //B
    "-.-.", //C
    "-..",  //D
    ".",    //E
    "..-.", //F
    "--.",  //G
    "....", //H
    "..",   //I
    ".---", //J
    "-.-",  //K
    ".-..", //L
    "--",   //M
    "-.",   //N
    "---",  //O
    ".--.", //P
    "--.-", //Q
    ".-.",  //R
    "...",  //S
    "-",    //T
    "..-",  //U
    "...-", //V
    ".--",  //W
    "-.--", //X
    "-.--", //Y
    "--..", //Z
};

const size_t morse_codes_len = sizeof(morse_codes) / sizeof(morse_codes[0]);

uint8_t morse_tree_dit(uint8_t pos) {
    return  2 * pos + 1;
}

uint8_t morse_tree_dah(uint8_t pos) {
    return 2 * pos + 2;
}
