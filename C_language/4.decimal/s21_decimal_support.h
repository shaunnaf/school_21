#define FALSE 0
#define TRUE 1

#define S21_POSITIVE_VALUE 0

//Маска бита знака числа decimal
#define _MASK_SIGN_ 0b10000000000000000000000000000000
//Маска Степени деления дробный части decimal
#define _MASK_DEGREE_ 0b00000000111111110000000000000000

//Маска бита знака числа decimal
#define _MASK_SIGN_ 0b10000000000000000000000000000000
//Маска Степени деления дробный части decimal
#define _MASK_DEGREE_ 0b00000000111111110000000000000000
//Максимальная степень на 1 Int
#define _MAX_DEGREE_ 1000000000

#define _MAX_DECIMAL_STR_ "79228162514264337593543950335"

#define OK 0
#define ERROR 1

//Получает размер decimal
//_SIZE_
#define _SIZE_(decimal) (sizeof(decimal.bits) / 4)

//Макрос получения знака decimal
//_GET_SIGN_
#define _G_S_(decimal) \
  (decimal.bits[_SIZE_(decimal) - 1] & _MASK_SIGN_ ? -1 : 1)*

//Макрос установки знака decimal
//_SET_SIGN_
#define _S_S_(decimal, sign)                           \
  if (1 sign 1)                                        \
    decimal.bits[_SIZE_(decimal) - 1] &= ~_MASK_SIGN_; \
  else                                                 \
    decimal.bits[_SIZE_(decimal) - 1] |= _MASK_SIGN_;

//Макрос проверки положительности decimal
#define _IS_POS_(decimal) (_G_S_(decimal) 1 == 1)

//Макрос для получения степени деления дробной части decimal
#define _G_D_(decimal) \
  ((decimal.bits[_SIZE_(decimal) - 1] & _MASK_DEGREE_) >> 16)

//Макрос для установки степени деления дробной части decimal
#define _S_D_(decimal, degree)                         \
  decimal.bits[_SIZE_(decimal) - 1] &= ~_MASK_DEGREE_; \
  decimal.bits[_SIZE_(decimal) - 1] |= ((degree) << 16)

//Макрос для получения бита decimal
#define _G_B_(decimal, bit) ((decimal.bits[(bit) / 32] >> ((bit) % 32)) & 1)

//Макрос для установки бита decimal
#define _S_B_(decimal, bit, value)                  \
  decimal.bits[(bit) / 32] &= ~(1 << ((bit) % 32)); \
  decimal.bits[(bit) / 32] |= ((value) << ((bit) % 32))

//Макрос для битового сдвига decimal вправо
#define _RS_B_(decimal, bit)                               \
  {                                                        \
    for (int i_b = 0; i_b < bit; i_b++) {                  \
      for (int j = 0; j < (int)_SIZE_(decimal) - 1; j++) { \
        int mem = _G_B_(decimal, j * 32);                  \
        decimal.bits[j] >>= 1;                             \
        _S_B_(decimal, j * 32 - 1, mem);                   \
      }                                                    \
    }                                                      \
  }

//Макрос для битового сдвига decimal влево
#define _LS_B_(decimal, bit)                           \
  {                                                    \
    for (int i_b = 0; i_b < bit; i_b++) {              \
      for (int j = _SIZE_(decimal) - 2; j >= 0; j--) { \
        int mem = _G_B_(decimal, j * 32 - 1);          \
        decimal.bits[j] <<= 1;                         \
        _S_B_(decimal, j * 32, mem);                   \
      }                                                \
      _S_B_(decimal, 0, 0);                            \
    }                                                  \
  }

#define MAX_UINT 4294967295
#define SIMPLE_NUMBER 2294967295

//Структура decimal
typedef struct {
  unsigned int bits[4];
} s21_decimal;