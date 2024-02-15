#include "../s21_tests.h"

int run_suite(Suite *suite);

int main(void) {
  int total_failed_count = 0;  // Общее количество неудачных тестов

  // Создание и запуск тестовых наборов
  total_failed_count += run_suite(suite_memchr());
  total_failed_count += run_suite(suite_memcmp());
  total_failed_count += run_suite(suite_memcpy());
  total_failed_count += run_suite(suite_memset());
  total_failed_count += run_suite(suite_strchr());
  total_failed_count += run_suite(suite_strcspn());
  total_failed_count += run_suite(suite_sscanf());
  total_failed_count += run_suite(suite_strerror());
  total_failed_count += run_suite(suite_strlen());
  total_failed_count += run_suite(suite_strncat());
  total_failed_count += run_suite(suite_strncmp());
  total_failed_count += run_suite(suite_strncpy());
  total_failed_count += run_suite(suite_strpbrk());
  total_failed_count += run_suite(suite_strrchr());
  total_failed_count += run_suite(suite_strstr());
  total_failed_count += run_suite(suite_strtok());
  total_failed_count += run_suite(suite_to_lower());
  total_failed_count += run_suite(suite_to_upper());
  total_failed_count += run_suite(suite_sprintf());
  total_failed_count += run_suite(suite_trim());
  total_failed_count += run_suite(suite_insert());

  // Возврат статуса завершения программы в зависимости от количества неудачных
  // тестов
  return (total_failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

int run_suite(Suite *suite) {
  int failed_count;

  // Создание исполнителя тестов для данного тестового набора
  SRunner *suite_runner = srunner_create(suite);

  // Запуск всех тестов в данном тестовом наборе
  srunner_run_all(suite_runner, CK_NORMAL);

  // Получение количества неудачных тестов
  failed_count = srunner_ntests_failed(suite_runner);

  // Освобождение ресурсов исполнителя тестов
  srunner_free(suite_runner);

  // Возвращаем количество неудачных тестов в данном тестовом наборе
  return failed_count;
}
