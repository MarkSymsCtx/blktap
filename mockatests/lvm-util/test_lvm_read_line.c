#include "lvm-util_test.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern int
lvm_read_line(FILE *scan);

extern char line[1024];

/* XXX: move to 'lvm-util.c' */
#define LINE_LEN 1024

void
test_lvm_read_line_under_no_nl(void **state)
{
	char  *test_line;
	char  *zeros;
	size_t test_line_len;
	size_t zeros_len;

	FILE *input = fopen("test/underflow_no_nl", "r");

	lvm_read_line(input);

	test_line_len = ftell(input);
	test_line = calloc(1, test_line_len + 1);

	rewind(input);
	fread(test_line, test_line_len, 1, input);

	fclose(input);

	zeros_len = LINE_LEN - test_line_len;
	zeros = calloc(1, zeros_len);

	assert_string_equal(line, test_line);
	assert_memory_equal(line + test_line_len, zeros, zeros_len);

	free(test_line);
	free(zeros);
}

void
test_lvm_read_line_under_nl(void **state)
{
	char  *test_line;
	char  *zeros;
	size_t test_line_len;
	size_t zeros_len;
	char  *nl = NULL;

	FILE *input = fopen("test/underflow_nl", "r");

	lvm_read_line(input);

	fseek(input, 0L, SEEK_END);
	test_line_len = ftell(input);
	test_line = calloc(1, test_line_len + 1);

	rewind(input);
	fread(test_line, test_line_len, 1, input);

	fclose(input);

	nl = strchr(test_line, '\n');
	*nl = '\0';

	zeros_len = LINE_LEN - (nl - test_line);
	zeros = calloc(1, zeros_len);

	assert_string_equal(line, test_line);
	assert_memory_equal(line + (nl - test_line), zeros, zeros_len);

	free(test_line);
	free(zeros);
}

void
test_lvm_read_line_over(void **state)
{
	char  *test_line;
	size_t test_line_len;

	FILE *input = fopen("test/overflow", "r");

	lvm_read_line(input);

	fseek(input, 0L, SEEK_END);
	test_line_len = ftell(input);
	test_line = calloc(1, test_line_len + 1);

	rewind(input);
	fread(test_line, test_line_len, 1, input);

	fclose(input);

	test_line[LINE_LEN - 1] = '\0';

	assert_string_equal(line, test_line);

	free(test_line);
}

const struct CMUnitTest lvm_read_line_tests[] = {
	cmocka_unit_test(test_lvm_read_line_under_no_nl),
	cmocka_unit_test(test_lvm_read_line_under_nl),
	cmocka_unit_test(test_lvm_read_line_over),
};

const struct CMUnitTest *get_lvm_read_line_tests()
{
	return lvm_read_line_tests;
}
