#ifndef DATA_H
#define DATA_H

#include <unistd.h>
#include <stdint.h>
#include "morsetree.h"

#define MORSE_MIN_LEN 5

extern const char *morse_codes[];
extern const size_t morse_codes_len;

uint8_t morse_tree_dit(uint8_t pos);
uint8_t morse_tree_dah(uint8_t pos);

#endif
