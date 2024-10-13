#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <cmath>
#include <iostream>
#include <stdexcept>

class S21Matrix {
 private:
  int rows_;
  int cols_;
  double **matrix_;

  void AllocateMemory(int rows, int cols);
  void FreeMemory();
  void CopyMatrix(const S21Matrix &other);

 public:
  S21Matrix();

  S21Matrix(int rows, int cols);

  S21Matrix(const S21Matrix &other);

  S21Matrix(S21Matrix &&other) noexcept;

  ~S21Matrix();

  int GetRows() const { return rows_; }
  int GetCols() const { return cols_; }

  void SetRows(int new_rows);
  void SetCols(int new_cols);
  void CreateMinor(int row_to_skip, int col_to_skip, S21Matrix &minor) const;

  S21Matrix operator+(const S21Matrix &other) const;  // Сложение матриц
  S21Matrix operator-(const S21Matrix &other) const;  // Вычитание матриц
  S21Matrix operator*(const S21Matrix &other) const;  // Умножение матриц
  S21Matrix operator*(double num) const;  // Умножение матрицы на число
  bool operator==(const S21Matrix &other) const;  // Проверка на равенство
  S21Matrix &operator=(const S21Matrix &other);  // Присваивание матрицы
  S21Matrix &operator+=(const S21Matrix &other);  // Присваивание сложения
  S21Matrix &operator-=(const S21Matrix &other);  // Присваивание вычитания
  S21Matrix &operator*=(const S21Matrix &other);  // Присваивание умножения
  S21Matrix &operator*=(double num);  // Присваивание умножения на число
  double &operator()(int i, int j);  // Индексация по элементам

  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MultNumber(double number);
  void MultMatrix(const S21Matrix &other, S21Matrix &result) const;
  void Transpose(S21Matrix &result) const;
  void CalcComplements(S21Matrix &result) const;
  double Determinant() const;
  void InverseMatrix(S21Matrix &result) const;
};

#endif  // S21_MATRIX_H
