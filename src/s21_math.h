long double exp_intgr(int x);

#define TOLERANCE 1e-6


// Лимиты на точность: больше - точнее

#define ASIN_LIMIT 12
#define ATAN_LIMIT 12
#define COS_LIMIT  15
#define EXP_LIMIT  20
#define LOG2_LIMIT 32

#define S21_E        2.71828182845904523536028747135266250  // e
#define S21_PI       3.14159265358979323846264338327950288  // pi
#define S21_PI_2     1.57079632679489661923132169163975144  // pi/2
#define S21_PI_6     0.52359877559829881565889309058547951  // pi/6
#define S21_PI_12    0.26179938779914940782944654529273976  // pi/12
#define S21_LOG2E    1.44269504088896340735992468100189214  // log2(e)
#define SQRT3        1.73205080756887719317660412343684584  // sqrt(3)
#define S21_NAN      0./0.
#define S21_INFINITY 1./0.


/**
 * @brief вычисляет абсолютное значение целого числа
 *
 * @param x
 * @return int
 */
int s21_abs(int x);

/**
 * @brief вычисляет арккосинус
 *
 * @param x
 * @return long double
 */
long double s21_acos(double x);

/**
 * @brief вычисляет арксинус
 *
 * @param x
 * @return long double
 */
long double s21_asin(double x);

/**
 * @brief вычисляет арктангенс
 *
 * @param x
 * @return long double
 */
long double s21_atan(double x);

/**
 * @brief возвращает ближайшее целое число, не меньшее заданного значения
 *
 * @param x
 * @return long double
 */
long double s21_ceil(double x);

/**
 * @brief вычисляет косинус
 *
 * @param x
 * @return long double
 */
long double s21_cos(double x);

/**
 * @brief возвращает значение e, возведенное в заданную степень
 *
 * @param x
 * @return long double
 */
long double s21_exp(double x);

/**
 * @brief вычисляет абсолютное значение числа с плавающей точкой
 *
 * @param x
 * @return long double
 */
long double s21_fabs(double x);

/**
 * @brief возвращает ближайшее целое число, не превышающее заданное значение
 *
 * @param x
 * @return long double
 */
long double s21_floor(double x);

/**
 * @brief остаток операции деления с плавающей точкой
 *
 * @param x
 * @param y
 * @return long double
 */
long double s21_fmod(double x, double y);

/**
 * @brief вычисляет натуральный логарифм
 *
 * @param x
 * @return long double
 */
long double s21_log(double x);

/**
 * @brief // возводит число в заданную степень
 *
 * @param base
 * @param exp
 * @return long double
 */
long double s21_pow(double base, double exp);

/**
 * @brief вычисляет синус
 *
 * @param x
 * @return long double
 */
long double s21_sin(double x);

/**
 * @brief вычисляет квадратный корень
 *
 * @param x
 * @return long double
 */
long double s21_sqrt(double x);

/**
 * @brief вычисляет тангенс
 *
 * @param x
 * @return long double
 */
long double s21_tan(double x);
