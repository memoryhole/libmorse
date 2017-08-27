#ifndef MORSE_H
#define MORSE_H

#ifndef SINGLE_HEADER
#include "morse_parser.h"
#endif

typedef enum morse_state {
    MORSE_DONE,
    MORSE_ERROR,
    MORSE_INVALID_SEQUENCE,
    MORSE_CONTINUE
} morse_state;

typedef enum morse_symbol {
    MORSE_DIT = '.',
    MORSE_DAH = '-'
} morse_symbol;

/*
 * Resets the parser to a clean state. Must be called before doing anything else.
 */
morse_state morse_reset(morse_parser *parser);

/*
 * Converts text to a string of morse with '.' being  DIT and '-' being a DAH.
 * `dest` should at least be MORSE_MIN_LEN bytes long.
 *
 * morse_from_text will return one of the following states
 *
 * MORSE_ERROR: the `dest_len` passed is less than MORSE_MIN_LEN
 * MORSE_INVALID_SEQUENCE: the passed `string` contains characters we cannot convert to morse
 * MORSE_CONTINUE: the `dest` buffer has been filled up to `fill_len`. you should flush it (probably print the contents) and then you can call `morse_from_text` again.
 * MORSE_DONE: the `dest` buffer has been filled up to `fill_len`. you should flush it (probably print the contents) and call `morse_reset` before using the parser again.
 *
 * @param parser    the morse parser
 * @param string    the input ASCII string
 * @param length    the number of bytes in `string`
 * @param dest      the destination buffer to write to (must be at least MORSE_MIN_LEN bytes)
 * @param dest_len  the size of the destination buffer
 * @param fill_len  the number of bytes writted to `dest` when morse_from_text returns MORSE_CONTINUE or MORSE_DONE
 *
 */
morse_state morse_from_text(morse_parser *parser, char *string, size_t length, char *dest, size_t dest_len, int *fill_len);


/*
 * Converts a string of morse to text with '.' being  DIT and '-' being a DAH in the input string.
 * This will write to `dest` up to `dest_len` characters.
 *
 * morse_to_text will return one of the following states
 *
 * MORSE_INVALID_SEQUENCE: the passed `string` contains invalid characters or invalid morse sequences
 * MORSE_CONTINUE: the `dest` buffer has been filled up to `fill_len`. you should flush it (probably print the contents) and then you can call `morse_to_text` again.
 * MORSE_DONE: the `dest` buffer has been filled up to `fill_len`. you should flush it (probably print the contents) and call `morse_reset` before using the parser again.
 *
 * @param parser        the morse parser
 * @param morse_string  the input morse string
 * @param length        the number of bytes in `string`
 * @param dest          the destination buffer to write to
 * @param dest_len      the size of the destination buffer
 * @param fill_len      the number of bytes writted to `dest` when morse_from_text returns MORSE_CONTINUE or MORSE_DONE
 *
 */
morse_state morse_to_text(morse_parser *parser, char *morse_string, size_t length, char *dest, size_t dest_len, int *fill_len);

/*
 * Inputs a morse symbol into the parser. This is useful when you want to process some streaming input of unknown size.
 *
 * morse_push_symbol will return one of the following states
 *
 * MORSE_INVALID_SEQUENCE: the current sequence of symbols is invalid morse. you should call `morse_reset` before using the parser again.
 * MORSE_CONTINUE: the current sequence of symbols is still valid and you can continue to call `morse_push_symbol` or `morse_get_value`.
 * 
 * @param parser  the morse parser
 * @param symbol  the input symbol
 */
morse_state morse_push_symbol(morse_parser *parser, morse_symbol symbol);

/*
 * Gets the current value for morse symbols pushed into the parser via `morse_push_symbol`.
 *
 * morse_get_value will return one of the following states
 *
 * MORSE_INVALID_SEQUENCE: the current sequence of symbols is invalid morse. you should call `morse_reset` before using the parser again.
 * MORSE_DONE: the current sequence of symbols was valid morse and the associated character has been written to `dest`
 * 
 * @param parser  the morse parser
 * @param dest    char pointer to write the value to
 */
morse_state morse_get_value(morse_parser *parser, char *dest);

#endif
