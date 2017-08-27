#ifndef MORSE_H
#define MORSE_H

#ifndef SINGLE_HEADER
#include "morse_parser.h"
#endif

morse_state morse_reset(morse_parser *parser);
morse_state morse_from_text(morse_parser *parser, char *string, size_t length, char *dest, size_t dest_len, int *fill_len);
morse_state morse_to_text(morse_parser *parser, char *morse_string, size_t length, char *dest, size_t dest_len, int *fill_len);
morse_state morse_push_symbol(morse_parser *parser, morse_symbol symbol);
morse_state morse_get_value(morse_parser *parser, char *dest);

#endif
