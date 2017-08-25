#include <unistd.h>
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>
#include <morse.h>
 
void morse_from_ascii_small_buf() {
    morse_parser morse;
    morse_init(&morse);

    int buf_len = 1;
    char buf[buf_len];
    size_t fill_len;

    morse_state result = morse_from_ascii(&morse, "ABC", 3, buf, buf_len, &fill_len);
    assert_int_equal(result, MORSE_ERROR);
}

void morse_from_ascii_fits_buf() {
    morse_parser morse;
    morse_init(&morse);

    int buf_len = 6;
    char buf[buf_len];
    size_t fill_len;

    morse_state result = morse_from_ascii(&morse, "A", 1, buf, buf_len, &fill_len);
    assert_int_equal(result, MORSE_DONE);
    assert_memory_equal(buf, ".-", 2);
}

void morse_from_ascii_larger_than_buf() {
    morse_parser morse;
    morse_init(&morse);

    int buf_len = 7;
    char buf[buf_len];
    size_t fill_len;

    morse_state result = morse_from_ascii(&morse, "ABCD", 4, buf, buf_len, &fill_len);
    assert_int_equal(result, MORSE_CONTINUE);
    assert_int_equal(fill_len, 6);
    assert_memory_equal(buf, ".--...", 6);

    result = morse_from_ascii(&morse, "ABCD", 4, buf, buf_len, &fill_len);
    assert_int_equal(result, MORSE_CONTINUE);
    assert_int_equal(fill_len, 4);
    assert_memory_equal(buf, "-.-.", 4);

    result = morse_from_ascii(&morse, "ABCD", 4, buf, buf_len, &fill_len);
    assert_int_equal(result, MORSE_DONE);
    assert_int_equal(fill_len, 3);
    assert_memory_equal(buf, "-..", 3);
}
 
 
int main(void)
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(morse_from_ascii_small_buf),
    cmocka_unit_test(morse_from_ascii_fits_buf),
    cmocka_unit_test(morse_from_ascii_larger_than_buf)
  };
 
  return cmocka_run_group_tests(tests, NULL, NULL);
}
