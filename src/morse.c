#include "morse.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

morse_state morse_init_parser(morse_parser *parser) {
    memset(parser, 0, sizeof(morse_parser));
}

morse_state morse_init(morse_parser *parser);
morse_state morse_reset(morse_parser *parser);
morse_state morse_parse(morse_parser *parser, char *morse_string, size_t length);
morse_state morse_push_symbol(morse_parser *parser, morse_symbol symbol);
morse_state morse_get_value(morse_parser *parser);
morse_state morse_from_ascii(char *string, size_t length);
