#include <gtest/gtest.h>

#include "../s21matrix_oop.h"

TEST(S21MatrixTest, DefaultConstructor) {
  S21Matrix m;
  ASSERT_EQ(m.GetRows(), 3);
  ASSERT_EQ(m.GetCols(), 3);
}

TEST(S21MatrixTest, ParamConstructor) {
  S21Matrix m(2, 2);
  ASSERT_EQ(m.GetRows(), 2);
  ASSERT_EQ(m.GetCols(), 2);
  ASSERT_NO_THROW(S21Matrix(1, 1));
  ASSERT_THROW(S21Matrix(-1, 3), std::invalid_argument);
}

TEST(S21MatrixTest, CopyConstructor) {
  S21Matrix m1(3, 3);
  m1(0, 0) = 1.0;
  S21Matrix m2(m1);
  ASSERT_EQ(m1(0, 0), m2(0, 0));
  ASSERT_NE(&m1, &m2);
}

TEST(S21MatrixTest, AssignmentOperator) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 5.0;
  S21Matrix m2;
  m2 = m1;
  ASSERT_EQ(m1(0, 0), m2(0, 0));
}

TEST(S21MatrixTest, EqualityOperator) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.0;
  S21Matrix m2(2, 2);
  m2(0, 0) = 1.0;
  ASSERT_TRUE(m1 == m2);
  m2(1, 1) = 2.0;
  ASSERT_FALSE(m1 == m2);
}

TEST(S21MatrixTest, AddOperator) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 1.0;
  m2(0, 0) = 2.0;
  S21Matrix result = m1 + m2;
  ASSERT_EQ(result(0, 0), 3.0);
  ASSERT_THROW(S21Matrix(2, 2) + S21Matrix(3, 3), std::invalid_argument);
}

TEST(S21MatrixTest, SubOperator) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 5.0;
  m2(0, 0) = 3.0;
  S21Matrix result = m1 - m2;
  ASSERT_EQ(result(0, 0), 2.0);
  ASSERT_THROW(S21Matrix(2, 2) - S21Matrix(3, 3), std::invalid_argument);
}

TEST(S21MatrixTest, MultNumberOperator) {
  S21Matrix m(2, 2);
  m(0, 0) = 2.0;
  S21Matrix result = m * 2.0;
  ASSERT_EQ(result(0, 0), 4.0);
}

TEST(S21MatrixTest, MultMatrixOperator) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1(0, 0) = 1.0;
  m1(1, 1) = 1.0;
  m2(0, 0) = 2.0;
  m2(1, 1) = 2.0;
  S21Matrix result = m1 * m2;
  ASSERT_EQ(result(0, 0), 2.0);
  ASSERT_EQ(result(1, 1), 2.0);
  ASSERT_THROW(S21Matrix(2, 2) * S21Matrix(3, 3), std::invalid_argument);
}

TEST(S21MatrixTest, Transpose) {
  S21Matrix m(2, 2);
  m(0, 1) = 1.0;
  S21Matrix result;
  m.Transpose(result);
  ASSERT_EQ(result(1, 0), 1.0);
}

TEST(S21MatrixTest, Determinant) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(1, 1) = 1.0;
  ASSERT_EQ(m.Determinant(), 1.0);
  m(0, 0) = 2.0;
  m(1, 1) = 3.0;
  ASSERT_EQ(m.Determinant(), 6.0);
  ASSERT_THROW(S21Matrix(2, 3).Determinant(), std::invalid_argument);
}

TEST(S21MatrixTest, InverseMatrix) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(1, 1) = 1.0;
  S21Matrix result;
  ASSERT_NO_THROW(m.InverseMatrix(result));
  ASSERT_EQ(result(0, 0), 1.0);
  m(0, 0) = 0.0;
  ASSERT_THROW(m.InverseMatrix(result), std::invalid_argument);
}

TEST(S21MatrixTest, Minor) {
  S21Matrix m(3, 3);
  m(0, 0) = 1.0;
  m(1, 1) = 1.0;
  m(2, 2) = 1.0;
  S21Matrix minor;
  m.CreateMinor(0, 0, minor);
  ASSERT_EQ(minor.GetRows(), 2);
  ASSERT_EQ(minor.GetCols(), 2);
}

TEST(S21MatrixTest, CalcComplements) {
  S21Matrix m(3, 3);
  m(0, 0) = 1.0;
  m(1, 1) = 1.0;
  m(2, 2) = 1.0;
  S21Matrix result;
  ASSERT_NO_THROW(m.CalcComplements(result));
  ASSERT_EQ(result(0, 0), 1.0);
}

TEST(S21MatrixTest, MultNumberMethod) {
  S21Matrix m(2, 2);
  m(0, 0) = 2.0;
  m.MultNumber(3.0);
  ASSERT_EQ(m(0, 0), 6.0);
}
