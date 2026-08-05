#include <check.h>

#include "s21_matrix.h"

#define SUCCESS 1
#define FAILURE 0
#define S21_OK 0
#define S21_INCORRECT_MATRIX 1
#define S21_CALC_ERROR 2

START_TEST(s21_eq_matrix_test_1) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_test_2) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 7.0;
  A.matrix[2][1] = 8.0;
  A.matrix[2][2] = 9.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[0][2] = 3.3;
  B.matrix[1][0] = 4.0;
  B.matrix[1][1] = 5.0;
  B.matrix[1][2] = 6.0;
  B.matrix[2][0] = 7.0;
  B.matrix[2][1] = 8.0;
  B.matrix[2][2] = 9.0;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_test_3) {
  matrix_t A, B;
  s21_create_matrix(2, 1, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[1][0] = 3.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_test_4) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 2, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_test_5) {
  ck_assert_int_eq(s21_eq_matrix(NULL, NULL), FAILURE);
}
END_TEST

START_TEST(s21_eq_matrix_test_6) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(s21_eq_matrix(&A, NULL), FAILURE);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_eq_matrix_test_7) {
  matrix_t B;
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(s21_eq_matrix(NULL, &B), FAILURE);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_test_8) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][1] += 1e-8;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sum_matrix_test_1) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 5.0;
  A.matrix[1][0] = 6.0;
  A.matrix[1][1] = 3.0;

  B.matrix[0][0] = 7.0;
  B.matrix[0][1] = 15.0;
  B.matrix[1][0] = 4.0;
  B.matrix[1][1] = 2.0;

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), S21_OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sum_matrix_test_2) {
  matrix_t A, B, result;
  s21_create_matrix(1, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 4.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), S21_CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sum_matrix_test_3) {
  matrix_t A, B, result;
  s21_create_matrix(2, 1, &A);
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), S21_CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sum_matrix_test_4) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(-1, 2, &B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), S21_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_sum_matrix_test_5) {
  matrix_t B, result;
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(s21_sum_matrix(NULL, &B, &result), S21_INCORRECT_MATRIX);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sum_matrix_test_6) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(s21_sum_matrix(&A, NULL, &result), S21_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_sum_matrix_test_7) {
  matrix_t A, B, result;
  s21_create_matrix(-2, 2, &A);
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), S21_INCORRECT_MATRIX);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sub_matrix_test_1) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 5.0;
  A.matrix[1][0] = 6.0;
  A.matrix[1][1] = 3.0;

  B.matrix[0][0] = 7.0;
  B.matrix[0][1] = 15.0;
  B.matrix[1][0] = 4.0;
  B.matrix[1][1] = 2.0;

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), S21_OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_test_2) {
  matrix_t A, B, result;
  s21_create_matrix(1, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 4.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 3.0;

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), S21_CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sub_matrix_test_3) {
  matrix_t B, result;
  s21_create_matrix(3, 3, &B);
  ck_assert_int_eq(s21_sub_matrix(NULL, &B, &result), S21_INCORRECT_MATRIX);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sub_matrix_test_4) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(-1, 2, &B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), S21_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_sub_matrix_test_5) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);
  ck_assert_int_eq(s21_sub_matrix(&A, NULL, &result), S21_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_sub_matrix_test_6) {
  matrix_t A, B, result;
  s21_create_matrix(2, -2, &A);
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), S21_INCORRECT_MATRIX);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_mult_number_test_1) {
  matrix_t A, result;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  double number = 2.0;

  ck_assert_int_eq(s21_mult_number(&A, number, &result), S21_OK);
  ck_assert_double_eq(result.matrix[0][0], 2.0);
  ck_assert_double_eq(result.matrix[0][1], 4.0);
  ck_assert_double_eq(result.matrix[1][0], 6.0);
  ck_assert_double_eq(result.matrix[1][1], 8.0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number_test_2) {
  matrix_t result;
  double number = 7.0;
  ck_assert_int_eq(s21_mult_number(NULL, number, &result),
                   S21_INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_mult_number_test_3) {
  matrix_t A, result;
  s21_create_matrix(-1, 2, &A);
  double number = 7.0;
  ck_assert_int_eq(s21_mult_number(&A, number, &result), S21_INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_mult_number_test_4) {
  matrix_t A, result;
  s21_create_matrix(2, -2, &A);
  double number = 7.0;
  ck_assert_int_eq(s21_mult_number(&A, number, &result), S21_INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_mult_matrix_test_1) {
  matrix_t A, B, result;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 3.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 2.0;

  B.matrix[0][0] = 4.0;
  B.matrix[0][1] = 6.0;
  B.matrix[1][0] = 6.0;
  B.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), S21_OK);
  ck_assert_double_eq(result.matrix[0][0], 26.0);
  ck_assert_double_eq(result.matrix[0][1], 24.0);
  ck_assert_double_eq(result.matrix[1][0], 24.0);
  ck_assert_double_eq(result.matrix[1][1], 26.0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_matrix_test_2) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(s21_mult_matrix(&A, NULL, &result), S21_INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_mult_matrix_test_3) {
  matrix_t B, result;
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(s21_mult_matrix(NULL, &B, &result), S21_INCORRECT_MATRIX);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_mult_matrix_test_4) {
  matrix_t A, B, result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), S21_CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_transpose_test_1) {
  matrix_t A, result;

  s21_create_matrix(2, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  ck_assert_int_eq(s21_transpose(&A, &result), S21_OK);
  ck_assert_double_eq(result.matrix[0][0], 1.0);
  ck_assert_double_eq(result.matrix[0][1], 4.0);
  ck_assert_double_eq(result.matrix[1][0], 2.0);
  ck_assert_double_eq(result.matrix[1][1], 5.0);
  ck_assert_double_eq(result.matrix[2][0], 3.0);
  ck_assert_double_eq(result.matrix[2][1], 6.0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_test_2) {
  matrix_t result;
  ck_assert_int_eq(s21_transpose(NULL, &result), S21_INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_transpose_test_3) {
  matrix_t A, result;
  s21_create_matrix(-1, 2, &A);
  ck_assert_int_eq(s21_transpose(&A, &result), S21_INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_transpose_test_4) {
  matrix_t A, result;
  // printf('%s',g(A));
  s21_create_matrix(2, -2, &A);
  ck_assert_int_eq(s21_transpose(&A, &result), S21_INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_determinant_test_1) {
  matrix_t A;
  double det;

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;
  ck_assert_int_eq(s21_determinant(&A, &det), S21_OK);
  ck_assert_double_eq(det, 5.0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_test_2) {
  matrix_t A;
  double det;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  ck_assert_int_eq(s21_determinant(&A, &det), S21_OK);
  ck_assert_double_eq(det, -2.0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_test_3) {
  matrix_t A;
  double det;

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 7.0;
  A.matrix[2][1] = 8.0;
  A.matrix[2][2] = 9.0;
  ck_assert_int_eq(s21_determinant(&A, &det), S21_OK);
  ck_assert_double_eq(det, 0.0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_test_4) {
  matrix_t A;
  double det;

  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[0][3] = 4.0;
  A.matrix[1][0] = 5.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  A.matrix[1][3] = 6.0;
  A.matrix[2][0] = 6.0;
  A.matrix[2][1] = 7.0;
  A.matrix[2][2] = 8.0;
  A.matrix[2][3] = 9.0;
  A.matrix[3][0] = 11.0;
  A.matrix[3][1] = 11.0;
  A.matrix[3][2] = 12.0;
  A.matrix[3][3] = 13.0;

  ck_assert_int_eq(s21_determinant(&A, &det), S21_OK);
  ck_assert_double_eq(det, 5);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_test_5) {
  double det;
  ck_assert_int_eq(s21_determinant(NULL, &det), S21_INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_determinant_test_6) {
  matrix_t A;
  double result;

  s21_create_matrix(2, 3, &A);
  ck_assert_int_eq(s21_determinant(&A, &result), S21_CALC_ERROR);
  s21_remove_matrix(&A);
}

END_TEST

START_TEST(s21_determinant_test_7) {
  matrix_t A;
  double result;

  s21_create_matrix(-2, 3, &A);
  ck_assert_int_eq(s21_determinant(&A, &result), S21_INCORRECT_MATRIX);
}

END_TEST

START_TEST(s21_determinant_test_8) {
  matrix_t A;
  double result;

  s21_create_matrix(2, -3, &A);
  ck_assert_int_eq(s21_determinant(&A, &result), S21_INCORRECT_MATRIX);
}

END_TEST

START_TEST(s21_calc_complements_test_1) {
  matrix_t A, result;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  ck_assert_int_eq(s21_calc_complements(&A, &result), S21_OK);
  ck_assert_double_eq(result.matrix[0][0], 4.0);
  ck_assert_double_eq(result.matrix[0][1], -3.0);
  ck_assert_double_eq(result.matrix[1][0], -2.0);
  ck_assert_double_eq(result.matrix[1][1], 1.0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_test_2) {
  matrix_t A, result;

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 4.0;
  A.matrix[1][2] = 2.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 2.0;
  A.matrix[2][2] = 1.0;
  ck_assert_int_eq(s21_calc_complements(&A, &result), S21_OK);
  ck_assert_double_eq(result.matrix[0][0], 0.0);
  ck_assert_double_eq(result.matrix[0][1], 10.0);
  ck_assert_double_eq(result.matrix[0][2], -20.0);
  ck_assert_double_eq(result.matrix[1][0], 4.0);
  ck_assert_double_eq(result.matrix[1][1], -14.0);
  ck_assert_double_eq(result.matrix[1][2], 8.0);
  ck_assert_double_eq(result.matrix[2][0], -8.0);
  ck_assert_double_eq(result.matrix[2][1], -2.0);
  ck_assert_double_eq(result.matrix[2][2], 4.0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_test_3) {
  matrix_t A, result;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;
  ck_assert_int_eq(s21_calc_complements(&A, &result), S21_CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_calc_complements_test_4) {
  matrix_t A, result;
  s21_create_matrix(1, 3, &A);
  ck_assert_int_eq(s21_calc_complements(&A, &result), S21_CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_calc_complements_test_5) {
  matrix_t A, result;
  s21_create_matrix(3, 2, &A);
  ck_assert_int_eq(s21_calc_complements(&A, &result), S21_CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_calc_complements_test_6) {
  matrix_t A, result;
  s21_create_matrix(2, -1, &A);
  ck_assert_int_eq(s21_calc_complements(&A, &result), S21_INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_calc_complements_test_7) {
  matrix_t A, result;
  s21_create_matrix(-1, 2, &A);
  ck_assert_int_eq(s21_calc_complements(&A, &result), S21_INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_calc_complements_test_8) {
  matrix_t result;
  ck_assert_int_eq(s21_calc_complements(NULL, &result), S21_INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_inverse_test_1) {
  matrix_t A, result;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 4.0;
  A.matrix[0][1] = 7.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 6.0;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), S21_OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.6, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], -0.7, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], -0.2, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], 0.4, 1e-6);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_test_2) {
  matrix_t A, result;
  s21_create_matrix(-1, 2, &A);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), S21_INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_inverse_test_3) {
  matrix_t A, result;
  s21_create_matrix(2, -2, &A);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), S21_INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_inverse_test_4) {
  matrix_t A, result;

  s21_create_matrix(2, 3, &A);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), S21_CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_test_5) {
  matrix_t A, result;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 4.0;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), S21_CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_test_6) {
  matrix_t A, result;

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 2.0;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), S21_OK);
  ck_assert_double_eq(result.matrix[0][0], 0.5);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_test_7) {
  matrix_t result;

  ck_assert_int_eq(s21_inverse_matrix(NULL, &result), S21_INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_create_matrix_test_1) {
  matrix_t matrix;
  ck_assert_int_eq(s21_create_matrix(3, -1, &matrix), S21_INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_create_matrix_test_2) {
  matrix_t matrix;
  ck_assert_int_eq(s21_create_matrix(-3, 4, &matrix), S21_INCORRECT_MATRIX);
}
END_TEST

Suite* matrix_suite(void) {
  Suite* s = suite_create("Matrix tests");

  TCase* tc_equal = tcase_create("matrix_equal");
  tcase_add_test(tc_equal, s21_eq_matrix_test_1);
  tcase_add_test(tc_equal, s21_eq_matrix_test_2);
  tcase_add_test(tc_equal, s21_eq_matrix_test_3);
  tcase_add_test(tc_equal, s21_eq_matrix_test_4);
  tcase_add_test(tc_equal, s21_eq_matrix_test_5);
  tcase_add_test(tc_equal, s21_eq_matrix_test_6);
  tcase_add_test(tc_equal, s21_eq_matrix_test_7);
  tcase_add_test(tc_equal, s21_eq_matrix_test_8);
  suite_add_tcase(s, tc_equal);

  TCase* tc_sum = tcase_create("matrix_sum");
  tcase_add_test(tc_sum, s21_sum_matrix_test_1);
  tcase_add_test(tc_sum, s21_sum_matrix_test_2);
  tcase_add_test(tc_sum, s21_sum_matrix_test_3);
  tcase_add_test(tc_sum, s21_sum_matrix_test_4);
  tcase_add_test(tc_sum, s21_sum_matrix_test_5);
  tcase_add_test(tc_sum, s21_sum_matrix_test_6);
  tcase_add_test(tc_sum, s21_sum_matrix_test_7);
  suite_add_tcase(s, tc_sum);

  TCase* tc_sub = tcase_create("matrix_sub");
  tcase_add_test(tc_sub, s21_sub_matrix_test_1);
  tcase_add_test(tc_sub, s21_sub_matrix_test_2);
  tcase_add_test(tc_sub, s21_sub_matrix_test_3);
  tcase_add_test(tc_sub, s21_sub_matrix_test_4);
  tcase_add_test(tc_sub, s21_sub_matrix_test_5);
  tcase_add_test(tc_sub, s21_sub_matrix_test_6);
  suite_add_tcase(s, tc_sub);

  TCase* tc_mult_num = tcase_create("matrix_mult_number");
  tcase_add_test(tc_mult_num, s21_mult_number_test_1);
  tcase_add_test(tc_mult_num, s21_mult_number_test_2);
  tcase_add_test(tc_mult_num, s21_mult_number_test_3);
  tcase_add_test(tc_mult_num, s21_mult_number_test_4);
  suite_add_tcase(s, tc_mult_num);

  TCase* tc_mult_matrix = tcase_create("matrix_mult");
  tcase_add_test(tc_mult_matrix, s21_mult_matrix_test_1);
  tcase_add_test(tc_mult_matrix, s21_mult_matrix_test_2);
  tcase_add_test(tc_mult_matrix, s21_mult_matrix_test_3);
  tcase_add_test(tc_mult_matrix, s21_mult_matrix_test_4);
  suite_add_tcase(s, tc_mult_matrix);

  TCase* tc_transpose = tcase_create("matrix_transpose");
  tcase_add_test(tc_transpose, s21_transpose_test_1);
  tcase_add_test(tc_transpose, s21_transpose_test_2);
  tcase_add_test(tc_transpose, s21_transpose_test_3);
  tcase_add_test(tc_transpose, s21_transpose_test_4);
  suite_add_tcase(s, tc_transpose);

  TCase* tc_det = tcase_create("matrix_determinant");
  tcase_add_test(tc_det, s21_determinant_test_1);
  tcase_add_test(tc_det, s21_determinant_test_2);
  tcase_add_test(tc_det, s21_determinant_test_3);
  tcase_add_test(tc_det, s21_determinant_test_4);
  tcase_add_test(tc_det, s21_determinant_test_5);
  tcase_add_test(tc_det, s21_determinant_test_6);
  tcase_add_test(tc_det, s21_determinant_test_7);
  tcase_add_test(tc_det, s21_determinant_test_8);
  suite_add_tcase(s, tc_det);

  TCase* tc_calc = tcase_create("matrix_calc_complements");
  tcase_add_test(tc_calc, s21_calc_complements_test_1);
  tcase_add_test(tc_calc, s21_calc_complements_test_2);
  tcase_add_test(tc_calc, s21_calc_complements_test_3);
  tcase_add_test(tc_calc, s21_calc_complements_test_4);
  tcase_add_test(tc_calc, s21_calc_complements_test_5);
  tcase_add_test(tc_calc, s21_calc_complements_test_6);
  tcase_add_test(tc_calc, s21_calc_complements_test_7);
  tcase_add_test(tc_calc, s21_calc_complements_test_8);
  suite_add_tcase(s, tc_calc);

  TCase* tc_inverse = tcase_create("matrix_inverse");
  tcase_add_test(tc_inverse, s21_inverse_test_1);
  tcase_add_test(tc_inverse, s21_inverse_test_2);
  tcase_add_test(tc_inverse, s21_inverse_test_3);
  tcase_add_test(tc_inverse, s21_inverse_test_4);
  tcase_add_test(tc_inverse, s21_inverse_test_5);
  tcase_add_test(tc_inverse, s21_inverse_test_6);
  tcase_add_test(tc_inverse, s21_inverse_test_7);
  suite_add_tcase(s, tc_inverse);

  TCase* tc_create = tcase_create("matrix_create");
  tcase_add_test(tc_create, s21_create_matrix_test_1);
  tcase_add_test(tc_create, s21_create_matrix_test_2);
  suite_add_tcase(s, tc_create);

  return s;
}

int main(void) {
  int number_failed = 0;
  Suite* s = matrix_suite();
  SRunner* sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
