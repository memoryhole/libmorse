#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include "morse.h"
#include "data.h"

morse_state morse_init(morse_parser *parser) {
    memset(parser, 0, sizeof(morse_parser));

    return MORSE_CONTINUE;
}

morse_state morse_from_ascii(morse_parser *parser, char *string, size_t length, char *dest, size_t dest_len, size_t *fill_len) {

    if (dest_len < MORSE_MIN_LEN + 1) {
        return MORSE_ERROR;
    }

    if (parser->buf_offsets.src == 0) {
        *fill_len = 0;
    }

    while(parser->buf_offsets.src < length) {
        int i = parser->buf_offsets.src;

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

        if (codelen > dest_len - parser->buf_offsets.dest) {
            parser->buf_offsets.dest = 0;
            return MORSE_CONTINUE;
        }

        memcpy(dest + parser->buf_offsets.dest, code, codelen);

        parser->buf_offsets.dest += codelen - 1;
        parser->buf_offsets.src += 1;
        *fill_len = parser->buf_offsets.dest;
    }

    return MORSE_DONE;
}

morse_state morse_parse(morse_parser *parser, char *morse_string, size_t length, char *dest, size_t dest_len, size_t *fill_len) {

    for (size_t i = parser->buf_offsets.src; i < length; i++) {
        const char symbol = morse_string[i];

        if (symbol == '.') {
            parser->tree_pos = morse_tree_dit(parser->tree_pos);

        } else if (symbol == '-') {
            parser->tree_pos = morse_tree_dah(parser->tree_pos);

        } else if (symbol == ' ') {
            uint8_t value = morsetree_bin[parser->tree_pos];
            if (parser->tree_pos > morsetree_bin_len || value == 0) {
                return MORSE_INVALID_SEQUENCE;
            }

            *(dest + parser->buf_offsets.dest) = value;
            parser->buf_offsets.dest += 1;
            parser->tree_pos = 0;

            if (parser->buf_offsets.dest == dest_len) {
                *fill_len = parser->buf_offsets.dest;
                parser->buf_offsets.dest = 0;
                parser->buf_offsets.src = i + 1;
                return MORSE_CONTINUE;
            }
        }
    }

    uint8_t value = morsetree_bin[parser->tree_pos];
    if (parser->tree_pos > morsetree_bin_len || value == 0) {
        return MORSE_INVALID_SEQUENCE;
    }

    *(dest + parser->buf_offsets.dest) = value;
    parser->buf_offsets.dest += 1;
    *fill_len = parser->buf_offsets.dest;

    return MORSE_DONE;
}

morse_state morse_push_symbol(morse_parser *parser, morse_symbol symbol) {
}

morse_state morse_get_value(morse_parser *parser) {
}
