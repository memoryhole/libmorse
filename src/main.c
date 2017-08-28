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

/*
 * Demonstrates how to parse morse from a stream
 */
int stdin_morse_to_text(morse_parser *parser) {
    char input_char = EOF;
    morse_state result = MORSE_INVALID_SEQUENCE;

    char value;

    int return_value = EXIT_SUCCESS;

    while ((input_char = getc(stdin)) != EOF) {
        if (input_char == MORSE_DIT || input_char == MORSE_DAH) {
            result = morse_push_symbol(parser, input_char);

            if (result == MORSE_INVALID_SEQUENCE) {
                fprintf(stderr, "invalid morse sequence\n");
                return_value = EXIT_FAILURE;
                break;
            }

        // If reading from something other than a stream, like an actual telegraph key or signal,
        // then you'd use timing to determing character boundaries.
        } else if (input_char == ' ' || input_char == '\n') {
            result = morse_get_value(parser, &value);

            if (result == MORSE_INVALID_SEQUENCE) {
                fprintf(stderr, "invalid morse sequence\n");
                return_value =  EXIT_FAILURE;
                break;
            } else {
                printf("%c", value);
                morse_reset(parser);
            }
        } else {
            fprintf(stderr, "invalid morse sequence\n");
            return_value = EXIT_FAILURE;
            break;
        }
    }

    return return_value;
}

/*
 * Demonstrates how to convert a morse string to text
 */
int morse_string_to_text(morse_parser *parser, char *input) {
    morse_state result = MORSE_INVALID_SEQUENCE;

    size_t buflen = 256;
    char buf[buflen];
    int written = 0;

    int return_value = -1;

    while (return_value == -1) {
        result = morse_to_text(parser, input, strlen(input), buf, buflen, &written);

        if (result == MORSE_INVALID_SEQUENCE) {
            fprintf(stderr, "invalid morse sequence\n");
            return_value = EXIT_FAILURE;
            break;

        } else if (result == MORSE_CONTINUE) {
            printf("%.*s", written, buf);

        } else if (result == MORSE_DONE) {
            printf("%.*s", written, buf);
            return_value = EXIT_SUCCESS;
            break;

        } else {
            fprintf(stderr, "unknown error\n");
            return_value = EXIT_FAILURE;
            break;
        }
    }

    return return_value;
}


/*
 * Demonstrates converting text to a morse string
 */
int text_to_morse(morse_parser *parser, char *input) {
    size_t buflen = 10;
    char buf[buflen];
    int written = 0;

    int return_value = -1;

    morse_state result = MORSE_INVALID_SEQUENCE;
   
    while (return_value == -1) {
        result = morse_from_text(parser, input, strlen(input), buf, buflen, &written);
        if (result == MORSE_INVALID_SEQUENCE) {
            fprintf(stderr, "invalid text: %s\nOnly a-z A-Z 0-9 supported.\n", input);
            return_value = EXIT_FAILURE;

        } else if (result == MORSE_CONTINUE) {
            printf("%.*s", written, buf);

        } else if (result == MORSE_DONE) {
            printf("%.*s", written, buf);
            break;

        } else {
            fprintf(stderr, "unknown error\n");
            return_value = EXIT_FAILURE;
        }
    }

    return return_value;

}

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

    // String passed as argument
    if (input != NULL) {
        if (mode == TO_TEXT) {
            return morse_string_to_text(&parser, input);

        } else {
            return text_to_morse(&parser, input);
        }

    // Read from stdin
    } else {
        if (mode == TO_TEXT) {
            return stdin_morse_to_text(&parser);

        } else {
            char temp[2] = {0, 0};
            bool firstchar = true;
                
            while ((temp[0] = getc(stdin)) != EOF) {
                if (!firstchar) {
                    if (temp[0] != '\n') {
                        printf(" ");
                    }
                } else {
                    firstchar = false;
                }

                int result = text_to_morse(&parser, temp);
                morse_reset(&parser);

                if (result == EXIT_FAILURE) {
                    return result;
                }
            }
        }
    }

    return EXIT_SUCCESS;
}
