#include <stdio.h>
#include "../srcs/ft_bsq_util.c"
#include "../.debug/ft_error.c"
#include "../srcs/ft_stdio.c"
#include "rag.h"

int main()
{
	int ret;

	t_file_info	info;
	info.empty = 0;
	info.full = 0;
	info.height = 0;
	info.obstacle = 0;
	info.width = 0;

	char header_1[] = "10000.ox\n";
	ret = read_bsq_header(header_1, &info);
	assert(ret == 9);
	ASSERT_EQUAL(info.empty, '.');
	ASSERT_EQUAL(info.obstacle, 'o');
	ASSERT_EQUAL(info.full, 'x');
	ASSERT_EQUAL(info.height, 10000);

	char header_2[] = "12345678\n";
	ret = read_bsq_header(header_2, &info);
	assert(ret == 9);
	ASSERT_EQUAL(info.empty, '6');
	ASSERT_EQUAL(info.obstacle, '7');
	ASSERT_EQUAL(info.full, '8');
	ASSERT_EQUAL(info.height, 12345);

	char header_2_no_newline[] = "12345678";
	ret = read_bsq_header(header_2_no_newline, &info);
	assert(ret < 0);

	char header_3[] = "f00bar";
	ret = read_bsq_header(header_3, &info);
	assert(ret < 0);

	char header_4[] = "1af";
	ret = read_bsq_header(header_4, &info);
	assert(ret < 0);

	char header_5[] = "";
	ret = read_bsq_header(header_5, &info);
	assert(ret < 0);

	char header_6[] = "123\n";  // invalid
	ret = read_bsq_header(header_6, &info);
	assert(ret < 0);

	char header_7[] = "1234\n"; // valid
	ret = read_bsq_header(header_7, &info);
	ASSERT_EQUAL(info.height, 1);
	assert(ret == 5);

	char header_8[] = "a234\n"; // invalid
	ret = read_bsq_header(header_8, &info);
	assert(ret < 0);

	char header_9[] = "+2345\n"; // valid
	ret = read_bsq_header(header_9, &info);
	assert(ret == 6);

	char header_10[] = "-2345\n"; // invalid
	ret = read_bsq_header(header_10, &info);
	assert(ret < 0);
}
