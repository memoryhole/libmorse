#ifndef MORSE_H
#define MORSE_H

#include <unistd.h>

typedef enum morse_state {
    MORSE_DONE,
    MORSE_ERROR,
    MORSE_INVALID_SEQUENCE,
    MORSE_CONTINUE
} morse_state;

typedef struct morse_parser {
    size_t dest_offset;
    size_t src_offset;
} morse_parser;

typedef enum morse_symbol {
    DIT,
    DAH
} morse_symbol;

morse_state morse_init(morse_parser *parser);
morse_state morse_parse(morse_parser *parser, char *morse_string, size_t length);
morse_state morse_push_symbol(morse_parser *parser, morse_symbol symbol);
morse_state morse_get_value(morse_parser *parser);
morse_state morse_from_ascii(morse_parser *parser, char *string, size_t length, char *dest, size_t dest_len, size_t *fill_len);

#endif
