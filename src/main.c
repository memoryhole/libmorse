#include "morse.h"
#include <stdio.h>

int main(void) {
    morse_parser parser;
    morse_reset(&parser);

    char buf[10];
    size_t buf_fill;

    while (1) {
        morse_state state = morse_from_ascii(&parser, "abc", 3, buf, sizeof(buf), &buf_fill);
        switch(state) {
            case MORSE_DONE:
                printf("%d - %s\n", state, buf);
                return 0;
            case MORSE_CONTINUE:
                printf("%d - %.*s\n", state, (int)buf_fill, buf);
                break;
            case MORSE_ERROR:
            case MORSE_INVALID_SEQUENCE:
                printf("ERROR\n");
                break;
        }
    }

    return 0;
}
