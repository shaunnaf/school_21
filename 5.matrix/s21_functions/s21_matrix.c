#include "../s21_matrix.h"

int s21_create_matrix(int rows, int colums, matrix_t *result) {
  int ret = 0;
  if (rows < 1 || colums < 1)
    ret = 1;
  else {
    result->rows = rows;
    result->columns = colums;
    result->matrix = calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = calloc(colums, sizeof(double));
    }
  }
  return ret;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
  }
  A->rows = 0;
  A->columns = 0;
}

int compare_double(double num1, double num2) {
  double epsilon = 1e-8;
  return fabs(num1 - num2) < epsilon;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = 1;
  if (A->columns == B->columns && A->rows == B->rows) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (!compare_double(A->matrix[i][j], B->matrix[i][j])) {
          res = 0;
          break;
        }
      }
      if (res == 0) break;
    }
  }
  return res;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = 0;
  if (A->columns < 1 || A->rows < 1 || B->rows < 1 || B->columns < 1) {
    ret = 1;
  } else if (A->columns == B->columns && A->rows == B->rows) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  } else {
    ret = 2;
  }
  return ret;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = 0;
  if (A->columns < 1 || A->rows < 1 || B->columns < 1 || B->rows < 1) {
    ret = 1;
  } else if (A->columns == B->columns && A->rows == B->rows) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  } else {
    ret = 2;
  }
  return ret;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int ret = 0;
  if (A->columns < 1 || A->rows < 1) {
    ret = 1;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return ret;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = 0;
  if (A->columns < 1 || A->rows < 1 || B->columns < 1 || B->rows < 1) {
    ret = 1;
  } else if (A->columns == B->rows) {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  } else {
    ret = 2;
  }
  return ret;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int ret = 0;
  if (A->columns < 1 || A->rows < 1) {
    ret = 1;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return ret;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int ret = 0;
  if (A->columns < 1 || A->rows < 1) {
    ret = 1;
  } else if (A->columns == A->rows) {
    s21_create_matrix(A->columns, A->columns, result);
    if (A->rows == 1) {
      result->matrix[0] = A->matrix[0];
    } else {
      matrix_t minor;
      double det;
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          s21_create_minor(A, &minor, i, j);
          s21_determinant(&minor, &det);
          result->matrix[i][j] = (i + j) % 2 == 0 ? det : -det;
          s21_remove_matrix(&minor);
        }
      }
    }
  } else {
    ret = 2;
  }
  return ret;
}

void s21_create_minor(matrix_t *A, matrix_t *minor, int row_to_skip,
                      int col_to_skip) {
  int n = A->rows - 1;
  s21_create_matrix(n, n, minor);

  for (int i = 0, row = 0; i < A->rows; i++) {
    if (i == row_to_skip) {
      continue;
    }
    for (int j = 0, col = 0; j < A->columns; j++) {
      if (j == col_to_skip) {
        continue;
      }
      minor->matrix[row][col++] = A->matrix[i][j];
    }
    row++;
  }
}

int s21_determinant(matrix_t *A, double *result) {
  int ret = 0;
  if (A->columns < 1 || A->rows < 1) {
    ret = 1;
  } else if (A->columns == A->rows) {
    if (A->columns == 1)
      *result = A->matrix[0][0];
    else if (A->columns == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
    } else {
      double det = 0;
      matrix_t minor;
      for (int j = 0; j < A->rows; j++) {
        s21_create_minor(A, &minor, 0, j);
        double minor_det;
        s21_determinant(&minor, &minor_det);
        det += (j % 2 == 0 ? 1 : -1) * A->matrix[0][j] * minor_det;
        s21_remove_matrix(&minor);
      }
      *result = det;
    }
  } else {
    ret = 2;
  }
  return ret;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int ret = 0;
  double det = 0;
  ret = s21_determinant(A, &det);
  if (ret == 0 && det != 0) {
    matrix_t complement, transpose;
    if (A->rows == 1) {
      s21_create_matrix(1, 1, result);
      result->matrix[0][0] = 1 / A->matrix[0][0];
    } else {
      ret = s21_calc_complements(A, &complement);
      if (ret == 0) {
        ret = s21_transpose(&complement, &transpose);
        if (ret == 0) {
          ret = s21_mult_number(&transpose, 1. / det, result);
        }
        s21_remove_matrix(&transpose);
      }
      s21_remove_matrix(&complement);
    }
  } else if (det == 0 && ret == 0)
    ret = 2;
  return ret;
}
