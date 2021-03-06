#include <unistd.h>
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>
#include <morse.h>
 
void morse_from_text_small_buf() {
    morse_parser morse;
    morse_reset(&morse);

    int buf_len = 1;
    char buf[buf_len];
    int fill_len = 0;

    morse_state result = morse_from_text(&morse, "ABC", 3, buf, buf_len, &fill_len);
    assert_int_equal(result, MORSE_ERROR);
}

void morse_from_text_fits_buf() {
    morse_parser morse;
    morse_reset(&morse);

    int buf_len = 6;
    char buf[buf_len];
    int fill_len = 0;

    morse_state result = morse_from_text(&morse, "A", 1, buf, buf_len, &fill_len);
    assert_int_equal(result, MORSE_DONE);
    assert_memory_equal(buf, ".-", 2);
}

void morse_from_text_larger_than_buf() {
    morse_parser morse;
    morse_reset(&morse);

    int buf_len = 7;
    char buf[buf_len];
    int fill_len = 0;

    morse_state result = morse_from_text(&morse, "ABC4", 4, buf, buf_len, &fill_len);
    assert_int_equal(result, MORSE_CONTINUE);
    assert_int_equal(fill_len, 3);
    assert_memory_equal(buf, ".- ", 4);

    result = morse_from_text(&morse, "ABC4", 4, buf, buf_len, &fill_len);
    assert_int_equal(result, MORSE_CONTINUE);
    assert_int_equal(fill_len, 5);
    assert_memory_equal(buf, "-... ", 6);

    result = morse_from_text(&morse, "ABC4", 4, buf, buf_len, &fill_len);
    assert_int_equal(result, MORSE_CONTINUE);
    assert_int_equal(fill_len, 5);
    assert_memory_equal(buf, "-.-. ", 6);

    result = morse_from_text(&morse, "ABC4", 4, buf, buf_len, &fill_len);
    assert_int_equal(result, MORSE_DONE);
    assert_int_equal(fill_len, 5);
    assert_memory_equal(buf, "....-", 6);
}

void morse_from_text_invalid_char() {
    morse_parser morse;
    morse_reset(&morse);

    int buf_len = 7;
    char buf[buf_len];
    int fill_len = 0;

    morse_state result = morse_from_text(&morse, "#", 3, buf, buf_len, &fill_len);
    assert_int_equal(result, MORSE_INVALID_SEQUENCE);
}

void morse_to_text_single_char() {
    morse_parser morse;
    morse_reset(&morse);

    int buf_len = 7;
    char buf[buf_len];
    int fill_len = 0;

    morse_state result = morse_to_text(&morse, ".-", 2, buf, buf_len, &fill_len);
    assert_int_equal(result, MORSE_DONE);
    assert_int_equal(fill_len, 1);
    assert_memory_equal(buf, "A", 1);
}

void morse_to_text_multi_char() {
    morse_parser morse;
    morse_reset(&morse);

    int buf_len = 7;
    char buf[buf_len];
    int fill_len  = 0;

    char *seq = ".- -... -.-.";
    size_t seq_len = 12;

    morse_state result = morse_to_text(&morse, seq, seq_len, buf, buf_len, &fill_len);
    assert_int_equal(result, MORSE_DONE);
    assert_int_equal(fill_len, 3);
    assert_memory_equal(buf, "ABC", 3);
}

void morse_to_text_small_buf() {
    morse_parser morse;
    morse_reset(&morse);

    int buf_len = 1;
    char buf[buf_len];
    int fill_len = 0;

    char *seq = ".- -... -.-.";
    int seq_len = 12;

    morse_state result = morse_to_text(&morse, seq, seq_len, buf, buf_len, &fill_len);
    assert_int_equal(result, MORSE_CONTINUE);
    assert_int_equal(fill_len, 1);
    assert_memory_equal(buf, "A", 1);

    result = morse_to_text(&morse, seq, seq_len, buf, buf_len, &fill_len);
    assert_int_equal(result, MORSE_CONTINUE);
    assert_int_equal(fill_len, 1);
    assert_memory_equal(buf, "B", 1);

    result = morse_to_text(&morse, seq, seq_len, buf, buf_len, &fill_len);
    assert_int_equal(result, MORSE_DONE);
    assert_int_equal(fill_len, 1);
    assert_memory_equal(buf, "C", 1);
}

void morse_to_text_invalid() {
    morse_parser morse;
    morse_reset(&morse);

    int buf_len = 1;
    char buf[buf_len];
    int fill_len = 0;

    char *seq = ".--...-.-.";
    int seq_len = 10;

    // long sequence
    morse_state result = morse_to_text(&morse, seq, seq_len, buf, buf_len, &fill_len);
    assert_int_equal(result, MORSE_INVALID_SEQUENCE);

    // empty node
    result = morse_to_text(&morse, "..--", 4, buf, buf_len, &fill_len);
    assert_int_equal(result, MORSE_INVALID_SEQUENCE);

    // invalid char
    result = morse_to_text(&morse, "..*-", 4, buf, buf_len, &fill_len);
    assert_int_equal(result, MORSE_INVALID_SEQUENCE);
}
 
void morse_stream_single_char() {
    morse_parser morse;
    morse_reset(&morse);

    morse_state result = morse_push_symbol(&morse, MORSE_DIT);
    assert_int_equal(result, MORSE_CONTINUE);
    result = morse_push_symbol(&morse, MORSE_DAH);
    assert_int_equal(result, MORSE_CONTINUE);

    char output;
    result = morse_get_value(&morse, &output);
    assert_int_equal(result, MORSE_DONE);

    assert_int_equal(output, 'A');
}
 
void morse_stream_multi_char() {
    morse_parser morse;
    morse_reset(&morse);

    char output;

    //.-
    morse_state result = morse_push_symbol(&morse, MORSE_DIT);
    assert_int_equal(result, MORSE_CONTINUE);
    result = morse_push_symbol(&morse, MORSE_DAH);
    assert_int_equal(result, MORSE_CONTINUE);
    result = morse_get_value(&morse, &output);
    assert_int_equal(result, MORSE_DONE);
    assert_int_equal(output, 'A');

    //.....
    result = morse_push_symbol(&morse, MORSE_DIT);
    assert_int_equal(result, MORSE_CONTINUE);
    result = morse_push_symbol(&morse, MORSE_DIT);
    assert_int_equal(result, MORSE_CONTINUE);
    result = morse_push_symbol(&morse, MORSE_DIT);
    assert_int_equal(result, MORSE_CONTINUE);
    result = morse_push_symbol(&morse, MORSE_DIT);
    assert_int_equal(result, MORSE_CONTINUE);
    result = morse_push_symbol(&morse, MORSE_DIT);
    assert_int_equal(result, MORSE_CONTINUE);
    result = morse_get_value(&morse, &output);
    assert_int_equal(result, MORSE_DONE);
    assert_int_equal(output, '5');
}
 
void morse_stream_invalid() {
    morse_parser morse;
    morse_reset(&morse);

    char output;

    //..--
    morse_state result = morse_push_symbol(&morse, MORSE_DIT);
    assert_int_equal(result, MORSE_CONTINUE);
    result = morse_push_symbol(&morse, MORSE_DIT);
    assert_int_equal(result, MORSE_CONTINUE);
    result = morse_push_symbol(&morse, MORSE_DAH);
    assert_int_equal(result, MORSE_CONTINUE);
    result = morse_push_symbol(&morse, MORSE_DAH);
    assert_int_equal(result, MORSE_CONTINUE);
    result = morse_get_value(&morse, &output);
    assert_int_equal(result, MORSE_INVALID_SEQUENCE);

    morse_reset(&morse);

    // sequence too long
    result = morse_push_symbol(&morse, MORSE_DIT);
    assert_int_equal(result, MORSE_CONTINUE);
    result = morse_push_symbol(&morse, MORSE_DIT);
    assert_int_equal(result, MORSE_CONTINUE);
    result = morse_push_symbol(&morse, MORSE_DIT);
    assert_int_equal(result, MORSE_CONTINUE);
    result = morse_push_symbol(&morse, MORSE_DIT);
    assert_int_equal(result, MORSE_CONTINUE);
    result = morse_push_symbol(&morse, MORSE_DIT);
    assert_int_equal(result, MORSE_CONTINUE);
    result = morse_push_symbol(&morse, MORSE_DIT);
    assert_int_equal(result, MORSE_INVALID_SEQUENCE);
}
 
int main(void) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(morse_from_text_small_buf),
    cmocka_unit_test(morse_from_text_fits_buf),
    cmocka_unit_test(morse_from_text_larger_than_buf),
    cmocka_unit_test(morse_from_text_invalid_char),
    cmocka_unit_test(morse_to_text_single_char),
    cmocka_unit_test(morse_to_text_multi_char),
    cmocka_unit_test(morse_to_text_small_buf),
    cmocka_unit_test(morse_to_text_invalid),
    cmocka_unit_test(morse_stream_single_char),
    cmocka_unit_test(morse_stream_multi_char),
    cmocka_unit_test(morse_stream_invalid)
  };
 
  return cmocka_run_group_tests(tests, NULL, NULL);
}
