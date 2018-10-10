#include "../srcs/ft_bsq_util.c"
#include "../srcs/ft_stdio.c"
#include "rag.h"

int main()
{
	char header_1[] = "10000.ox";
	char header_2[] = "12345678";
	char header_3[] = "f00bar";
	char header_4[] = "1af";
	char header_5[] = "";
	char header_6[] = "123\n";  // invalid
	char header_7[] = "1234\n"; // valid
	char header_8[] = "a234\n"; // invalid
	char header_8[] = "+2345\n"; // valid
	char header_8[] = "-2345\n"; // valid

	int err;

	t_file_info	info;
	info.empty = 0;
	info.full = 0;
	info.height = 0;
	info.obstacle = 0;
	info.width = 0;

	err = read_bsq_header(header_1, &info);
	ASSERT_EQUAL(err, 0);
	ASSERT_EQUAL(info.empty, '.');
	ASSERT_EQUAL(info.obstacle, 'o');
	ASSERT_EQUAL(info.full, 'x');
	ASSERT_EQUAL(info.height, 10000);

	err = read_bsq_header(header_2, &info);
	ASSERT_EQUAL(err, 0);
	ASSERT_EQUAL(info.empty, '6');
	ASSERT_EQUAL(info.obstacle, '7');
	ASSERT_EQUAL(info.full, '8');
	ASSERT_EQUAL(info.height, 12345);

	err = read_bsq_header(header_3, &info);
	ASSERT_NOT_EQUAL(err, 0);

	err = read_bsq_header(header_4, &info);
	ASSERT_NOT_EQUAL(err, 0);

	err = read_bsq_header(header_5, &info);
	ASSERT_NOT_EQUAL(err, 0);
}
