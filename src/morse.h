#ifndef MORSE_H
#define MORSE_H

#include <unistd.h>

typedef enum morse_state {
    MORSE_OK,
    MORSE_ERROR,
    MORSE_INVALID_SEQUENCE,
    MORSE_HAS_VALUE
} morse_state;

typedef struct morse_parser {
} morse_parser;

typedef enum morse_symbol {
    DIT,
    DAH
} morse_symbol;

morse_state morse_init(morse_parser *parser);
morse_state morse_reset(morse_parser *parser);
morse_state morse_parse(morse_parser *parser, char *morse_string, size_t length);
morse_state morse_push_symbol(morse_parser *parser, morse_symbol symbol);
morse_state morse_get_value(morse_parser *parser);
morse_state morse_from_ascii(char *string, size_t length);

#endif
