#include "s21_math.h"

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double op1;
    double op2;
} test_struct_dd;

// s21_abs

int test_pack_abs[] = {0, -0, 10, -10, INT_MAX, INT_MIN};

START_TEST(test_abs) { ck_assert_int_eq(s21_abs(test_pack_abs[_i]), abs(test_pack_abs[_i])); }
END_TEST

// s21_acos

double test_pack_acos[] = {
    0.,          -0.,        1.23456e-7,    -1.23456e-7,   0.5,     -0.5,      0.99,      -0.99,
    1.,          -1.,        1.1,           -1.1,          10,      -10,       15.01,     -15.01,
    -9999999999, 9999999999, -S21_INFINITY, -S21_INFINITY, S21_NAN, TOLERANCE, -TOLERANCE};

START_TEST(test_acos) {
    if isnan (acos(test_pack_acos[_i])) {
        ck_assert_ldouble_nan(s21_acos(test_pack_acos[_i]));
    } else {
        ck_assert_ldouble_eq_tol(s21_acos(test_pack_acos[_i]), acos(test_pack_acos[_i]), TOLERANCE);
    }
}
END_TEST

// s21_asin

double test_pack_asin[] = {
    0.,          -0.,        1.23456e-7,    -1.23456e-7,   0.5,     -0.5,      0.99,      -0.99,
    1,           -1,         1.1,           -1.1,          10,      -10,       15.01,     -15.01,
    -9999999999, 9999999999, -S21_INFINITY, -S21_INFINITY, S21_NAN, TOLERANCE, -TOLERANCE};

START_TEST(test_asin) {
    if isnan (asin(test_pack_asin[_i])) {
        ck_assert_ldouble_nan(s21_asin(test_pack_asin[_i]));
    } else {
        ck_assert_ldouble_eq_tol(s21_asin(test_pack_asin[_i]), asin(test_pack_asin[_i]), TOLERANCE);
    }
}
END_TEST

// s21_atan

double test_pack_atan[] = {
    0.,          -0.,        1.23456e-7,    -1.23456e-7,   0.5,     -0.5,      0.99,      -0.99,
    1,           -1,         1.1,           -1.1,          10,      -10,       15.01,     -15.01,
    -9999999999, 9999999999, -S21_INFINITY, -S21_INFINITY, S21_NAN, TOLERANCE, -TOLERANCE};

START_TEST(test_atan) {
    if isnan (atan(test_pack_atan[_i])) {
        ck_assert_ldouble_nan(s21_atan(test_pack_atan[_i]));
    } else {
        ck_assert_ldouble_eq_tol(s21_atan(test_pack_atan[_i]), atan(test_pack_atan[_i]), TOLERANCE);
    }
}
END_TEST

// s21_ceil

double test_pack_ceil[] = {0.,
                           -0.,
                           0.1,
                           -0.1,
                           0.6,
                           -0.6,
                           10.5,
                           -10.5,
                           1.0e-50,
                           -1.0e-50,
                           1.0e-53,
                           -1.0e-53,
                           1.1234567890123456789e50,
                           -1.1234567890123456789e50,
                           1.1234567890123456789e53,
                           -1.1234567890123456789e53,
                           S21_NAN,
                           S21_INFINITY,
                           -S21_INFINITY};

START_TEST(test_ceil) {
    if isnan (ceil(test_pack_ceil[_i])) {
        ck_assert_ldouble_nan(s21_ceil(test_pack_ceil[_i]));
    } else {
        ck_assert_ldouble_eq(s21_ceil(test_pack_ceil[_i]), ceil(test_pack_ceil[_i]));
    }
}
END_TEST

// s21_cos

double test_pack_cos[] = {0.,
                          -0.,
                          0.5,
                          -0.5,
                          1,
                          -1,
                          10,
                          -10,
                          174.532925199433,
                          -174.532925199433,
                          S21_INFINITY,
                          -S21_INFINITY,
                          S21_NAN,
                          TOLERANCE,
                          -TOLERANCE};

START_TEST(test_cos) {
    if isnan (cos(test_pack_cos[_i])) {
        ck_assert_ldouble_nan(s21_cos(test_pack_cos[_i]));
    } else {
        ck_assert_double_eq_tol(s21_cos(test_pack_cos[_i]), cos(test_pack_cos[_i]), TOLERANCE);
    }
}
END_TEST

// s21_exp

double test_pack_exp[] = {0,
                          0.5,
                          1,
                          2,
                          3,
                          1.5,
                          -1.5,
                          0.5,
                          -0.5,
                          6,
                          -10,
                          /* 100,*/ -100,
                          715,
                          -715,
                          -0,
                          S21_NAN,
                          S21_INFINITY,
                          -S21_INFINITY};

START_TEST(test_exp) {
    if isnan (exp(test_pack_exp[_i])) {
        ck_assert_ldouble_nan(s21_exp(test_pack_exp[_i]));
    } else if isinf (exp(test_pack_exp[_i])) {
        ck_assert_ldouble_infinite(s21_exp(test_pack_exp[_i]));
    } else {
        ck_assert_double_eq_tol(s21_exp(test_pack_exp[_i]), exp(test_pack_exp[_i]), TOLERANCE);
    }
}
END_TEST

// s21_fabs

double test_pack_fabs[] = {0.,        -0.,     21.000345,    -21.000345,    -2147483600.543, 2147483600.4857,
                           DBL_MAX,   DBL_MIN, S21_INFINITY, -S21_INFINITY, S21_NAN,         TOLERANCE,
                           -TOLERANCE};

START_TEST(test_fabs) {
    if (isinf(fabs(test_pack_fabs[_i]))) {
        ck_assert_ldouble_infinite(s21_fabs(test_pack_fabs[_i]));
    } else if (isnan(fabs(test_pack_fabs[_i]))) {
        ck_assert_ldouble_nan(s21_fabs(test_pack_fabs[_i]));
    } else {
        ck_assert_ldouble_eq_tol(s21_fabs(test_pack_fabs[_i]), fabs(test_pack_fabs[_i]), TOLERANCE);
    }
}
END_TEST

// s21_floor

double test_pack_floor[] = {0.,
                            -0.,
                            0.1,
                            -0.1,
                            0.6,
                            -0.6,
                            10.5,
                            -10.5,
                            1.0e-50,
                            -1.0e-50,
                            1.0e-53,
                            -1.0e-53,
                            1.1234567890123456789e50,
                            -1.1234567890123456789e50,
                            1.1234567890123456789e53,
                            -1.1234567890123456789e53,
                            S21_NAN,
                            S21_INFINITY,
                            -S21_INFINITY};

START_TEST(test_floor) {
    if isnan (floor(test_pack_floor[_i])) {
        ck_assert_ldouble_nan(s21_floor(test_pack_floor[_i]));
    } else {
        ck_assert_double_eq(s21_floor(test_pack_ceil[_i]), floor(test_pack_ceil[_i]));
    }
}
END_TEST

// s21_fmod

test_struct_dd test_pack_fmod[] = {
    {2.34, 2.0},
    {-2.34, 2.0},
    {2.34, -2.0},
    {-2.34, -2.0},
    {21.21, 3},
    {3, 21.21},
    {-21.21, 3},
    {3, -21.21},
    {100500, 9},
    {-100500, -9},
    {-9, -100500},  // #10
    {-9, -9},
    {S21_INFINITY, S21_INFINITY},
    {S21_NAN, S21_NAN},
    {0, 23},
    {2.45, 0},
    {0, 0},
    {S21_INFINITY, 0},
    {S21_NAN, 2.0},
    {2.0, S21_NAN},
    {2.0, S21_INFINITY},  // #20
    {2.0, -S21_INFINITY},
};

START_TEST(test_fmod) {
    if isnan (fmod(test_pack_fmod[_i].op1, test_pack_fmod[_i].op2)) {
        ck_assert_ldouble_nan(s21_fmod(test_pack_fmod[_i].op1, test_pack_fmod[_i].op2));
    } else {
        ck_assert_double_eq_tol(s21_fmod(test_pack_fmod[_i].op1, test_pack_fmod[_i].op2),
                                fmod(test_pack_fmod[_i].op1, test_pack_fmod[_i].op2), TOLERANCE);
    }
}
END_TEST

// s21_log

double test_pack_log[] = {-0.1, 0, 1.1e-80, 1.1e-11,          9.234578353457e-6, 0.1,           0.7,
                          2.5,  3, 10,      9.234578353457e6, S21_INFINITY,      -S21_INFINITY, S21_NAN};

START_TEST(test_log) {
    if isnan (log(test_pack_log[_i])) {
        ck_assert_ldouble_nan(s21_log(test_pack_log[_i]));
    } else if (isinf(log(test_pack_log[_i]))) {
        ck_assert_ldouble_infinite(s21_log(test_pack_log[_i]));
    } else {
        ck_assert_double_eq_tol(s21_log(test_pack_log[_i]), log(test_pack_log[_i]), TOLERANCE);
    }
}
END_TEST


// s21_pow

test_struct_dd test_pack_pow[] = {
    {0, 0},
    {1., 1.},

    {3, S21_INFINITY},
    {-3, S21_INFINITY},
    {0.3, S21_INFINITY},
    {-0.3, S21_INFINITY},
    {S21_INFINITY, S21_INFINITY},
    {-S21_INFINITY, S21_INFINITY},
    {S21_NAN, S21_INFINITY},

    {3, -S21_INFINITY},
    {-3, -S21_INFINITY},  // # 10
    {0.3, -S21_INFINITY},
    {-0.3, -S21_INFINITY},
    {S21_INFINITY, -S21_INFINITY},
    {-S21_INFINITY, -S21_INFINITY},
    {S21_NAN, -S21_INFINITY},

    {3, S21_NAN},
    {-3, S21_NAN},
    {0.3, S21_NAN},
    {-0.3, S21_NAN},
    {S21_INFINITY, S21_NAN},  // # 20
    {-S21_INFINITY, S21_NAN},
    {S21_NAN, S21_NAN},

    {3, 3},
    {-3, 3},
    {0.3, 3},
    {-0.3, 3},
    {S21_INFINITY, 3},
    {-S21_INFINITY, 3},
    {S21_NAN, 3},

    {3, -3},  // # 30
    {-3, -3},
    {0.3, -3},
    {-0.3, -3},
    {S21_INFINITY, -3},
    {-S21_INFINITY, -3},
    {S21_NAN, -3},

    {3, 0.3},
    {-3, 0.3},
    {0.3, 0.3},
    {-0.3, 0.3},  // # 40
    {S21_INFINITY, 0.3},
    {-S21_INFINITY, 0.3},
    {S21_NAN, 0.3},

    {3, -0.3},
    {-3, -0.3},
    {0.3, -0.3},
    {-0.3, -0.3},
    {S21_INFINITY, -0.3},
    {-S21_INFINITY, -0.3},
    {S21_NAN, -0.3},

    {0, 3},
    {0, 0.3},
    {0, -0.3},
    {0, -3},
};

START_TEST(test_pow) {
    if isnan (pow(test_pack_pow[_i].op1, test_pack_pow[_i].op2)) {
        ck_assert_ldouble_nan(s21_pow(test_pack_pow[_i].op1, test_pack_pow[_i].op2));
    } else if (isinf(pow(test_pack_pow[_i].op1, test_pack_pow[_i].op2))) {
        ck_assert_ldouble_infinite(s21_pow(test_pack_pow[_i].op1, test_pack_pow[_i].op2));
    } else {
        ck_assert_double_eq_tol(s21_pow(test_pack_pow[_i].op1, test_pack_pow[_i].op2),
                            pow(test_pack_pow[_i].op1, test_pack_pow[_i].op2), TOLERANCE);
    }
}
END_TEST

// s21_sin

double test_pack_sin[] = {0.,  -0.,          0.5,           -0.5,    1,         -1,        10,
                          -10, S21_INFINITY, -S21_INFINITY, S21_NAN, TOLERANCE, -TOLERANCE};

START_TEST(test_sin) {
    if isnan (sin(test_pack_sin[_i])) {
        ck_assert_ldouble_nan(s21_sin(test_pack_sin[_i]));
    } else {
        ck_assert_double_eq_tol(s21_sin(test_pack_sin[_i]), sin(test_pack_sin[_i]), TOLERANCE);
    }
}
END_TEST

// s21_sqrt

double test_pack_sqrt[] = {
    0.0,    -0.0,         0.5,       0.9999,      1.0,          1.1,           -15.01,  100,
    10e+16, 98765432.123, 981.123e6, 981.123e-15, S21_INFINITY, -S21_INFINITY, S21_NAN,
};

START_TEST(test_sqrt) {
    if isnan (sqrt(test_pack_sqrt[_i])) {
        ck_assert_ldouble_nan(s21_sqrt(test_pack_sqrt[_i]));
    } else if (isinf(sqrt(test_pack_sqrt[_i]))) {
        ck_assert_ldouble_infinite(s21_sqrt(test_pack_sqrt[_i]));
    } else {
        ck_assert_double_eq_tol(s21_sqrt(test_pack_sqrt[_i]), sqrt(test_pack_sqrt[_i]), TOLERANCE);
    }
}
END_TEST

// s21_tan

double test_pack_tan[] = {0.,  -0.,          0.5,           -0.5,    1,         -1,        10,
                          -10, S21_INFINITY, -S21_INFINITY, S21_NAN, TOLERANCE, -TOLERANCE};

START_TEST(test_tan) {
    if isnan (tan(test_pack_tan[_i])) {
        ck_assert_ldouble_nan(s21_tan(test_pack_tan[_i]));
    } else {
        ck_assert_double_eq_tol(s21_tan(test_pack_tan[_i]), tan(test_pack_tan[_i]), TOLERANCE);
    }
}
END_TEST

// main

int main() {
    Suite *s = suite_create("s21_math test");
    SRunner *sr = srunner_create(s);
    srunner_set_fork_status(sr, CK_NOFORK);
    TCase *tc = tcase_create("s21_math case");
    suite_add_tcase(s, tc);
    tcase_set_timeout(tc, 10);

    // s21_abs
    int test_pack_size = sizeof(test_pack_abs) / sizeof(int);
    tcase_add_loop_test(tc, test_abs, 0, test_pack_size);

    // s21_acos
    test_pack_size = sizeof(test_pack_acos) / sizeof(double);
    tcase_add_loop_test(tc, test_acos, 0, test_pack_size);

    // s21_asin
    test_pack_size = sizeof(test_pack_asin) / sizeof(double);
    tcase_add_loop_test(tc, test_asin, 0, test_pack_size);

    // s21_atan
    test_pack_size = sizeof(test_pack_atan) / sizeof(double);
    tcase_add_loop_test(tc, test_atan, 0, test_pack_size);

    // s21_ceil
    test_pack_size = sizeof(test_pack_ceil) / sizeof(double);
    tcase_add_loop_test(tc, test_ceil, 0, test_pack_size);

    // s21_cos
    test_pack_size = sizeof(test_pack_cos) / sizeof(double);
    tcase_add_loop_test(tc, test_cos, 0, test_pack_size);

    // s21_exp
    test_pack_size = sizeof(test_pack_exp) / sizeof(double);
    tcase_add_loop_test(tc, test_exp, 0, test_pack_size);

    // s21_fabs
    test_pack_size = sizeof(test_pack_fabs) / sizeof(double);
    tcase_add_loop_test(tc, test_fabs, 0, test_pack_size);

    // s21_floor
    test_pack_size = sizeof(test_pack_floor) / sizeof(double);
    tcase_add_loop_test(tc, test_floor, 0, test_pack_size);

    // s21_fmod
    test_pack_size = sizeof(test_pack_fmod) / sizeof(test_struct_dd);
    tcase_add_loop_test(tc, test_fmod, 0, test_pack_size);

    // s21_log
    test_pack_size = sizeof(test_pack_log) / sizeof(double);
    tcase_add_loop_test(tc, test_log, 0, test_pack_size);

    // s21_pow
    test_pack_size = sizeof(test_pack_pow) / sizeof(test_struct_dd);
    tcase_add_loop_test(tc, test_pow, 0, test_pack_size);

    // s21_sin
    test_pack_size = sizeof(test_pack_sin) / sizeof(double);
    tcase_add_loop_test(tc, test_sin, 0, test_pack_size);

    // s21_sqrt
    test_pack_size = sizeof(test_pack_sqrt) / sizeof(double);
    tcase_add_loop_test(tc, test_sqrt, 0, test_pack_size);

    // s21_tan
    test_pack_size = sizeof(test_pack_tan) / sizeof(double);
    tcase_add_loop_test(tc, test_tan, 0, test_pack_size);

    srunner_run_all(sr, CK_ENV);
    srunner_free(sr);
    return 0;
}