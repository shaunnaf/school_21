#ifndef TEST_DECIMAL_H
#define TEST_DECIMAL_H

#include <check.h>
Suite *suite_truncate(void);
Suite *suite_not_equal_test(void);
Suite *suite_equal_test(void);
Suite *suite_greate_equal_test(void);
Suite *suite_greater_test(void);
Suite *suite_less_equal_test(void);
Suite *suite_less_test(void);
Suite *suite_floor(void);
Suite *suite_round(void);
Suite *suite_mul_test(void);
Suite *suite_div_test(void);
Suite *suite_sub_test(void);
Suite *suite_add_test(void);
Suite *suite_add(void);
Suite *suite_sub(void);
Suite *suite_mul(void);
Suite *suite_div(void);
Suite *suite_mod(void);

Suite *suite_from_int_to_decimal(void);
Suite *suite_from_float_to_decimal(void);
Suite *suite_from_decimal_to_int(void);
Suite *suite_from_decimal_to_float(void);

Suite *suite_floor(void);
Suite *suite_round(void);
Suite *suite_truncate(void);
Suite *suite_negate(void);

/* Auxiliary functions */

#endif
