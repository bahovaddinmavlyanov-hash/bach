#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t* result) {
  int error = ERROR;

  if (!result) return ERROR;
  result->matrix = NULL;
  result->rows = 0;
  result->columns = 0;

  if (rows > 0 && columns > 0) {
    result->matrix = calloc(rows, sizeof(double*));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = calloc(columns, sizeof(double));
    }
    result->rows = rows;
    result->columns = columns;
    error = OK;
  }
  return error;
}

void s21_remove_matrix(matrix_t* A) {
  if (!A || !A->matrix || A->rows < 0 || A->columns < 0) return;
  for (int i = 0; i < A->rows; i++) {
    if (A->matrix[i]) {
      free(A->matrix[i]);
      A->matrix[i] = NULL;
    }
  }
  if (A->matrix) free(A->matrix);
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(matrix_t* A, matrix_t* B) {
  int error = SUCCESS;
  if (!A || !B || !A->matrix || !B->matrix) return FAILURE;
  if (A->rows == B->rows && A->columns == B->columns) {
    int general_rows = A->rows;
    int general_columns = A->columns;
    for (int i = 0; i < general_rows && error == SUCCESS; i++) {
      for (int j = 0; j < general_columns && error == SUCCESS; j++) {
        double diff = fabs(A->matrix[i][j] - B->matrix[i][j]);
        if (diff > EPS) error = FAILURE;
      }
    }
  } else
    error = FAILURE;

  return error;
}

int s21_sum_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
  int error = OK;
  if (!A || !B || A->rows < 1 || A->columns < 1 || B->rows < 1 ||
      B->columns < 1)
    return ERROR;
  if (!A->matrix || !B->matrix) return ERROR;
  if (A->rows != B->rows || A->columns != B->columns)
    error = CALCULATION_FAILURE;
  else {
    int general_row = A->rows;
    int general_column = A->columns;
    if (s21_create_matrix(general_row, general_column, result) != OK)
      error = ERROR;
    for (int i = 0; i < general_row; i++) {
      for (int j = 0; j < general_column; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return error;
}

int s21_sub_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
  int error = OK;
  if (!A || !B || A->rows < 1 || A->columns < 1 || B->rows < 1 ||
      B->columns < 1)
    return ERROR;
  if (!A->matrix || !B->matrix) return ERROR;
  if (A->rows != B->rows || A->columns != B->columns) {
    error = CALCULATION_FAILURE;
  } else {
    int general_row = A->rows;
    int general_column = A->columns;
    if (s21_create_matrix(general_row, general_column, result) != OK)
      error = ERROR;
    for (int i = 0; error == OK && i < general_row; i++) {
      for (int j = 0; j < general_column; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return error;
}

int s21_mult_number(matrix_t* A, double number, matrix_t* result) {
  int error = OK;
  if (!A || !A->matrix || A->rows < 1 || A->columns < 1) return ERROR;
  if (s21_create_matrix(A->rows, A->columns, result) != OK) return ERROR;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return error;
}

int s21_mult_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
  int error = OK;
  if (!A || !B || A->rows < 1 || A->columns < 1 || B->rows < 1 ||
      B->columns < 1)
    return ERROR;
  if (!A->matrix || !B->matrix) return ERROR;
  if (A->columns != B->rows) return CALCULATION_FAILURE;
  int general_row = A->rows;
  int general_column = B->columns;
  if (s21_create_matrix(general_row, general_column, result) != OK)
    error = ERROR;
  for (int i = 0; i < general_row && error == OK; i++) {
    for (int j = 0; j < general_column && error == OK; j++) {
      double sum = 0;
      for (int dop_j = 0; dop_j < B->rows; dop_j++) {
        sum += A->matrix[i][dop_j] * B->matrix[dop_j][j];
      }
      result->matrix[i][j] = sum;
    }
  }
  return error;
}

int s21_transpose(matrix_t* A, matrix_t* result) {
  int error = OK;
  if (A == NULL || A->matrix == NULL || A->rows < 1 || A->columns < 1)
    return ERROR;
  if (s21_create_matrix(A->columns, A->rows, result) != OK) {
    error = ERROR;
  }
  for (int i = 0; error == OK && i < A->columns; i++) {
    for (int j = 0; j < A->rows; j++) {
      result->matrix[i][j] = A->matrix[j][i];
    }
  }
  return error;
}

int s21_determinant(matrix_t* A, double* result) {
  int error = OK;
  if (!result) return ERROR;
  if (!A || !A->matrix || A->rows < 1 || A->columns < 1) return ERROR;
  if (A->rows != A->columns) return CALCULATION_FAILURE;
  if (A->columns == 2)
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  else if (A->columns == 1)
    *result = A->matrix[0][0];
  else {
    *result = 0.0;
    for (int i = 0; i < A->columns && error == OK; i++) {
      matrix_t temp = {NULL, 0, 0};
      if (s21_create_matrix(A->rows - 1, A->columns - 1, &temp) != OK)
        error = ERROR;
      else {
        int temp_row = 0;
        for (int m = 1; m < A->rows && error == OK; m++) {
          int temp_column = 0;
          for (int n = 0; n < A->columns && error == OK; n++) {
            if (n != i) temp.matrix[temp_row][temp_column++] = A->matrix[m][n];
          }
          temp_row++;
        }
      }
      double det;
      if (s21_determinant(&temp, &det) != OK)
        error = ERROR;
      else if (error != ERROR) {
        double sign = (i % 2 == 0) ? 1.0 : -1.0;
        *result += sign * A->matrix[0][i] * det;
      }
      s21_remove_matrix(&temp);
    }
  }
  return error;
}

int s21_calc_complements(matrix_t* A, matrix_t* result) {
  int error = OK;
  if (!A || !A->matrix || A->rows < 1 || A->columns < 1) return ERROR;
  if (A->rows != A->columns || A->rows == 1) return CALCULATION_FAILURE;

  if (s21_create_matrix(A->rows, A->columns, result) != OK) error = ERROR;

  for (int i = 0; i < A->rows && error == OK; i++) {
    for (int j = 0; j < A->columns && error == OK; j++) {
      matrix_t temp = {NULL, 0, 0};
      s21_create_matrix(A->rows - 1, A->columns - 1, &temp);
      int temp_row = 0;
      for (int m = 0; m < A->rows && error == OK; m++) {
        if (m == i) continue;
        int temp_column = 0;
        for (int n = 0; n < A->columns; n++) {
          if (n != j) temp.matrix[temp_row][temp_column++] = A->matrix[m][n];
        }
        temp_row++;
      }
      double det = 0;
      if (s21_determinant(&temp, &det) != OK)
        error = ERROR;
      else if (error == OK)
        result->matrix[i][j] = det * pow(-1, i + j);
      s21_remove_matrix(&temp);
    }
  }
  return error;
}

int s21_inverse_matrix(matrix_t* A, matrix_t* result) {
  int error = OK;
  if (!A || !A->matrix || A->rows < 1 || A->columns < 1) return ERROR;
  double det = 0;
  error = s21_determinant(A, &det);
  if (A->rows != A->columns || error != OK || fabs(det) < 1e-7)
    return CALCULATION_FAILURE;

  s21_create_matrix(A->rows, A->columns, result);

  if (error == OK && A->rows == 1)
    result->matrix[0][0] = 1 / A->matrix[0][0];
  else {
    matrix_t complements = {NULL, 0, 0};
    matrix_t transpose = {NULL, 0, 0};

    error = s21_calc_complements(A, &complements);

    if (error == OK) {
      s21_transpose(&complements, &transpose);

      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = transpose.matrix[i][j] / det;
        }
      }
      if (transpose.matrix) s21_remove_matrix(&transpose);
    }

    if (complements.matrix) s21_remove_matrix(&complements);
  }
  return error;
}