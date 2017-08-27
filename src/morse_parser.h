#ifndef MORSE_PARSER_H
#define MORSE_PARSER_H
#include <stdint.h>
#include <unistd.h>


struct morse_buf_offsets {
    size_t dest;
    size_t src;
};

typedef struct morse_parser {
    struct morse_buf_offsets buf_offsets;
    uint8_t tree_pos;
} morse_parser;

#endif
