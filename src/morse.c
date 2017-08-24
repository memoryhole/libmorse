#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include "morse.h"
#include "data.h"

morse_state morse_init(morse_parser *parser) {
    memset(parser, 0, sizeof(morse_parser));

    parser->dest_offset = 0;
    parser->src_offset = 0;

    return MORSE_CONTINUE;
}

morse_state morse_from_ascii(morse_parser *parser, char *string, size_t length, char *dest, size_t dest_len, size_t *fill_len) {

    if (dest_len < MORSE_MIN_LEN) {
        return MORSE_ERROR;
    }

    if (parser->src_offset == 0) {
        *fill_len = 0;
    }

    while(parser->src_offset < length) {
        int i = parser->src_offset;

        char c = string[i];
        uint8_t table_idx = 0;

        if (c <= 'z' && c >= 'a') {
            table_idx = c - 'a';

        } else if (c <= 'Z' && c >= 'A') {
            table_idx = c - 'A';

        } else if (c <= '9' && c >= '0') {
            table_idx = c - '0';

        } else {
            return MORSE_INVALID_SEQUENCE;
        }

        const char *code = morse_codes[table_idx];
        const size_t codelen = strlen(code) + 1;

        if (codelen > dest_len - parser->dest_offset) {
            parser->dest_offset = 0;
            return MORSE_CONTINUE;
        }

        memcpy(dest + parser->dest_offset, code, codelen);

        parser->dest_offset += codelen - 1;
        parser->src_offset += 1;
        *fill_len = parser->dest_offset;
    }

    return MORSE_DONE;
}

morse_state morse_parse(morse_parser *parser, char *morse_string, size_t length);
morse_state morse_push_symbol(morse_parser *parser, morse_symbol symbol);
morse_state morse_get_value(morse_parser *parser);
