#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#ifndef SINGLE_HEADER
#include "morse.h"
#include "data.h"
#endif

morse_state morse_reset(morse_parser *parser) {
    memset(parser, 0, sizeof(morse_parser));

    return MORSE_CONTINUE;
}

morse_state morse_from_text(morse_parser *parser, char *string, size_t length, char *dest, size_t dest_len, int *fill_len) {

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

        const char *code;
        size_t codelen;

        if (c <= 'z' && c >= 'a') {
            table_idx = c - 'a';

            code = morse_characters[table_idx];
            codelen = strlen(code);

        } else if (c <= 'Z' && c >= 'A') {
            table_idx = c - 'A';

            code = morse_characters[table_idx];
            codelen = strlen(code);

        } else if (c <= '9' && c >= '0') {
            table_idx = c - '0';

            code = morse_numbers[table_idx];
            codelen = strlen(code);

        } else if (c == ' ' || c == '\n') {
            //skip
            parser->buf_offsets.src += 1;
            continue;

        } else {
            return MORSE_INVALID_SEQUENCE;
        }


        if (codelen >= dest_len - parser->buf_offsets.dest) {
            parser->buf_offsets.dest = 0;
            return MORSE_CONTINUE;
        }

        memcpy(dest + parser->buf_offsets.dest, code, codelen + 1);

        // add a space if we are not at the end
        if (parser->buf_offsets.src < length - 1) {
            *(dest + parser->buf_offsets.dest + codelen) = ' ';
            *(dest + parser->buf_offsets.dest + codelen + 1) = 0;
            parser->buf_offsets.dest += codelen + 1;
        } else {
            parser->buf_offsets.dest += codelen;
        }

        parser->buf_offsets.src += 1;
        *fill_len = parser->buf_offsets.dest;
    }

    return MORSE_DONE;
}

morse_state morse_to_text(morse_parser *parser, char *morse_string, size_t length, char *dest, size_t dest_len, int *fill_len) {

    morse_state result = MORSE_ERROR;

    size_t i = 0;
    for (i = parser->buf_offsets.src; i < length; i++) {
        const char symbol = morse_string[i];

        if (symbol == '.' || symbol == '-') {
            result = morse_push_symbol(parser, symbol);
            if (result == MORSE_INVALID_SEQUENCE) {
                return result;
            }

        } else if (symbol == ' ' || symbol == '\n') {

            if (parser->buf_offsets.dest == dest_len) {
                *fill_len = parser->buf_offsets.dest;
                parser->buf_offsets.dest = 0;
                parser->buf_offsets.src = i;
                return MORSE_CONTINUE;
            }

            result = morse_get_value(parser, dest + parser->buf_offsets.dest);
            parser->buf_offsets.dest += 1;
            if (result == MORSE_INVALID_SEQUENCE) {
                return result;
            }

        } else {
            return MORSE_INVALID_SEQUENCE;
        }
    }

    if (parser->buf_offsets.dest == dest_len) {
        *fill_len = parser->buf_offsets.dest;
        parser->buf_offsets.dest = 0;
        parser->buf_offsets.src = i;
        return MORSE_CONTINUE;
    }

    *fill_len = parser->buf_offsets.dest + 1;
    return morse_get_value(parser, dest + parser->buf_offsets.dest);
}

morse_state morse_push_symbol(morse_parser *parser, morse_symbol symbol) {
    if (symbol == MORSE_DIT) {
        parser->tree_pos = morse_tree_dit(parser->tree_pos);

    } else if (symbol == MORSE_DAH) {
        parser->tree_pos = morse_tree_dah(parser->tree_pos);

    } else {
        return MORSE_INVALID_SEQUENCE;
    }

    if (parser->tree_pos > morsetree_bin_len) {
        return MORSE_INVALID_SEQUENCE;
    }

    return MORSE_CONTINUE;
}

morse_state morse_get_value(morse_parser *parser, char *dest) {
    if (parser->tree_pos > morsetree_bin_len) {
        return MORSE_INVALID_SEQUENCE;
    }

    uint8_t value = morsetree_bin[parser->tree_pos];

    if (value != 0) {
        *dest = value;
        parser->tree_pos = 0;
        return MORSE_DONE;
    }

    return MORSE_INVALID_SEQUENCE;
}
