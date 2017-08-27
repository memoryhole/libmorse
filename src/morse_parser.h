#ifndef MORSE_PARSER_H
#define MORSE_PARSER_H
#include <stdint.h>
#include <unistd.h>

typedef enum morse_state {
    MORSE_DONE,
    MORSE_ERROR,
    MORSE_INVALID_SEQUENCE,
    MORSE_CONTINUE
} morse_state;

struct morse_buf_offsets {
    size_t dest;
    size_t src;
};

typedef struct morse_parser {
    struct morse_buf_offsets buf_offsets;
    uint8_t tree_pos;
} morse_parser;

typedef enum morse_symbol {
    MORSE_DIT = '.',
    MORSE_DAH = '-'
} morse_symbol;

#endif
