#include <stdint.h>
#include "data.h"
#include "morsetree.h"

const char *morse_characters[] = {
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

const size_t morse_characters_len = sizeof(morse_characters) / sizeof(morse_characters[0]);

const char *morse_numbers[] = {
    "-----", //0
    ".----", //1
    "..---", //2
    "...--", //3
    "....-", //4
    ".....", //5
    "-....", //6
    "--...", //7
    "---..", //8
    "----.", //9
};

const size_t morse_numbers_len = sizeof(morse_numbers) / sizeof(morse_numbers[0]);


uint8_t morse_tree_dit(uint8_t pos) {
    return  2 * pos + 1;
}

uint8_t morse_tree_dah(uint8_t pos) {
    return 2 * pos + 2;
}
