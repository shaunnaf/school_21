#include "s21matrix_oop.h"

void S21Matrix::AllocateMemory(int rows, int cols) {
  matrix_ = new double*[rows];
  for (int i = 0; i < rows; i++) {
    matrix_[i] = new double[cols]{0};
  }
}

void S21Matrix::FreeMemory() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

S21Matrix::S21Matrix() : rows_(3), cols_(3) { AllocateMemory(rows_, cols_); }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::invalid_argument("Invalid matrix size");
  }
  AllocateMemory(rows_, cols_);
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  AllocateMemory(rows_, cols_);
  CopyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { FreeMemory(); }

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Matrices have different dimensions for addition");
  }
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Matrices have different dimensions for subtraction");
  }
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Matrices have incompatible dimensions for multiplication");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::operator*(double num) const {
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = matrix_[i][j] * num;
    }
  }
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (matrix_[i][j] != other.matrix_[i][j]) {
        return false;
      }
    }
  }
  return true;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    FreeMemory();
    rows_ = other.rows_;
    cols_ = other.cols_;
    AllocateMemory(rows_, cols_);
    CopyMatrix(other);
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  *this = *this + other;
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  *this = *this - other;
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  *this = *this * other;
  return *this;
}

S21Matrix& S21Matrix::operator*=(double num) {
  *this = *this * num;
  return *this;
}

double& S21Matrix::operator()(int i, int j) {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::out_of_range("Index out of bounds");
  }
  return matrix_[i][j];
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) return false;
    }
  }
  return true;
}

void S21Matrix::CopyMatrix(const S21Matrix& other) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices dimensions do not match.");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices dimensions do not match.");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MultNumber(double number) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= number;
    }
  }
}

void S21Matrix::MultMatrix(const S21Matrix& other, S21Matrix& result) const {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Matrix dimensions do not match for multiplication.");
  }
  result.FreeMemory();
  result.rows_ = rows_;
  result.cols_ = other.cols_;
  result.AllocateMemory(result.rows_, result.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
}

void S21Matrix::Transpose(S21Matrix& result) const {
  result.FreeMemory();
  result.rows_ = cols_;
  result.cols_ = rows_;
  result.AllocateMemory(result.rows_, result.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
}

void S21Matrix::CalcComplements(S21Matrix& result) const {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Matrix must be square to calculate complements.");
  }
  result.FreeMemory();
  result.rows_ = rows_;
  result.cols_ = cols_;
  result.AllocateMemory(result.rows_, result.cols_);

  if (rows_ == 1) {
    result.matrix_[0][0] = 1;
  } else {
    S21Matrix minor;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        CreateMinor(i, j, minor);
        double det = minor.Determinant();
        result.matrix_[i][j] = ((i + j) % 2 == 0) ? det : -det;
      }
    }
  }
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Matrix must be square to calculate determinant.");
  }
  if (rows_ == 1) return matrix_[0][0];
  if (rows_ == 2) {
    return matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  }

  double det = 0.0;
  for (int j = 0; j < cols_; j++) {
    S21Matrix minor;
    CreateMinor(0, j, minor);
    det += (j % 2 == 0 ? 1 : -1) * matrix_[0][j] * minor.Determinant();
  }
  return det;
}

void S21Matrix::InverseMatrix(S21Matrix& result) const {
  double det = Determinant();
  if (fabs(det) < 1e-7)
    throw std::invalid_argument("Matrix is singular and cannot be inverted.");

  S21Matrix complements;
  CalcComplements(complements);
  complements.Transpose(result);
  result.MultNumber(1.0 / det);
}

void S21Matrix::CreateMinor(int row_to_skip, int col_to_skip,
                            S21Matrix& minor) const {
  minor.FreeMemory();
  minor.rows_ = rows_ - 1;
  minor.cols_ = cols_ - 1;
  minor.AllocateMemory(minor.rows_, minor.cols_);

  for (int i = 0, row = 0; i < rows_; i++) {
    if (i == row_to_skip) continue;
    for (int j = 0, col = 0; j < cols_; j++) {
      if (j == col_to_skip) continue;
      minor.matrix_[row][col++] = matrix_[i][j];
    }
    row++;
  }
}
