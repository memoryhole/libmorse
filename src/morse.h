#ifndef MORSE_H
#define MORSE_H

#include <unistd.h>
#include <stdint.h>

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
    MORSE_DIT,
    MORSE_DAH
} morse_symbol;

morse_state morse_reset(morse_parser *parser);
morse_state morse_from_ascii(morse_parser *parser, char *string, size_t length, char *dest, size_t dest_len, size_t *fill_len);
morse_state morse_parse(morse_parser *parser, char *morse_string, size_t length, char *dest, size_t dest_len, size_t *fill_len);
morse_state morse_push_symbol(morse_parser *parser, morse_symbol symbol);
morse_state morse_get_value(morse_parser *parser, char *dest);

#endif
