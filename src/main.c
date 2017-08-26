#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "morse.h"

void usage(void) {
    fprintf(stderr,
            "Usage: morse [OPTION] [STRING]\n"
            "Converts standard input or argument to morse or text\n\n"
            "  -t        morse to text\n"
            "  -m        text to morse\n"
           );
}

void die(const char *msg) {
    fputs(msg, stderr);
    abort();
}

typedef enum mode {
    TO_MORSE,
    TO_TEXT
} mode;

int main(int argc, char **argv) {

    // Argument Parsing
    mode mode;
    char *input = NULL;

    if (argc < 2) {
        usage();
        exit(EXIT_FAILURE);
    } else if (strncmp(argv[1], "-t", 2) == 0) {
        mode = TO_TEXT;
    } else if (strncmp(argv[1], "-m", 2) == 0) {
        mode = TO_MORSE;
    } else {
        usage();
        exit(EXIT_FAILURE);
    }

    if (argc > 2) {
        input = argv[2];
    }

    morse_parser parser;
    morse_reset(&parser);

    size_t buflen = 256;
    char buf[buflen];

    int written = 0;
    morse_state result;

    // String passed as argument
    if (input != NULL) {
        if (mode == TO_TEXT) {
            while(true) {
                result = morse_to_text(&parser, input, strlen(input), buf, buflen, &written);

                switch(result) {
                    case MORSE_ERROR:
                        fprintf(stderr, "unknown error\n");
                        exit(EXIT_FAILURE);
                    case MORSE_INVALID_SEQUENCE:
                        fprintf(stderr, "invalid morse sequence: %s\n", input);
                        exit(EXIT_FAILURE);
                    case MORSE_CONTINUE:
                        printf("%.*s", written, buf);
                        break;
                    case MORSE_DONE:
                        printf("%.*s", written, buf);
                        exit(EXIT_SUCCESS);
                }
            }
        } else {
            while(true) {
                result = morse_from_text(&parser, input, strlen(input), buf, buflen, &written);

                switch(result) {
                    case MORSE_ERROR:
                        fprintf(stderr, "unknown error\n");
                        exit(EXIT_FAILURE);
                    case MORSE_INVALID_SEQUENCE:
                        fprintf(stderr, "invalid text: %s\nOnly a-z A-Z 0-9 supported.\n", input);
                        exit(EXIT_FAILURE);
                    case MORSE_CONTINUE:
                        printf("%.*s", written, buf);
                        break;
                    case MORSE_DONE:
                        printf("%.*s", written, buf);
                        exit(EXIT_SUCCESS);
                }
            }
        }

    // Read from stdin
    } else {
        char input_char = EOF;

        while ((input_char = getc(stdin)) != EOF) {
            if (mode == TO_TEXT) {
                if (input_char == ' ' || input_char == '\n') {
                    result = morse_get_value(&parser, buf);

                    switch(result) {
                        case MORSE_ERROR:
                            fprintf(stderr, "unknown error\n");
                            exit(EXIT_FAILURE);
                        case MORSE_INVALID_SEQUENCE:
                            fprintf(stderr, "invalid morse sequence\n");
                            exit(EXIT_FAILURE);
                        case MORSE_CONTINUE:
                        case MORSE_DONE:
                            printf("%c", buf[0]);
                            morse_reset(&parser);
                    }
                } else if (input_char == '.' || input_char == '-') {
                    result = morse_push_symbol(&parser, input_char == '.' ? MORSE_DIT : MORSE_DAH);

                    switch(result) {
                        case MORSE_ERROR:
                            fprintf(stderr, "unknown error\n");
                            exit(EXIT_FAILURE);
                        case MORSE_INVALID_SEQUENCE:
                            fprintf(stderr, "invalid morse sequence\n");
                            exit(EXIT_FAILURE);
                        case MORSE_CONTINUE:
                            continue;
                        case MORSE_DONE:
                            printf("%c", buf[0]);
                            morse_reset(&parser);
                    }
                } else {
                    fprintf(stderr, "invalid morse sequence\n");
                    exit(EXIT_FAILURE);
                }
                
            } else { 
                result = morse_from_text(&parser, &input_char, 1, buf, buflen, &written);

                switch(result) {
                    case MORSE_ERROR:
                        fprintf(stderr, "unknown error\n");
                        exit(EXIT_FAILURE);
                    case MORSE_INVALID_SEQUENCE:
                        fprintf(stderr, "invalid text: %c\nOnly a-z A-Z 0-9 supported.\n", input_char);
                        exit(EXIT_FAILURE);
                    case MORSE_CONTINUE:
                        printf("%.*s", written, buf);
                        break;
                    case MORSE_DONE:
                        printf("%.*s", written, buf);
                        morse_reset(&parser);
                }
            }
        }


    }

}
