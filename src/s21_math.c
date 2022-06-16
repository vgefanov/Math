#include "s21_math.h"
#include <stdio.h>
#include <float.h>


// Внутренние константы и типы

#define TRUE 1
#define FALSE 0
typedef unsigned short bool;

/**
 * @brief Сервисная функция усечения вниз или вверх (в зависимости от флага)
 *
 * @param x
 * @param is_ceil
 * @return long double
 */
long double ceil_or_floor(double x, bool is_ceil) {
    union {
       double dbl;
       char bits[8];
    } result;
    result.dbl = x;
    char sign = result.bits[7] & 0x80;
    if (x == x && s21_fabs(x) < 0x1.0p52) {
        double truncation = (long long)x;
        if (is_ceil) {
            result.dbl = truncation + (truncation < x);
        } else {
            result.dbl = truncation - (truncation > x);
        }
        result.bits[7] = result.bits[7] | sign;
    }
    return result.dbl;
}


/**
 * @brief Вычисляет log2 для x из диапазона [1;2]
 *
 * @param x
 * @return double
 */
double s21_log2(double x) {
    double s = 0.0;
    double a = 0.5;
    for (int i = 0; i < LOG2_LIMIT; i++) {
        x = x * x;
        if (x > 2) {
            x = x / 2;
            s += a;
        }
        a *=  0.5;
    }
    return s;
}


/**
 * @brief Вычисление арктангенса рядом Тейлора в области [0; pi/12]
 *
 * @param x
 * @return long double
 */
long double atan_p12(double x) {
    double x_accum = x;
    double atan_result = x_accum;
    for (int n = 2; n <= ATAN_LIMIT; n++) {
        double sign = (n % 2) ? 1. : -1.;
        x_accum = x_accum * x * x;
        atan_result += sign * x_accum / (2 * n - 1);
    }
    return atan_result;
}


// s21_abs

int s21_abs(int x) {
    return (x > 0) ? x : -x;
}


// s21_acos

long double s21_acos(double x) {
    return ((x > 1) || (x < -1)) ? S21_NAN : S21_PI_2 - s21_asin(x);
}


// s21_asin

long double s21_asin(double x) {
    double asin_result = S21_NAN;
    if ((x == 1) || (x == -1)) {
        asin_result = x * S21_PI_2;
    } else if ((x > -1) && (x < 1)) {
        asin_result = s21_atan(x / s21_sqrt(1 - x * x));
    }
    return asin_result;
}


// s21_atan

long double s21_atan(double x) {
    bool sign_change = FALSE;
    bool inverse = FALSE;
    if (x < 0) {
        x = -x;
        sign_change = TRUE;
    }
    if (x > 1) {
        x = 1 / x;
        inverse = TRUE;
    }
    int num_of_steps = 0;
    for (; x > S21_PI_12; num_of_steps++) {
        double a = 1 / (x + SQRT3);
        x = (x * SQRT3 - 1) * a;
    }
    double result = atan_p12(x) + S21_PI_6 * num_of_steps;
    if (inverse) {
        result = S21_PI_2 - result;
    }
    if (sign_change) {
        result = -result;
    }
    return result;
}


// s21_ceil

long double s21_ceil(double x) {
    return ceil_or_floor(x, TRUE);
}


// s21_cos

long double s21_cos(double x) {
    double inverse = 1;
    x = s21_fabs(x);
    x = s21_fmod(x, 2 * S21_PI);
    if (x > S21_PI) {
        x = S21_PI - x;
        inverse = -1;
    }
    double cos_result = 1;
    double x_accum = 1;
    double factorial = 1;
    for (int i = 2; i <= COS_LIMIT; i += 2) {
        int sign = (i % 4) ? -1 : 1;
        x_accum = x_accum * x * x;
        factorial *= (i - 1) * i;
        cos_result += sign * x_accum / factorial;
    }
    return inverse * cos_result;
}


// s21_exp

long double exp_fractional(double x) {
    double x_accum = 1;
    double exp_result = x_accum;
    double factorial = 1;
    for (int i = 1; i <= EXP_LIMIT; i++) {
        x_accum *= x;
        factorial *= i;
        exp_result += x_accum / factorial;
    }
    return exp_result;
}

long double exp_intgr(int x) {
    int flag = 512;
    long double result = 1;
    while (flag > 0) {
        result = result * result;
        if (x & flag) {
            result = result * S21_E;
        }
        flag >>= 1;
    }
    return result;
}

long double s21_exp(double x) {
    double exp_result = 0;
    if (x < -38) {
        exp_result = 0;
    } else if (x > 709) {
        exp_result = S21_INFINITY;
    } else {
        if (x > 5 || x < -5) {
            double x_pos = s21_fabs(x);
            int x_int = (int)x_pos;
            double x_frac = x_pos - x_int;
            exp_result = exp_intgr(x_int) * exp_fractional(x_frac);
            if (x < 0) {
                exp_result = 1 / exp_result;
            }
        } else {
            exp_result = exp_fractional(x);
        }
    }
    return exp_result;
}


// s21_fabs

long double s21_fabs(double x) {
    return (x > 0) ? x : -x;
}


// s21_floor

long double s21_floor(double x) {
    return ceil_or_floor(x, FALSE);
}


// s21_fmod

long double s21_fmod(double x, double y) {
    double div = x / y;
    if (div == div && s21_fabs(div) < 0x1.0p52) {
        div = (long long)div;
    }
    return (s21_fabs(x) != S21_INFINITY && s21_fabs(y) == S21_INFINITY) ? x : x - div * y;
}


// s21_log

long double s21_log(double x) {
    long double result = S21_NAN;
    if (x == 0) {
        result = -S21_INFINITY;
    } else if (x == S21_INFINITY) {
        result = S21_INFINITY;
    } else if (x > 0) {
        result = 0;
        while (x < 1) {
            x *= 2;
            result--;
        }
        while (x > 2) {
            x /= 2;
            result++;
        }
        result = (result + s21_log2(x)) / S21_LOG2E;
    }
    return result;
}


// s21_pow

long double s21_pow(double base, double exp) {
    long double result;
    if (exp == 0) {
        result = 1;
    } else if (base != base || exp != exp) {
        result = S21_NAN;
    } else if (exp == -S21_INFINITY) {
        result = 0;
        if (base > -1 && base < 1) {
            result = S21_INFINITY;
        }
    } else if (exp == S21_INFINITY) {
        result = S21_INFINITY;
        if (base < 1 && base > -1) {
            result = 0;
        }
    } else if (base == -S21_INFINITY) {
        result = 0;
        if (exp > 0) {
            result = S21_INFINITY;
        }
        if (exp >= 1) {
            result = -S21_INFINITY;
        }
    } else if (base == S21_INFINITY) {
        result = (exp > 0) ? S21_INFINITY : 0;
    } else if (base < 0 && exp != s21_ceil(exp)) {
        result = S21_NAN;
    } else {
        int reverse = 1;
        if (base < 0) {
            base = -base;
            reverse = -1;
        }
        result = reverse * s21_exp(exp * s21_log(base));
    }
    return result;
}


// s21_sin

long double s21_sin(double x) {
    return s21_cos(x - S21_PI_2);
}


// s21_sqrt

long double s21_sqrt(double x) {
    long double result = .0;
    result /= .0;
    if (x == S21_INFINITY) {
        result = 1.0 / 0.0;
    } else if (x >= 0) {
        double a = 1;
        double b = x;
        while (s21_fabs(a - b) > TOLERANCE) {
            a = (a + b) / 2;
            b = x / a;
        }
        result = (a + b) / 2;
    }
    return result;
}


// s21_tan

long double s21_tan(double x) {
    return s21_sin(x) / s21_cos(x);
}
