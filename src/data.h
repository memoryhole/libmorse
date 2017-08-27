#ifndef DATA_H
#define DATA_H

#include <unistd.h>
#include <stdint.h>

#ifndef SINGLE_HEADER
#include "morsetree.h"
#endif

#define MORSE_MIN_LEN 5

extern const char *morse_characters[];
extern const size_t morse_characters_len;

extern const char *morse_numbers[];
extern const size_t morse_numbers_len;

uint8_t morse_tree_dit(uint8_t pos);
uint8_t morse_tree_dah(uint8_t pos);

#endif
