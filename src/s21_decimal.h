#ifndef SRC_DECIMAL_H_
#define SRC_DECIMAL_H_
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S21_MAX_FLOAT 79228162514264337593543950335
#define S21_MIN_FLOAT 1e-28

#define S21_INT_MAX 2147483647
#define S21_INT_MIN -2147483648
#define S21_INF 1.0 / 0.0
#define S21_MAX_UINT 4294967295

typedef struct {
  unsigned int bits[4];
} s21_decimal;
typedef struct {
  unsigned int bits[6];
} big_d;

typedef unsigned int d_int;
enum des_enum { STEPEN, DECIMAL };
enum des_result_func { RES_OK, RES_OVERFLOW, RES_UNDERFLOW, RES_NULL };
enum des_comparison { EQUAL, MORE, LESS };
enum des_div_round { NO_ROUND, ROUND, ROUND_B, ROUND_MOD };
enum even_numbered { NOT_EVEN, EVEN };
enum arithmetic_operations { ADD, SUB, DIV, MUL };

// ------------------------------- decimal
int getbit_bd(big_d value, int bit);
void des_set_bit_bd(big_d *dec, int bit, int status);
int des_shift_left_bd(big_d *dec, int shift);
int des_comparison_mantissa_bd(big_d dec1, big_d dec2);
void s21_dec_null_bd(big_d *dec);
void des_sub_mantissa_bd(big_d dec1, big_d dec2, big_d *res);
void des_shift_right_bd(big_d *dec, int shift);
int des_div_mantissa_exp_bd(big_d a, big_d b, big_d *res);
big_d des_round_div_mantissa_bd(big_d a, big_d b, big_d *res, int round);
int ten_func_bd(big_d ten, big_d *ten_res);
int des_r_div_mant_bd(big_d ost, big_d b, big_d *result);
int des_div_mantissa_bd(big_d dec1, big_d dec2, big_d *res, big_d *mod,
                        int round);
int des_m_nul_bd(big_d dec);
void exp_round_left(s21_decimal *a, s21_decimal *b, int *exp);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

/**
 * @brief Складывает два децимала
 * @param value_1,value_2 децималы, которые будут складываться
 * @return 0 - ОК, 1 - Переполнение
 * @author Desperos
 */
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/**
 * @brief Вычитает два децимала
 * @param value_1,value_2 децималы, которые будут складываться
 * @return 0 - ОК, 1 - Переполнение
 * @author Desperos
 */
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/**
 * @brief Делит первый децимал на второй
 * @param value_1 децимал, делимое
 * @param value_2 децимал, делитель
 * @return 0 - RES_ОК, 3 - RES_NULL(Деление на ноль)
 * @author Desperos
 */
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/**
 * @brief value_1 < value_2, Функция сравнения децималов
 * @param value_1,value_2 децимал, value_1 меньше чем value_2
 * @return 0 - FALSE, 1 - TRUE
 * @author Desperos
 */
int s21_is_less(s21_decimal value_1, s21_decimal value_2);

/**
 * @brief value_1 <= value_2, Функция сравнения децималов
 * @param value_1,value_2 децимал, value_1 меньше или равно чем value_2
 * @return 0 - FALSE, 1 - TRUE
 * @author Desperos
 */
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);

/**
 * @brief value_1 > value_2, Функция сравнения децималов
 * @param value_1,value_2 децимал, value_1 больше чем value_2
 * @return 0 - FALSE, 1 - TRUE
 * @author Desperos
 */
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);

/**
 * @brief value_1 >= value_2, Функция сравнения децималов
 * @param value_1,value_2 децимал, value_1 больше или равно чем value_2
 * @return 0 - FALSE, 1 - TRUE
 * @author Desperos
 */
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);

/**
 * @brief value_1 = value_2, Функция сравнения децималов
 * @param value_1,value_2 децимал, value_1 равно value_2
 * @return 0 - FALSE, 1 - TRUE
 * @author Desperos
 */
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);

/**
 * @brief value_1 != value_2, Функция сравнения децималов
 * @param value_1,value_2 децимал, value_1 НЕ равно value_2
 * @return 0 - FALSE, 1 - TRUE
 * @author Desperos
 */
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int des_mul_mant_big(s21_decimal dec1, s21_decimal dec2, s21_decimal *res);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_isnull_dec(s21_decimal value);
int s21_get_exp(s21_decimal value);

// -------------------- Input and Output decimal

// нужен для s21_printf_decimal. Автор Fartlouv
int call_of_me(int row);

// нужен для s21_printf_decimal. Автор Fartlouv
int call_of_me_stop_me(int row);

// выводит вид decimal . Автор Fartlouv + Desperos
void s21_printf_decimal(s21_decimal value);

/**
 * @brief выводит мантису в строке из указанного децимала
 * @param value Децимал из которого нужен вывод мантисы
 * @author Desperos
 */
void s21_from_decimal_to_int_mantisa(s21_decimal value);

/**
 * @brief Реверс символов в строке. Реверс в том же указателе.
 * @param str строка, в которой нужно сделать реверс
 * @author Desperos
 */
void des_rev_str(char *str);

/**
 * @brief конвертер двоичная строка в число Int. Возвращает сконвертированное
 * число Int.
 * @param buf строка, из которой берем число
 * @param size количество символов в строке к изменению
 * @author Desperos
 */
int hex_to_int(char *buf, int size);

/**
 * @brief Конвертер из строки символов (10) в децимал (2), только мантиса
 * @param str Строка содержащая мантису децимала в 10 система счисления.
 * @param dec Децимал, в который будет записана мантиса.
 * @author Desperos
 */
void char_manstis_to_dec(char *str, s21_decimal *dec);

/**
 * @brief Преобразует число (10) в строку в нужной системе счисления.
 * @param value Число с тиов int, которое нужное преобразовать.
 * @param result Строка, куда будет помещено число в нужной СС.
 * @param base Система счисления, в которую нужно преобразование.
 * @author Desperos
 */
char *itoa(int value, char *result, int base);

/**
 * @brief  Складывает два числа в массиве символов.
 * @param str1,str2 Строки с числами из символов для сложения.
 * @param res Строка, в которой будет результат сложения.
 * @author Desperos
 */
void des_str1_plus_str2(char *str, char *str2, char *res);

/**
 * @brief Умножение двойки на выбранную степень.
 * @param str Строка содержащая число в 10 системе счисления. Она же содержит
 * результат функции.
 * @param step Степень, в которую нужно возвести двойку.
 * @author Desperos
 */
void des_2_v_pow(char *str, int step);

/**
 * @brief Умножает целое число, без точки и без знака, на 2 в массиве символов
 * @param str Строка содержащая число в 10 системе счисления.
 * @param res Строка в которой будет результат умноженный на 2 в 10 СС.
 * @author Desperos
 */
void des_str_x2(char *str, char *res);

/**
 * @brief  Достает из s21_decimal только мантису и кладет в строку.
 * @param dec Децимал, откуда получаем мантису иили степень.
 * @param str1 Строка, где будет результат.
 * @param d_enum Enum, для получения мантисы DECIMAL или степени STEPEN.
 * @author Desperos
 */
void des_mantisa_dec_to_str(s21_decimal *dec, char *str1, int d_enum);

/**
 * @brief Верхняя функция. Записывает число в 10 СС из массива символов в наш
 * децимал, без проверки переполнения, степени и знака.
 * @param buf Строка содержащая число в 10 система счисления с - и/или с точкой.
 * @param dec Децимал, в который будет записано мантиса, степень, знак.
 * @author Desperos
 */
void char_str_to_decimal(char *buf, s21_decimal *dec);

/**
 * @brief Верхняя функция. Записывает число в 10 CC из децимала в строку.
 * @see des_mantisa_dec_to_str()
 * @param dec Децимал, откуда получаем число.
 * @param res Строка, где будет результат в строке.
 * @author Desperos
 */
void des_dec_to_str(s21_decimal *dec, char *res);

// ---------------------- Desperos

/**
 * @brief Обнуляет все биты в децимал
 * @param dec Полное число децимал
 * @author Desperos
 */
// обнуляет все 128 битов в 0, степень принимает 127 (то есть ноль)
void s21_dec_null(s21_decimal *dec);

/**
 * @brief Устанавливет нужный бит в децимал
 * @param dec Полное число децимал
 * @param bit адрес нужного бита
 * @param status состояние бита
 * @author Desperos
 */
void des_set_bit(s21_decimal *dec, int bit, int status);

/**
 * @brief Получает степень числа децимал
 * @param dec Полное число децимал
 * @param 255 маска в виде int -> 0b11111111 для степени
 * @return int степень в 10 системе счисления
 * @author Desperos
 */
int des_get_exp(s21_decimal dec);

/**
 * @brief Устанавливает степень числа в децимал, знак остается какой был
 * @param dec Полное число децимал куда записываем степень
 * @param exp степень для записи int в 10 системе счисления
 * @author Desperos
 */
void des_set_exp(s21_decimal *dec, int exp);

/**
 * @brief Делает побитовый сдвиг влево, старшие биты отбрасываются. Только
 * мантиса, знак и степень сохраняются
 * @param dec Полное число децимал мантису которого двигаем влево
 * @param shift Число в 10 СС на которое будем двигать влево
 * @return Возвращает 0 - RES_OK и 1 - RES_OVERFLOW.
 * @author Desperos
 */
int des_shift_left(s21_decimal *dec, int shift);

/**
 * @brief Делает побитовый сдвиг вправо, младшие биты отбрасываются. Только
 * мантиса, знак и степень сохраняются
 * @param dec Полное число децимал мантису которого двигаем вправо
 * @param shift Число в 10 СС на которое будем двигать вправо
 * @author Desperos
 */
void des_shift_right(s21_decimal *dec, int shift);

/**
 * @brief обнуляет все 128 битов в 0.
 * @param dec Децимал, который нужно обнулить.
 * @author Desperos
 */
void s21_dec_null(s21_decimal *dec);

/**
 * @brief Складывает только мантисы в числах децимал, возращает перполнение
 * мантисы. При сложении задействует свободные биты в bits[3], после очищает
 * @param dec1,dec2 числа децимал, в которых нужно сложить мантисы
 * @param res число децимал, в которой будет сумма мантис, без знака и без
 * степени
 * @return Возвращает 0 - RES_OK и 1 - RES_OVERFLOW.
 * @author Desperos
 */
int des_add_mantissa(s21_decimal dec1, s21_decimal dec2, s21_decimal *res);

/**
 * @brief Сравнивает две мантиссы и возвращает результат
 * @param dec1,dec2 числа децимал, в которых нужно сравнить мантиссы
 * @return Возвращает состояние для dec1: 0 - EQUAL, 1 - MORE, 2 - LESS.
 * @author Desperos
 */
int des_comparison_mantissa(s21_decimal dec1, s21_decimal dec2);

/**
 * @brief Вложенная функция для des_sub_mantissa, выполняет инверсию битов
 * мантиссы и добавляет знаковый бит в 96 индекс.
 * @param dec1 децимал, в которых нужно сделать инверсию
 * @author Desperos
 */
void des_negate_mantissa(s21_decimal *dec);

/**
 * @brief Вычитание мантиссы
 * @param dec1,dec2 Из Первого вычитается второе.
 * @param res Помещается результат вычитания.
 * @author Desperos
 */
void des_sub_mantissa(s21_decimal dec1, s21_decimal dec2, s21_decimal *res);

/**
 * @brief Вложенная функция для des_div_mantissa, выполняет поиск степени для
 * делителя до делимого
 * @param a децимал, делимое, котороые будет смещаться
 * @param b децимал, делитель, котороые будет смещаться
 * @param c децимал, промежуточный результат для des_div_mantissa
 * @return степень числа a
 * @author Desperos
 */
int des_div_mantissa_exp(s21_decimal a, s21_decimal b, s21_decimal *c);

/**
 * @brief Вложенная функция округления частного после деления мантисс децимала
 * @param a децимал, делимое, остаток от деления
 * @param b децимал, делитель
 * @param res децимал, частное, результат деления
 * @param round Тип окгругления 0 - NO_ROUND (без, остаток в mod), 1 - ROUND
 * (математическое), 2 - ROUND_B(банковское), 3 - NO_ROUND_NO(без, дописывает
 * знаки дроби в свободное место мантиссы).
 * @return децимал, остаток от деления
 * @author Desperos
 */
s21_decimal des_round_div_mantissa(s21_decimal a, s21_decimal b,
                                   s21_decimal *res, int round);

/**
 * @brief Функция деления мантисс децимала
 * @param dec1 децимал, делимое
 * @param dec2 децимал, делитель
 * @param res децимал, частное, результат деления, которое округляем
 * @param mod децимал, остаток от деления
 * @param round Тип окгругления 0 - NO_ROUND (без, остаток в mod), 1 - ROUND
 * (математическое), 2 - ROUND_B(банковское), 3 - ROUND_MOD(без, дописывает
 * знаки дроби в свободное место мантиссы).
 * @return Статус функции: 0 - RES_OK, 3 - RES_NULL
 * @author Desperos
 */
int des_div_mantissa(s21_decimal dec1, s21_decimal dec2, s21_decimal *res,
                     s21_decimal *mod, int round);

/**
 * @brief Функция умноженя мантисс децимала
 * @param dec1,dec2 децимал, делимое, делитель
 * @param res децимал, Результат умножения
 * @return Возвращает 0 - RES_OK и 1 - RES_OVERFLOW.
 * @author Desperos
 */
int des_mul_mantissa(s21_decimal dec1, s21_decimal dec2, s21_decimal *res);

/**
 * @brief Функция деноменатор (нормализация) приводит два числа к одной степени,
 * саначало увеличивает степень, если степень максимальная или нет свободных
 * мест, то уменьшает степень второго числа.
 * @param dec1,dec2 децимал, делимое
 * @author Desperos
 */
void des_denomenator(s21_decimal *dec1, s21_decimal *dec2);

/**
 * @brief Функция проверяет есть ли у нуля мантисы знак минус, если есть,
 * убирает его.
 * @param dec1 децимал
 * @return Децимал с нулем в мантисе и степени, без знака.
 * @author Desperos
 */
s21_decimal des_is_minus_null(s21_decimal dec);

/**
 * @brief Функция складывает мантисы, с учетом их знака в 127 бите
 * @param dec1,dec2 децималы, могут быть с любыми знаками
 * @return Статус переполнения 0 - RES_OK, 1 - RES_OVERFLOW.
 * @author Desperos
 */
int des_add_sign_mant(s21_decimal dec1, s21_decimal dec2, s21_decimal *res);

/**
 * @brief Функция Определяет знак для мантисы после арифметики
 * @param dec1,dec2 децималы, могут быть с любыми знаками
 * @return Состояние знака 0 +, 1 -
 * @author Desperos
 */
int des_sign_mant(s21_decimal dec1, s21_decimal dec2);

/**
 * @brief Функция проверяет мантису на отсутствие значений
 * @param dec1 децимал, который нужно проверить
 * @return Состояние знака 0 - мантисса пуста, 1 - есть значения
 * @author Desperos
 */
int des_m_nul(s21_decimal dec);

/**
 * @brief Функция вычитания мантисы, с учетом их знака в 127 бите
 * @param dec1,dec2 децималы, могут быть с любыми знаками
 * @return Статус переполнения 0 - RES_OK, 1 - RES_OVERFLOW.
 * @author Desperos
 */
int des_sub_sign_mant(s21_decimal dec1, s21_decimal dec2, s21_decimal *res,
                      int *exp);

/**
 * @brief Функция округления мантисы, при арифметических операциях и отсутствия
 * свободного места в мантисе. В частности сложения мантисс.
 * @param dec1,dec2 децималы, могут быть с любыми знаками
 * @return Статус переполнения 0 - RES_OK, 1 - RES_OVERFLOW.
 * @author Desperos
 */
int des_round(s21_decimal a, s21_decimal b, s21_decimal *res, int *ex, int ar);

/**
 * @brief Функция проверки в конце функций арифметический вычеслений.
 * Устанавливает степень и обнуляет результат в случае ошибки
 * @param dec децимал
 * @author Desperos
 */
void des_end_func(s21_decimal *dec, int exp, int err);

/**
 * @brief Функция умножает мантиссу на 10 (10 СС)
 * @param ten децимал, который будет увеличиваться
 * @param ten_res децимал, в котором будет res * 10 (10 CC)
 * @return Статус переполнения 0 - RES_OK, 1 - RES_OVERFLOW.
 * @author Desperos
 */
int ten_func(s21_decimal ten, s21_decimal *ten_res);

/**
 * @brief Функция добавляет остаток от деления к мантиссе, в свободное место.
 * Если места нет округляет по банковскому последний знак.
 * @param ost децимал, остаток от деления
 * @param b децимал, делитель из функции деления
 * @author Desperos
 */
int des_r_div_mant(s21_decimal ost, s21_decimal b, s21_decimal *result);

/**
 * @brief Функция сравнения децимала по мантисе и степени с единицей, без учета
 * знака.
 * @param ost децимал, который нужно сравнить
 * @return 0 - больше или равно единице, 1 - меньше единицы.
 * @author Desperos
 */
int des_less_one(s21_decimal dec);

/**
 * @brief Функция сравнения двух децималов по мантиссе и степени, без учета
 * знака.
 * @param a,b децималы, который нужно сравнить
 * @return 0 - не равны, 1 - равны.
 * @author Desperos
 */
int des_equal(s21_decimal a, s21_decimal b);

/**
 * @brief Функция удаления последних нулей и понижения степени. Только для
 * дробной части
 * @param res децимал, в котором нужно убрать нули
 * @author Desperos
 */
void des_del_nul(s21_decimal *res, int *exp);
// -----------------------------------

// смотрит есть ли бит
int getbit(s21_decimal value, int bit);

int Perepis(s21_decimal dec1, s21_decimal *dec2,
            int bit);  // перписывает 0 и 1 из dec1 в dec2 до нужного бита
//  обнуление decimal но нужного значения
void s21_DeleteBitUnder(s21_decimal *value, int bit);

// ------------------------
int s21_GetBinExp(float src);
int call_of_me(int row);
int call_of_me_stop_me(int row);
void s21_printf_decimal(s21_decimal value);
int s21_show_exp(s21_decimal src);
void s21_set_exp(s21_decimal *src, int exp);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);

void s21_DeleteBit(s21_decimal *value, int bit);

void s21_SetBit(s21_decimal *value, int bit);

int s21_isnull_dec(s21_decimal value);
int is_less_mod(s21_decimal val1, s21_decimal val2);

#endif  // SRC_DECIMAL_H_
