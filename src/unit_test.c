#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_matrix.h"

#define OK 0
#define CALCULATION_ERROR 2
#define INCORRECT_MATRIX 1
#define SUCCESS 1
#define FAILURE 0

#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2

START_TEST(test_s21_create_matrix_1) {
  matrix_t my_matrix;
  int ret = s21_create_matrix(4, 4, &my_matrix);
  ck_assert_int_eq(ret, 0);
  s21_remove_matrix(&my_matrix);
}
END_TEST

START_TEST(test_s21_create_matrix_2) {
  matrix_t my_matrix;
  int ret = s21_create_matrix(-4, 4, &my_matrix);
  ck_assert_int_eq(ret, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_s21_create_matrix_3) {
  matrix_t my_matrix;
  int ret = s21_create_matrix(-4, 0, &my_matrix);
  ck_assert_int_eq(ret, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_s21_create_matrix_4) {
  matrix_t result_matrix;
  int res = s21_create_matrix(0, 0, &result_matrix);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}

START_TEST(test_s21_create_matrix_5) {
  matrix_t result_matrix;
  int res = s21_create_matrix(0, 4, &result_matrix);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}

START_TEST(test_s21_create_matrix_6) {
  matrix_t result_matrix;
  int res = s21_create_matrix(4, 0, &result_matrix);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}

START_TEST(test_s21_create_matrix_7) {
  int rows = 5;
  int columns = 5;
  matrix_t result_matrix;
  int res = s21_create_matrix(rows, columns, &result_matrix);

  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(result_matrix.rows, rows);
  ck_assert_int_eq(result_matrix.rows, columns);
  s21_remove_matrix(&result_matrix);
}

START_TEST(test_s21_create_matrix_8) {
  int rows = 3;
  int columns = 2;
  matrix_t result_matrix;
  int res = s21_create_matrix(rows, columns, &result_matrix);

  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(result_matrix.rows, rows);
  ck_assert_int_eq(result_matrix.columns, columns);
  s21_remove_matrix(&result_matrix);
}

START_TEST(test_s21_create_matrix_9) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = 0;
      ck_assert_ldouble_eq_tol(0, m.matrix[i][j], 1e-06);
    }
  }
  ck_assert_int_eq(m.rows, rows);
  ck_assert_int_eq(m.columns, cols);
  s21_remove_matrix(&m);
}

START_TEST(test_s21_create_matrix_10) {
  matrix_t my_matrix;
  int ret = 0;
  ret = s21_create_matrix(4, 4, &my_matrix);
  ck_assert_int_eq(ret, 0);
  s21_remove_matrix(&my_matrix);
}

START_TEST(test_s21_create_matrix_11) {
  matrix_t my_matrix;
  int ret = 0;
  ret = s21_create_matrix(-4, 4, &my_matrix);
  ck_assert_int_eq(ret, 1);
}

START_TEST(test_s21_create_matrix_12) {
  matrix_t my_matrix;
  int ret = 0;
  ret = s21_create_matrix(-4, 0, &my_matrix);
  ck_assert_int_eq(ret, 1);
}

START_TEST(test_s21_create_matrix_13) {
  const int rows = 0;
  const int cols = 10;
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), 1);
}

START_TEST(test_s21_create_matrix_14) {
  const int rows = 10;
  const int cols = 0;

  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), 1);
}

END_TEST

START_TEST(test_s21_remove_matrix_1) {
  matrix_t result_matrix;
  s21_create_matrix(1, 1, &result_matrix);
  s21_remove_matrix(&result_matrix);

  ck_assert_int_eq(result_matrix.matrix == NULL, SUCCESS);
}

START_TEST(test_s21_remove_matrix_2) {
  matrix_t result_matrix;
  s21_create_matrix(2, 2, &result_matrix);
  s21_remove_matrix(&result_matrix);

  ck_assert_int_eq(result_matrix.matrix == NULL, SUCCESS);
}

START_TEST(test_s21_remove_matrix_3) {
  matrix_t result_matrix;
  s21_create_matrix(3, 3, &result_matrix);
  s21_remove_matrix(&result_matrix);

  ck_assert_int_eq(result_matrix.matrix == NULL, SUCCESS);
}

START_TEST(test_s21_eq_matrix_1) {
  matrix_t matrix_1, matrix_2;
  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  int ret = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(test_s21_eq_matrix_2) {
  matrix_t matrix_1, matrix_2;
  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(10, 10, &matrix_2);
  int ret = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(ret, FAILURE);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(test_s21_eq_matrix_3) {
  matrix_t matrix_1, matrix_2;
  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  matrix_1.matrix[2][3] = -7;
  int ret = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(ret, FAILURE);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(test_s21_eq_matrix_4) {
  matrix_t matrix_1, matrix_2;
  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  matrix_1.matrix[2][3] = -7;
  matrix_2.matrix[2][3] = -7;
  int ret = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(ret, SUCCESS);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(test_s21_sum_matrix_1) {
  matrix_t matrix_1, matrix_2, res_my, res_org;
  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  s21_create_matrix(4, 4, &res_org);
  int ret = s21_sum_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_sum_matrix_2) {
  matrix_t matrix_1, matrix_2, res_my;
  s21_create_matrix(4, 5, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  int ret = s21_sum_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res_my);
}
END_TEST

START_TEST(test_s21_sum_matrix_3) {
  matrix_t matrix_1, matrix_2, res_my, res_org;
  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
      res_org.matrix[i][j] = i + j;
    }
  }
  int ret = s21_sum_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_sub_matrix_1) {
  matrix_t matrix_1, matrix_2, res_my, res_org;
  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  s21_create_matrix(4, 4, &res_org);
  int ret = s21_sub_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_sub_matrix_2) {
  matrix_t matrix_1, matrix_2, res_my;
  s21_create_matrix(4, 5, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  int ret = s21_sub_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res_my);
}
END_TEST

START_TEST(test_s21_sub_matrix_3) {
  matrix_t matrix_1 = {0}, matrix_2, res_my;
  s21_create_matrix(4, 4, &matrix_2);
  int ret = s21_sub_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(test_s21_sub_matrix_4) {
  matrix_t matrix_1, matrix_2, res_my, res_org;
  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);
  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
      res_org.matrix[i][j] = i + j;
    }
  }
  int ret = s21_sub_matrix(&matrix_1, &matrix_2, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_mult_number) {
  matrix_t matrix_1, res_my, res_org;
  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &res_org);
  int ret = s21_mult_number(&matrix_1, 5, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);

  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
      res_org.matrix[i][j] = (i + j) * (-3);
    }
  }
  ret = s21_mult_number(&matrix_1, -3, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);

  s21_create_matrix(4, 4, &res_org);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_1.matrix[i][j] = i + j;
    }
  }
  ret = s21_mult_number(&matrix_1, 0, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_my, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_mult_matrix_1) {
  matrix_t matrix;
  matrix_t result;

  int rows = 3;
  int columns = 3;

  s21_create_matrix(rows, columns, &matrix);
  matrix.matrix[0][0] = 5;
  matrix.matrix[0][1] = 8;
  matrix.matrix[0][2] = -4;
  matrix.matrix[1][0] = 6;
  matrix.matrix[1][1] = 9;
  matrix.matrix[1][2] = -5;
  matrix.matrix[2][0] = 4;
  matrix.matrix[2][1] = 7;
  matrix.matrix[2][2] = -3;

  int res = s21_mult_matrix(&matrix, &matrix, &result);
  ck_assert_int_eq(res, OK);

  ck_assert_double_eq(result.matrix[0][0], 57);
  ck_assert_double_eq(result.matrix[0][1], 84);
  ck_assert_double_eq(result.matrix[0][2], -48);
  ck_assert_double_eq(result.matrix[1][0], 64);
  ck_assert_double_eq(result.matrix[1][1], 94);
  ck_assert_double_eq(result.matrix[1][2], -54);
  ck_assert_double_eq(result.matrix[2][0], 50);
  ck_assert_double_eq(result.matrix[2][1], 74);
  ck_assert_double_eq(result.matrix[2][2], -42);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_mult_matrix_2) {
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t result;

  int rows1 = 2;
  int columns1 = 3;

  int rows2 = 3;
  int columns2 = 2;

  s21_create_matrix(rows1, columns1, &matrix1);
  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[0][2] = 3;
  matrix1.matrix[1][0] = 4;
  matrix1.matrix[1][1] = 5;
  matrix1.matrix[1][2] = 6;

  s21_create_matrix(rows2, columns2, &matrix2);
  matrix2.matrix[0][0] = 7;
  matrix2.matrix[0][1] = 8;
  matrix2.matrix[1][0] = 9;
  matrix2.matrix[1][1] = 1;
  matrix2.matrix[2][0] = 2;
  matrix2.matrix[2][1] = 3;

  int res = s21_mult_matrix(&matrix1, &matrix2, &result);
  ck_assert_int_eq(res, OK);

  ck_assert_double_eq(result.matrix[0][0], 31);
  ck_assert_double_eq(result.matrix[0][1], 19);
  ck_assert_double_eq(result.matrix[1][0], 85);
  ck_assert_double_eq(result.matrix[1][1], 55);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_mult_matrix_3) {
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t result;

  int rows1 = 2;
  int columns1 = 3;

  int rows2 = 2;
  int columns2 = 2;

  s21_create_matrix(rows1, columns1, &matrix1);
  s21_create_matrix(rows2, columns2, &matrix2);

  int res = s21_mult_matrix(&matrix1, &matrix2, &result);
  ck_assert_int_eq(res, CALCULATION_ERROR);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_mult_matrix_4) {
  matrix_t A, B, result, res_origin;
  int check_origin = 0;
  int check_1 = s21_create_matrix(5, 4, &A);
  int check_2 = s21_create_matrix(4, 4, &B);
  int check_4 = s21_create_matrix(5, 4, &res_origin);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[0][3] = -4;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[1][3] = 14;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;
  A.matrix[2][3] = -1;
  A.matrix[3][0] = 10;
  A.matrix[3][1] = 3;
  A.matrix[3][2] = 9;
  A.matrix[3][3] = -3;
  A.matrix[4][0] = -3;
  A.matrix[4][1] = 3;
  A.matrix[4][2] = 1;
  A.matrix[4][3] = 5;
  B.matrix[0][0] = 8;
  B.matrix[0][1] = 8;
  B.matrix[0][2] = 3;
  B.matrix[0][3] = 5;
  B.matrix[1][0] = -7;
  B.matrix[1][1] = 7;
  B.matrix[1][2] = 1;
  B.matrix[1][3] = 1;
  B.matrix[2][0] = 7;
  B.matrix[2][1] = 3;
  B.matrix[2][2] = 4;
  B.matrix[2][3] = -4;
  B.matrix[3][0] = 10;
  B.matrix[3][1] = 3;
  B.matrix[3][2] = 9;
  B.matrix[3][3] = -3;
  res_origin.matrix[0][0] = -10;
  res_origin.matrix[0][1] = 60;
  res_origin.matrix[0][2] = 3;
  res_origin.matrix[0][3] = -1;
  res_origin.matrix[1][0] = 195;
  res_origin.matrix[1][1] = 123;
  res_origin.matrix[1][2] = 163;
  res_origin.matrix[1][3] = -25;
  res_origin.matrix[2][0] = 23;
  res_origin.matrix[2][1] = 14;
  res_origin.matrix[2][2] = -8;
  res_origin.matrix[2][3] = 38;
  res_origin.matrix[3][0] = 92;
  res_origin.matrix[3][1] = 119;
  res_origin.matrix[3][2] = 42;
  res_origin.matrix[3][3] = 26;
  res_origin.matrix[4][0] = 12;
  res_origin.matrix[4][1] = 15;
  res_origin.matrix[4][2] = 43;
  res_origin.matrix[4][3] = -31;
  int check = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(check_1, check_origin);
  ck_assert_int_eq(check_2, check_origin);
  ck_assert_int_eq(check_4, check_origin);
  ck_assert_int_eq(check, check_origin);
  for (int i = 0; i < res_origin.rows; i++) {
    for (int j = 0; j < res_origin.columns; j++) {
      ck_assert_uint_eq(res_origin.matrix[i][j], result.matrix[i][j]);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&res_origin);
}
END_TEST

START_TEST(test_s21_mult_matrix_5) {
  matrix_t A, B, result, res_origin;
  int check_origin = 0;
  int check_1 = s21_create_matrix(2, 2, &A);
  int check_2 = s21_create_matrix(2, 4, &B);
  int check_4 = s21_create_matrix(2, 4, &res_origin);
  A.matrix[0][0] = 2.987654;
  A.matrix[0][1] = -5.3456;
  A.matrix[1][0] = 6.23;
  A.matrix[1][1] = -3.9292;
  B.matrix[0][0] = 4.838;
  B.matrix[0][1] = 8.0987;
  B.matrix[0][2] = 8.09;
  B.matrix[0][3] = -987;
  B.matrix[1][0] = -8;
  B.matrix[1][1] = -0.921;
  B.matrix[1][2] = -0.91;
  B.matrix[1][3] = 21;
  res_origin.matrix[0][0] = 57.219070052;
  res_origin.matrix[0][1] = 29.1194110498;
  res_origin.matrix[0][2] = 29.03461686;
  res_origin.matrix[0][3] = -3061.072098;
  res_origin.matrix[1][0] = 61.57434;
  res_origin.matrix[1][1] = 54.0736942;
  res_origin.matrix[1][2] = 53.976272;
  res_origin.matrix[1][3] = -6231.5232;
  int check = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(check_1, check_origin);
  ck_assert_int_eq(check_2, check_origin);
  ck_assert_int_eq(check_4, check_origin);
  ck_assert_int_eq(check, check_origin);
  for (int i = 0; i < res_origin.rows; i++) {
    for (int j = 0; j < res_origin.columns; j++) {
      ck_assert_uint_eq(res_origin.matrix[i][j], result.matrix[i][j]);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&res_origin);
}
END_TEST

START_TEST(test_s21_mult_matrix_6) {
  matrix_t A, B, result, res_origin;
  int check_origin = 0;
  int check_1 = s21_create_matrix(3, 3, &A);
  int check_2 = s21_create_matrix(3, 3, &B);
  int check_4 = s21_create_matrix(3, 3, &res_origin);
  A.matrix[0][0] = 0;
  A.matrix[0][1] = 9;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 7;
  A.matrix[2][0] = 2;
  A.matrix[2][1] = 7;
  A.matrix[2][2] = 0;
  B.matrix[0][0] = 0;
  B.matrix[0][1] = 9;
  B.matrix[0][2] = 8;
  B.matrix[1][0] = 0;
  B.matrix[1][1] = 9;
  B.matrix[1][2] = 9;
  B.matrix[2][0] = 1;
  B.matrix[2][1] = 9;
  B.matrix[2][2] = 6;
  res_origin.matrix[0][0] = 1;
  res_origin.matrix[0][1] = 90;
  res_origin.matrix[0][2] = 87;
  res_origin.matrix[1][0] = 7;
  res_origin.matrix[1][1] = 99;
  res_origin.matrix[1][2] = 77;
  res_origin.matrix[2][0] = 0;
  res_origin.matrix[2][1] = 81;
  res_origin.matrix[2][2] = 79;
  int check = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(check_1, check_origin);
  ck_assert_int_eq(check_2, check_origin);
  ck_assert_int_eq(check_4, check_origin);
  ck_assert_int_eq(check, check_origin);
  for (int i = 0; i < res_origin.rows; i++) {
    for (int j = 0; j < res_origin.columns; j++) {
      ck_assert_uint_eq(res_origin.matrix[i][j], result.matrix[i][j]);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&res_origin);
}
END_TEST

START_TEST(test_s21_mult_matrix_7) {
  matrix_t A, B, result;
  int check_origin = 2;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(4, 2, &B);
  int check = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(check, check_origin);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_mult_matrix_8) {
  matrix_t A, B, result;
  int check_origin = 0;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 12, &B);
  for (int i = 0; i < B.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      B.matrix[i][j] = i + j;
    }
  }
  int check = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(check, check_origin);
  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_int_eq(result.matrix[i][j], 0.0);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_mult_matrix_9) {
  const int rows = 2;
  const int cols = 3;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(cols, rows, &mtx);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m.matrix[i][j] = c++;

  for (int i = 0, c = 7; i < cols; i++)
    for (int j = 0; j < rows; j++) mtx.matrix[i][j] = c++;

  matrix_t check = {0};
  s21_create_matrix(m.rows, mtx.columns, &check);
  check.matrix[0][0] = 58;
  check.matrix[0][1] = 64;
  check.matrix[1][0] = 139;
  check.matrix[1][1] = 154;

  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_matrix(&m, &mtx, &res), 0);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_s21_mult_matrix_10) {
  matrix_t mat_1, mat_2, res_mat, res_org;
  s21_create_matrix(2, 2, &mat_1);
  s21_create_matrix(2, 2, &mat_2);
  s21_create_matrix(2, 2, &res_org);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      mat_1.matrix[i][j] = i + j + 1;
      mat_2.matrix[i][j] = i + j + 1;
    }
  }
  res_org.matrix[0][0] = 5;
  res_org.matrix[0][1] = 8;
  res_org.matrix[1][0] = 8;
  res_org.matrix[1][1] = 13;
  int ret = s21_mult_matrix(&mat_1, &mat_2, &res_mat);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&res_mat);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_mult_matrix_11) {
  matrix_t mat_1, mat_2, res_mat, res_org;
  s21_create_matrix(3, 2, &mat_1);
  s21_create_matrix(2, 2, &mat_2);
  s21_create_matrix(3, 2, &res_org);
  int ret = s21_mult_matrix(&mat_1, &mat_2, &res_mat);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&res_mat);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_mult_matrix_12) {
  matrix_t mat_1, mat_2, res_mat;
  s21_create_matrix(2, 7, &mat_1);
  s21_create_matrix(2, 2, &mat_2);
  int ret = s21_mult_matrix(&mat_1, &mat_2, &res_mat);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&res_mat);
}
END_TEST

START_TEST(test_s21_transpose_0) {
  matrix_t mat_1, res_mat, res_org;
  s21_create_matrix(2, 2, &mat_1);
  s21_create_matrix(2, 2, &res_org);
  mat_1.matrix[0][0] = 1;
  mat_1.matrix[0][1] = 2;
  mat_1.matrix[1][0] = 3;
  mat_1.matrix[1][1] = 4;
  res_org.matrix[0][0] = 1;
  res_org.matrix[0][1] = 3;
  res_org.matrix[1][0] = 2;
  res_org.matrix[1][1] = 4;
  int ret = s21_transpose(&mat_1, &res_mat);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&res_mat);
  s21_remove_matrix(&res_org);

  double matrix[2][2] = {
      {1, 2},
      {3, 4},
  };
  double res[2][2] = {{1, 3}, {2, 4}};
  s21_create_matrix(2, 2, &mat_1);
  s21_create_matrix(2, 2, &res_org);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      mat_1.matrix[i][j] = matrix[i][j];
    }
  }
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      res_org.matrix[i][j] = res[i][j];
    }
  }
  ret = s21_transpose(&mat_1, &res_mat);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&res_mat);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_transpose_1) {
  matrix_t matrix;
  matrix_t result;

  s21_create_matrix(3, 3, &matrix);
  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 3;
  matrix.matrix[1][0] = 4;
  matrix.matrix[1][1] = 5;
  matrix.matrix[1][2] = 6;
  matrix.matrix[2][0] = 7;
  matrix.matrix[2][1] = 8;
  matrix.matrix[2][2] = 9;

  int res = s21_transpose(&matrix, &result);
  ck_assert_uint_eq(res, OK);

  ck_assert_double_eq(result.matrix[0][0], 1);
  ck_assert_double_eq(result.matrix[0][1], 4);
  ck_assert_double_eq(result.matrix[0][2], 7);
  ck_assert_double_eq(result.matrix[1][0], 2);
  ck_assert_double_eq(result.matrix[1][1], 5);
  ck_assert_double_eq(result.matrix[1][2], 8);
  ck_assert_double_eq(result.matrix[2][0], 3);
  ck_assert_double_eq(result.matrix[2][1], 6);
  ck_assert_double_eq(result.matrix[2][2], 9);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_transpose_2) {
  matrix_t matrix;
  matrix_t result;

  s21_create_matrix(3, 2, &matrix);
  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[1][0] = 4;
  matrix.matrix[1][1] = 5;
  matrix.matrix[2][0] = 7;
  matrix.matrix[2][1] = 8;

  int res = s21_transpose(&matrix, &result);
  ck_assert_uint_eq(res, OK);

  ck_assert_double_eq(result.matrix[0][0], 1);
  ck_assert_double_eq(result.matrix[0][1], 4);
  ck_assert_double_eq(result.matrix[0][2], 7);
  ck_assert_double_eq(result.matrix[1][0], 2);
  ck_assert_double_eq(result.matrix[1][1], 5);
  ck_assert_double_eq(result.matrix[1][2], 8);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_transpose_3) {
  matrix_t matrix;
  matrix_t result;

  s21_create_matrix(1, 3, &matrix);
  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 4;

  int res = s21_transpose(&matrix, &result);
  ck_assert_uint_eq(res, OK);

  ck_assert_double_eq(result.matrix[0][0], 1);
  ck_assert_double_eq(result.matrix[1][0], 2);
  ck_assert_double_eq(result.matrix[2][0], 4);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_determinant_0) {
  matrix_t matrix;
  s21_create_matrix(3, 3, &matrix);
  int count = 1;
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      matrix.matrix[i][j] = count++;
    }
  }
  matrix.matrix[2][2] = 10;
  double res;
  int ret = s21_determinant(&matrix, &res);
  ck_assert_uint_eq(res, -3);
  ck_assert_int_eq(ret, 0);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(test_s21_determinant_1) {
  matrix_t matrix;
  s21_create_matrix(1, 1, &matrix);
  matrix.matrix[0][0] = 1.232;

  double det = 0;

  int res = s21_determinant(&matrix, &det);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq_tol(det, 1.232, 1E-6);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(test_s21_determinant_2) {
  matrix_t matrix;
  s21_create_matrix(2, 2, &matrix);
  matrix.matrix[0][0] = 2342.234;
  matrix.matrix[0][1] = 2.312;
  matrix.matrix[1][0] = 24.234;
  matrix.matrix[1][1] = 424.2;

  double det = 0;

  int res = s21_determinant(&matrix, &det);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq_tol(det, 993519.633792, 1E-6);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(test_s21_determinant_3) {
  matrix_t matrix;
  s21_create_matrix(3, 3, &matrix);
  matrix.matrix[0][0] = 2.34;
  matrix.matrix[0][1] = 27.345;
  matrix.matrix[0][2] = 25.23;
  matrix.matrix[1][0] = 2.55;
  matrix.matrix[1][1] = 8.56;
  matrix.matrix[1][2] = 45.75;
  matrix.matrix[2][0] = 55.3;
  matrix.matrix[2][1] = 4.34;
  matrix.matrix[2][2] = 24.33;

  double det = 0;

  int res = s21_determinant(&matrix, &det);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq_tol(det, 55844.5082595, 1E-6);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(test_s21_determinant_4) {
  matrix_t matrix;
  s21_create_matrix(4, 4, &matrix);
  matrix.matrix[0][0] = 1.34;
  matrix.matrix[0][1] = 7.423;
  matrix.matrix[0][2] = 2.45;
  matrix.matrix[0][3] = 2.42;
  matrix.matrix[1][0] = 34;
  matrix.matrix[1][1] = 2;
  matrix.matrix[1][2] = 5;
  matrix.matrix[1][3] = 24.52;
  matrix.matrix[2][0] = 3;
  matrix.matrix[2][1] = 4.5;
  matrix.matrix[2][2] = 2.4;
  matrix.matrix[2][3] = 2.4;
  matrix.matrix[3][0] = 8.43;
  matrix.matrix[3][1] = 3.5;
  matrix.matrix[3][2] = 53.6;
  matrix.matrix[3][3] = 24.5;

  double det = 0;

  int res = s21_determinant(&matrix, &det);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq_tol(det, -10769.66942328, 1E-6);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(test_s21_determinant_5) {
  matrix_t matrix;
  s21_create_matrix(4, 3, &matrix);
  double det = 0;

  int res = s21_determinant(&matrix, &det);
  ck_assert_int_eq(res, CALCULATION_ERROR);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(test_s21_determinant_6) {
  matrix_t A;
  double B, R = 1.25;
  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 1.25;

  s21_determinant(&A, &B);

  ck_assert(fabs(B - R) < 1e-7);

  s21_remove_matrix(&A);
}

END_TEST

START_TEST(test_s21_determinant_7) {
  matrix_t A;
  double B, R = -69;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 10;
  A.matrix[1][2] = 5.25;
  A.matrix[2][0] = 6.25;
  A.matrix[2][1] = 7.25;
  A.matrix[2][2] = 8.25;

  s21_determinant(&A, &B);

  ck_assert(fabs(B - R) < 1e-7);

  s21_remove_matrix(&A);
}

END_TEST

START_TEST(test_s21_determinant_8) {
  matrix_t A;
  double B, R = -2;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 4;
  A.matrix[0][2] = -6;
  A.matrix[1][0] = -5;
  A.matrix[1][1] = -7;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 5;
  A.matrix[2][2] = -6;

  s21_determinant(&A, &B);

  ck_assert(fabs(B - R) < 1e-7);

  s21_remove_matrix(&A);
}

END_TEST

START_TEST(test_s21_determinant_9) {
  matrix_t A;
  double B, R = 25;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = -3;
  A.matrix[0][1] = 4;
  A.matrix[0][2] = -6;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = -7;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = -4;
  A.matrix[2][1] = 5;
  A.matrix[2][2] = -6;

  s21_determinant(&A, &B);

  ck_assert(fabs(B - R) < 1e-7);

  s21_remove_matrix(&A);
}

END_TEST

START_TEST(test_s21_determinant_10) {
  matrix_t A;
  double B, R = 23;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = -3;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = -6;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = -5;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = -4;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = -6;

  s21_determinant(&A, &B);

  ck_assert(fabs(B - R) < 1e-7);

  s21_remove_matrix(&A);
}

END_TEST

START_TEST(test_s21_determinant_11) {
  matrix_t A;
  double B, R = -8;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = -3;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = -5;
  A.matrix[1][2] = -7;
  A.matrix[2][0] = -4;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 5;

  s21_determinant(&A, &B);

  ck_assert(fabs(B - R) < 1e-7);

  s21_remove_matrix(&A);
}

END_TEST

START_TEST(test_s21_determinant_12) {
  matrix_t A = {0};
  double B, R = 18;
  s21_create_matrix(4, 4, &A);

  A.matrix[0][0] = 3;
  A.matrix[0][1] = -3;
  A.matrix[0][2] = -5;
  A.matrix[0][3] = 8;
  A.matrix[1][0] = -3;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 4;
  A.matrix[1][3] = -6;
  A.matrix[2][0] = 2;
  A.matrix[2][1] = -5;
  A.matrix[2][2] = -7;
  A.matrix[2][3] = 5;
  A.matrix[3][0] = -4;
  A.matrix[3][1] = 3;
  A.matrix[3][2] = 5;
  A.matrix[3][3] = -6;

  s21_determinant(&A, &B);

  ck_assert(fabs(B - R) < 1e-7);

  s21_remove_matrix(&A);
}

END_TEST

START_TEST(test_s21_determinant_13) {
  matrix_t A = {0};
  double B, R = -69.0 / 4.0;
  s21_create_matrix(5, 5, &A);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[0][3] = 3.25;
  A.matrix[0][4] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 10;
  A.matrix[1][2] = 5.25;
  A.matrix[1][3] = 5.25;
  A.matrix[1][4] = 5.25;
  A.matrix[2][0] = 6.25;
  A.matrix[2][1] = 7.25;
  A.matrix[2][2] = 8.25;
  A.matrix[2][3] = 6.25;
  A.matrix[2][4] = 6.25;
  A.matrix[3][0] = 6.25;
  A.matrix[3][1] = 7.25;
  A.matrix[3][2] = 8.25;
  A.matrix[3][3] = 6.25;
  A.matrix[3][4] = 7.25;
  A.matrix[4][0] = 6.25;
  A.matrix[4][1] = 7.25;
  A.matrix[4][2] = 8.25;
  A.matrix[4][3] = 6;
  A.matrix[4][4] = 8.25;

  s21_determinant(&A, &B);

  ck_assert(fabs(B - R) < 1e-7);

  s21_remove_matrix(&A);
}

END_TEST

START_TEST(test_s21_determinant_14) {
  matrix_t A;
  double B;
  s21_create_matrix(4, 5, &A);
  int res = s21_determinant(&A, &B);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
}

END_TEST

START_TEST(test_s21_determinant_15) {
  matrix_t a = {0};
  double number;
  s21_create_matrix(4, 4, &a);
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[0][2] = 3;
  a.matrix[0][3] = 13;
  a.matrix[1][0] = 4;
  a.matrix[1][1] = 5;
  a.matrix[1][2] = 6;
  a.matrix[1][3] = 16;
  a.matrix[2][0] = 7;
  a.matrix[2][1] = 8;
  a.matrix[2][2] = 90;
  a.matrix[2][3] = 19;
  a.matrix[3][0] = 1;
  a.matrix[3][1] = 7;
  a.matrix[3][2] = 7;
  a.matrix[3][3] = 17;

  s21_determinant(&a, &number);
  ck_assert_int_eq(number, 13608);
  s21_remove_matrix(&a);
}

END_TEST

START_TEST(test_s21_determinant_16) {
  matrix_t *B = NULL;
  double re = 0;
  int res = s21_determinant(B, &re);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(test_s21_determinant_17) {
  matrix_t a = {0};
  double number;
  s21_create_matrix(4, 4, &a);
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 2;
  a.matrix[0][2] = 3;
  a.matrix[0][3] = 13;
  a.matrix[1][0] = 0;
  a.matrix[1][1] = 0;
  a.matrix[1][2] = 6;
  a.matrix[1][3] = 16;
  a.matrix[2][0] = 0;
  a.matrix[2][1] = 0;
  a.matrix[2][2] = 90;
  a.matrix[2][3] = 19;
  a.matrix[3][0] = 0;
  a.matrix[3][1] = 7;
  a.matrix[3][2] = 7;
  a.matrix[3][3] = 17;

  s21_determinant(&a, &number);
  ck_assert_int_eq(number, -9282);
  s21_remove_matrix(&a);
}

END_TEST

START_TEST(test_s21_calc_complements) {
  double m[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  double r[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};
  matrix_t matrix, res_org, res_my;
  s21_create_matrix(3, 3, &matrix);
  s21_create_matrix(3, 3, &res_org);
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      matrix.matrix[i][j] = m[i][j];
    }
  }
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      res_org.matrix[i][j] = r[i][j];
    }
  }
  int ret = s21_calc_complements(&matrix, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_org, &res_my);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_calc_complements_1) {
  matrix_t matrix;
  matrix_t result;

  s21_create_matrix(2, 1, &matrix);

  int res = s21_calc_complements(&matrix, &result);
  ck_assert_int_eq(res, CALCULATION_ERROR);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_calc_complements_2) {
  matrix_t matrix;
  matrix_t result;

  s21_create_matrix(2, 2, &matrix);
  matrix.matrix[0][0] = 3;
  matrix.matrix[0][1] = 4;
  matrix.matrix[1][0] = 5;
  matrix.matrix[1][1] = 7;

  int res = s21_calc_complements(&matrix, &result);
  ck_assert_int_eq(res, OK);

  ck_assert_double_eq(result.matrix[0][0], 7);
  ck_assert_double_eq(result.matrix[0][1], -5);
  ck_assert_double_eq(result.matrix[1][0], -4);
  ck_assert_double_eq(result.matrix[1][1], 3);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_calc_complements_3) {
  matrix_t matrix;
  matrix_t result;

  s21_create_matrix(3, 3, &matrix);
  matrix.matrix[0][0] = 2;
  matrix.matrix[0][1] = 5;
  matrix.matrix[0][2] = 7;
  matrix.matrix[1][0] = 6;
  matrix.matrix[1][1] = 3;
  matrix.matrix[1][2] = 4;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = -2;
  matrix.matrix[2][2] = -3;

  int res = s21_calc_complements(&matrix, &result);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq(result.matrix[0][0], -1);
  ck_assert_double_eq(result.matrix[0][1], 38);
  ck_assert_double_eq(result.matrix[0][2], -27);
  ck_assert_double_eq(result.matrix[1][0], 1);
  ck_assert_double_eq(result.matrix[1][1], -41);
  ck_assert_double_eq(result.matrix[1][2], 29);
  ck_assert_double_eq(result.matrix[2][0], -1);
  ck_assert_double_eq(result.matrix[2][1], 34);
  ck_assert_double_eq(result.matrix[2][2], -24);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_calc_complements_4) {
  matrix_t matrix;
  matrix_t result;

  s21_create_matrix(4, 4, &matrix);
  matrix.matrix[0][0] = 2;
  matrix.matrix[0][1] = 1;
  matrix.matrix[0][2] = 0;
  matrix.matrix[0][3] = 0;
  matrix.matrix[1][0] = 3;
  matrix.matrix[1][1] = 2;
  matrix.matrix[1][2] = 0;
  matrix.matrix[1][3] = 0;
  matrix.matrix[2][0] = 1;
  matrix.matrix[2][1] = 1;
  matrix.matrix[2][2] = 3;
  matrix.matrix[2][3] = 4;
  matrix.matrix[3][0] = 2;
  matrix.matrix[3][1] = -1;
  matrix.matrix[3][2] = 2;
  matrix.matrix[3][3] = 3;

  int res = s21_calc_complements(&matrix, &result);
  ck_assert_int_eq(res, OK);

  ck_assert_int_eq(fabs(result.matrix[0][0]) - 2 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[0][1]) - 3 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[0][2]) - 31 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[0][3]) - 23 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[1][0]) - 1 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[1][1]) - 2 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[1][2]) - 19 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[1][3]) - 14 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[2][0]) - 0 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[2][1]) - 0 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[2][2]) - 3 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[2][3]) - 2 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[3][0]) - 0 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[3][1]) - 0 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[3][2]) - 4 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[3][3]) - 3 < 1e-7, 1);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_calc_complements_5) {
  matrix_t matrix;
  matrix_t result;

  s21_create_matrix(1, 1, &matrix);

  int res = s21_calc_complements(&matrix, &result);
  ck_assert_int_eq(res, CALCULATION_ERROR);  // calc_error ???

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_calc_complements_6) {
  double m[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  double r[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};
  matrix_t matrix, res_org, res_my;
  s21_create_matrix(3, 3, &matrix);
  s21_create_matrix(3, 3, &res_org);
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      matrix.matrix[i][j] = m[i][j];
    }
  }
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      res_org.matrix[i][j] = r[i][j];
    }
  }
  int ret = s21_calc_complements(&matrix, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_org, &res_my);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(test_s21_calc_complements_7) {
  matrix_t A, B, R;
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &A);
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[0][2] = 3;
  B.matrix[1][0] = 0;
  B.matrix[1][1] = 4;
  B.matrix[1][2] = 2;
  B.matrix[2][0] = 5;
  B.matrix[2][1] = 2;
  B.matrix[2][2] = 1;

  A.matrix[0][0] = 0;
  A.matrix[0][1] = 10;
  A.matrix[0][2] = -20;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = -14;
  A.matrix[1][2] = 8;
  A.matrix[2][0] = -8;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = 4;

  int code = s21_calc_complements(&B, &R);
  ck_assert_int_eq(s21_eq_matrix(&R, &A), SUCCESS);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&A);
}

END_TEST

START_TEST(test_s21_calc_complements_8) {
  matrix_t A, B, R;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  A.matrix[0][0] = 5;
  A.matrix[0][1] = -1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 3;

  s21_calc_complements(&A, &R);

  B.matrix[0][0] = 9;
  B.matrix[0][1] = -2;
  B.matrix[0][2] = -3;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 14;
  B.matrix[1][2] = -1;
  B.matrix[2][0] = -7;
  B.matrix[2][1] = -18;
  B.matrix[2][2] = 17;

  ck_assert_int_eq(s21_eq_matrix(&R, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}

END_TEST

START_TEST(test_s21_calc_complements_9) {
  matrix_t B, R;
  s21_create_matrix(2, 3, &B);

  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[0][2] = 3;
  B.matrix[1][0] = 0;
  B.matrix[1][1] = 4;
  B.matrix[1][2] = 2;

  int code = s21_calc_complements(&B, &R);

  ck_assert_int_eq(code, 2);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}

END_TEST

START_TEST(test_s21_calc_complements_10) {
  matrix_t A, B, R;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 5;

  s21_calc_complements(&A, &R);

  B.matrix[0][0] = 5;

  ck_assert_int_eq(s21_eq_matrix(&R, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}

END_TEST

START_TEST(test_s21_calc_complements_11) {
  matrix_t *B = NULL;
  matrix_t *R = NULL;
  int res = s21_calc_complements(B, R);
  ck_assert_int_eq(res, 1);
}

END_TEST

START_TEST(test_s21_inverse_matrix_0) {
  double m[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double r[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
  matrix_t matrix, res_org, res_my;
  s21_create_matrix(3, 3, &matrix);
  s21_create_matrix(3, 3, &res_org);
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      matrix.matrix[i][j] = m[i][j];
    }
  }
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      res_org.matrix[i][j] = r[i][j];
    }
  }
  int ret = s21_inverse_matrix(&matrix, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_org, &res_my);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST
START_TEST(test_s21_inverse_matrix_1) {
  matrix_t matrix;
  matrix_t result;

  s21_create_matrix(3, 3, &matrix);
  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 3;
  matrix.matrix[1][0] = 4;
  matrix.matrix[1][1] = 5;
  matrix.matrix[1][2] = 6;
  matrix.matrix[2][0] = 7;
  matrix.matrix[2][1] = 8;
  matrix.matrix[2][2] = 9;

  int res = s21_inverse_matrix(&matrix, &result);
  ck_assert_int_eq(res, CALCULATION_ERROR);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(test_s21_inverse_matrix_2) {
  matrix_t matrix;
  matrix_t result;

  s21_create_matrix(2, 2, &matrix);
  matrix.matrix[0][0] = 3;
  matrix.matrix[0][1] = 4;
  matrix.matrix[1][0] = 5;
  matrix.matrix[1][1] = 7;

  int res = s21_inverse_matrix(&matrix, &result);
  ck_assert_int_eq(res, OK);

  ck_assert_double_eq(result.matrix[0][0], 7);
  ck_assert_double_eq(result.matrix[0][1], -4);
  ck_assert_double_eq(result.matrix[1][0], -5);
  ck_assert_double_eq(result.matrix[1][1], 3);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_inverse_matrix_3) {
  matrix_t matrix;
  matrix_t result;

  s21_create_matrix(3, 3, &matrix);
  matrix.matrix[0][0] = 2;
  matrix.matrix[0][1] = 5;
  matrix.matrix[0][2] = 7;
  matrix.matrix[1][0] = 6;
  matrix.matrix[1][1] = 3;
  matrix.matrix[1][2] = 4;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = -2;
  matrix.matrix[2][2] = -3;

  int res = s21_inverse_matrix(&matrix, &result);
  ck_assert_int_eq(res, OK);

  ck_assert_int_eq(fabs(result.matrix[0][0]) - 1 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[0][1]) - 1 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[0][2]) - 1 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[1][0]) - 38 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[1][1]) - 41 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[1][2]) - 34 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[2][0]) - 27 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[2][1]) - 29 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[2][2]) - 24 < 1e-7, 1);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_inverse_matrix_4) {
  matrix_t matrix;
  matrix_t result;

  s21_create_matrix(4, 4, &matrix);
  matrix.matrix[0][0] = 2;
  matrix.matrix[0][1] = 1;
  matrix.matrix[0][2] = 0;
  matrix.matrix[0][3] = 0;
  matrix.matrix[1][0] = 3;
  matrix.matrix[1][1] = 2;
  matrix.matrix[1][2] = 0;
  matrix.matrix[1][3] = 0;
  matrix.matrix[2][0] = 1;
  matrix.matrix[2][1] = 1;
  matrix.matrix[2][2] = 3;
  matrix.matrix[2][3] = 4;
  matrix.matrix[3][0] = 2;
  matrix.matrix[3][1] = -1;
  matrix.matrix[3][2] = 2;
  matrix.matrix[3][3] = 3;

  int res = s21_inverse_matrix(&matrix, &result);
  ck_assert_int_eq(res, OK);

  ck_assert_int_eq(fabs(result.matrix[0][0]) - 2 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[0][1]) - 1 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[0][2]) - 0 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[0][3]) - 0 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[1][0]) - 3 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[1][1]) - 2 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[1][2]) - 0 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[1][3]) - 0 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[2][0]) - 31 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[2][1]) - 19 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[2][2]) - 3 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[2][3]) - 4 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[3][0]) - 23 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[3][1]) - 14 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[3][2]) - 2 < 1e-7, 1);
  ck_assert_int_eq(fabs(result.matrix[3][3]) - 3 < 1e-7, 1);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_inverse_matrix_5) {
  matrix_t matrix;
  matrix_t result;
  s21_create_matrix(4, 3, &matrix);

  int res = s21_inverse_matrix(&matrix, &result);
  ck_assert_int_eq(res, CALCULATION_ERROR);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(test_s21_inverse_matrix_6) {
  matrix_t matrix = {0};
  matrix_t result = {0};
  s21_create_matrix(1, 1, &matrix);
  matrix.matrix[0][0] = 5;

  int res = s21_inverse_matrix(&matrix, &result);
  ck_assert_int_eq(res, OK);
  ck_assert_double_eq(1.0 / matrix.matrix[0][0], result.matrix[0][0]);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_inverse_matrix_7) {
  matrix_t matrix = {0};
  matrix_t result = {0};
  s21_create_matrix(-1, -1, &matrix);

  int res = s21_inverse_matrix(&matrix, &result);
  ck_assert_int_eq(res, INCORRECT_MATRIX);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(test_s21_inverse_matrix_8) {
  matrix_t result1;
  matrix_t result2;
  matrix_t result3;
  s21_create_matrix(3, 3, &result1);
  result1.matrix[0][0] = 2;
  result1.matrix[0][1] = 5;
  result1.matrix[0][2] = 7;

  result1.matrix[1][0] = 6;
  result1.matrix[1][1] = 3;
  result1.matrix[1][2] = 4;

  result1.matrix[2][0] = 5;
  result1.matrix[2][1] = -2;
  result1.matrix[2][2] = -3;

  int expected_result = s21_create_matrix(3, 3, &result2);
  result2.matrix[0][0] = 1;
  result2.matrix[0][1] = -1;
  result2.matrix[0][2] = 1;
  result2.matrix[1][0] = -38;
  result2.matrix[1][1] = 41;
  result2.matrix[1][2] = -34;
  result2.matrix[2][0] = 27;
  result2.matrix[2][1] = -29;
  result2.matrix[2][2] = 24;
  int actual_result = s21_inverse_matrix(&result1, &result3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(result2.matrix[i][j], result3.matrix[i][j], 1e-6);
    }
  }
  ck_assert_uint_eq(expected_result, actual_result);
  s21_remove_matrix(&result3);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&result1);
}
END_TEST

START_TEST(test_s21_inverse_matrix_9) {
  matrix_t result1;
  matrix_t result3;
  s21_create_matrix(3, 3, &result1);
  result1.matrix[0][0] = 1;
  result1.matrix[0][1] = 2;
  result1.matrix[0][2] = 3;

  result1.matrix[1][0] = 4;
  result1.matrix[1][1] = 5;
  result1.matrix[1][2] = 6;

  result1.matrix[2][0] = 7;
  result1.matrix[2][1] = 8;
  result1.matrix[2][2] = 9;
  int expected_result = 2;
  int actual_result = s21_inverse_matrix(&result1, &result3);
  ck_assert_uint_eq(expected_result, actual_result);

  s21_remove_matrix(&result1);
}
END_TEST

START_TEST(test_s21_inverse_matrix_10) {
  matrix_t A, result, check;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &check);
  A.matrix[0][0] = 1.;
  A.matrix[0][1] = -1.;
  A.matrix[0][2] = 1.;
  A.matrix[1][0] = -38.;
  A.matrix[1][1] = 41.;
  A.matrix[1][2] = -34.;
  A.matrix[2][0] = 27.;
  A.matrix[2][1] = -29.;
  A.matrix[2][2] = 24.;

  check.matrix[0][0] = 2.;
  check.matrix[0][1] = 5.;
  check.matrix[0][2] = 7.;
  check.matrix[1][0] = 6.;
  check.matrix[1][1] = 3.;
  check.matrix[1][2] = 4.;
  check.matrix[2][0] = 5.;
  check.matrix[2][1] = -2.;
  check.matrix[2][2] = -3.;

  s21_inverse_matrix(&A, &result);
  int res = s21_eq_matrix(&result, &check);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_s21_inverse_matrix_11) {
  matrix_t A, B, C;
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &C);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 4;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[1][3] = 1;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  A.matrix[2][3] = 3;
  A.matrix[3][0] = 3;
  A.matrix[3][1] = 7;
  A.matrix[3][2] = 2;
  A.matrix[3][3] = 4;
  s21_inverse_matrix(&A, &B);
  C.matrix[0][0] = -0.125;
  C.matrix[0][1] = 0.19166666;
  C.matrix[0][2] = 0.325;
  C.matrix[0][3] = -0.16666666;
  C.matrix[1][0] = -0.125;
  C.matrix[1][1] = 0.05833333;
  C.matrix[1][2] = -0.075;
  C.matrix[1][3] = 0.16666666;
  C.matrix[2][0] = 0.125;
  C.matrix[2][1] = 0.675;
  C.matrix[2][2] = 0.275;
  C.matrix[2][3] = -0.5;
  C.matrix[3][0] = 0.25;
  C.matrix[3][1] = -0.58333333;
  C.matrix[3][2] = -0.25;
  C.matrix[3][3] = 0.33333333;
  ck_assert_int_eq(s21_eq_matrix(&B, &C), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_s21_inverse_matrix_12) {
  matrix_t A, B;
  s21_create_matrix(3, 4, &A);
  ck_assert_int_eq(s21_inverse_matrix(&A, &B), 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_inverse_matrix_13) {
  matrix_t A, result = {0};
  s21_create_matrix(1, 2, &A);
  A.matrix[0][0] = 777;
  A.matrix[0][1] = 777;
  int check = s21_inverse_matrix(&A, &result);
  int check_origin = 2;
  ck_assert_uint_eq(check, check_origin);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite *s21_matrix_suite() {
  Suite *s = suite_create("s21_matrix_test");

  TCase *tc_s21_create_matrix_1 = tcase_create("test_s21_create_matrix_1");
  suite_add_tcase(s, tc_s21_create_matrix_1);
  tcase_add_test(tc_s21_create_matrix_1, test_s21_create_matrix_1);

  TCase *tc_s21_create_matrix_2 = tcase_create("test_s21_create_matrix_2");
  suite_add_tcase(s, tc_s21_create_matrix_2);
  tcase_add_test(tc_s21_create_matrix_2, test_s21_create_matrix_2);

  TCase *tc_s21_create_matrix_3 = tcase_create("test_s21_create_matrix_3");
  suite_add_tcase(s, tc_s21_create_matrix_3);
  tcase_add_test(tc_s21_create_matrix_3, test_s21_create_matrix_3);

  TCase *tc_s21_create_matrix_4 = tcase_create("test_s21_create_matrix_4");
  suite_add_tcase(s, tc_s21_create_matrix_4);
  tcase_add_test(tc_s21_create_matrix_4, test_s21_create_matrix_4);

  TCase *tc_s21_create_matrix_5 = tcase_create("test_s21_create_matrix_5");
  suite_add_tcase(s, tc_s21_create_matrix_5);
  tcase_add_test(tc_s21_create_matrix_5, test_s21_create_matrix_5);

  TCase *tc_s21_create_matrix_6 = tcase_create("test_s21_create_matrix_6");
  suite_add_tcase(s, tc_s21_create_matrix_6);
  tcase_add_test(tc_s21_create_matrix_6, test_s21_create_matrix_6);

  TCase *tc_s21_create_matrix_7 = tcase_create("test_s21_create_matrix_7");
  suite_add_tcase(s, tc_s21_create_matrix_7);
  tcase_add_test(tc_s21_create_matrix_7, test_s21_create_matrix_7);

  TCase *tc_s21_create_matrix_8 = tcase_create("test_s21_create_matrix_8");
  suite_add_tcase(s, tc_s21_create_matrix_8);
  tcase_add_test(tc_s21_create_matrix_8, test_s21_create_matrix_8);

  TCase *tc_s21_create_matrix_9 = tcase_create("test_s21_create_matrix_9");
  suite_add_tcase(s, tc_s21_create_matrix_9);
  tcase_add_test(tc_s21_create_matrix_9, test_s21_create_matrix_9);

  TCase *tc_s21_create_matrix_10 = tcase_create("test_s21_create_matrix_10");
  suite_add_tcase(s, tc_s21_create_matrix_10);
  tcase_add_test(tc_s21_create_matrix_10, test_s21_create_matrix_10);

  TCase *tc_s21_create_matrix_11 = tcase_create("test_s21_create_matrix_11");
  suite_add_tcase(s, tc_s21_create_matrix_11);
  tcase_add_test(tc_s21_create_matrix_11, test_s21_create_matrix_11);

  TCase *tc_s21_create_matrix_12 = tcase_create("test_s21_create_matrix_12");
  suite_add_tcase(s, tc_s21_create_matrix_12);
  tcase_add_test(tc_s21_create_matrix_12, test_s21_create_matrix_12);

  TCase *tc_s21_create_matrix_13 = tcase_create("test_s21_create_matrix_13");
  suite_add_tcase(s, tc_s21_create_matrix_13);
  tcase_add_test(tc_s21_create_matrix_13, test_s21_create_matrix_13);

  TCase *tc_s21_create_matrix_14 = tcase_create("test_s21_create_matrix_14");
  suite_add_tcase(s, tc_s21_create_matrix_14);
  tcase_add_test(tc_s21_create_matrix_14, test_s21_create_matrix_14);

  TCase *tc_s21_remove_matrix_1 = tcase_create("test_s21_remove_matrix_1");
  suite_add_tcase(s, tc_s21_remove_matrix_1);
  tcase_add_test(tc_s21_remove_matrix_1, test_s21_remove_matrix_1);

  TCase *tc_s21_remove_matrix_2 = tcase_create("test_s21_remove_matrix_2");
  suite_add_tcase(s, tc_s21_remove_matrix_2);
  tcase_add_test(tc_s21_remove_matrix_2, test_s21_remove_matrix_2);

  TCase *tc_s21_remove_matrix_3 = tcase_create("test_s21_remove_matrix_3");
  suite_add_tcase(s, tc_s21_remove_matrix_3);
  tcase_add_test(tc_s21_remove_matrix_3, test_s21_remove_matrix_3);

  TCase *tc_s21_eq_matrix_1 = tcase_create("test_s21_eq_matrix_1");
  suite_add_tcase(s, tc_s21_eq_matrix_1);
  tcase_add_test(tc_s21_eq_matrix_1, test_s21_eq_matrix_1);

  TCase *tc_s21_eq_matrix_2 = tcase_create("test_s21_eq_matrix_2");
  suite_add_tcase(s, tc_s21_eq_matrix_2);
  tcase_add_test(tc_s21_eq_matrix_2, test_s21_eq_matrix_2);

  TCase *tc_s21_eq_matrix_3 = tcase_create("test_s21_eq_matrix_3");
  suite_add_tcase(s, tc_s21_eq_matrix_3);
  tcase_add_test(tc_s21_eq_matrix_3, test_s21_eq_matrix_3);

  TCase *tc_s21_eq_matrix_4 = tcase_create("test_s21_eq_matrix_4");
  suite_add_tcase(s, tc_s21_eq_matrix_4);
  tcase_add_test(tc_s21_eq_matrix_4, test_s21_eq_matrix_4);

  TCase *tc_s21_sum_matrix_1 = tcase_create("test_s21_sum_matrix_1");
  suite_add_tcase(s, tc_s21_sum_matrix_1);
  tcase_add_test(tc_s21_sum_matrix_1, test_s21_sum_matrix_1);

  TCase *tc_s21_sum_matrix_2 = tcase_create("test_s21_sum_matrix_2");
  suite_add_tcase(s, tc_s21_sum_matrix_2);
  tcase_add_test(tc_s21_sum_matrix_2, test_s21_sum_matrix_2);

  TCase *tc_s21_sum_matrix_3 = tcase_create("test_s21_sum_matrix_2");
  suite_add_tcase(s, tc_s21_sum_matrix_3);
  tcase_add_test(tc_s21_sum_matrix_3, test_s21_sum_matrix_3);

  TCase *tc_s21_sub_matrix_1 = tcase_create("test_s21_sub_matrix_1");
  suite_add_tcase(s, tc_s21_sub_matrix_1);
  tcase_add_test(tc_s21_sub_matrix_1, test_s21_sub_matrix_1);

  TCase *tc_s21_sub_matrix_2 = tcase_create("test_s21_sub_matrix_2");
  suite_add_tcase(s, tc_s21_sub_matrix_2);
  tcase_add_test(tc_s21_sub_matrix_2, test_s21_sub_matrix_2);

  TCase *tc_s21_sub_matrix_3 = tcase_create("test_s21_sub_matrix_3");
  suite_add_tcase(s, tc_s21_sub_matrix_3);
  tcase_add_test(tc_s21_sub_matrix_3, test_s21_sub_matrix_3);

  TCase *tc_s21_sub_matrix_4 = tcase_create("test_s21_sub_matrix_4");
  suite_add_tcase(s, tc_s21_sub_matrix_4);
  tcase_add_test(tc_s21_sub_matrix_4, test_s21_sub_matrix_4);

  TCase *tc_s21_mult_number = tcase_create("test_s21_mult_number");
  suite_add_tcase(s, tc_s21_mult_number);
  tcase_add_test(tc_s21_mult_number, test_s21_mult_number);

  TCase *tc_s21_mult_matrix_1 = tcase_create("test_s21_mult_matrix_1");
  suite_add_tcase(s, tc_s21_mult_matrix_1);
  tcase_add_test(tc_s21_mult_matrix_1, test_s21_mult_matrix_1);

  TCase *tc_s21_mult_matrix_2 = tcase_create("test_s21_mult_matrix_2");
  suite_add_tcase(s, tc_s21_mult_matrix_2);
  tcase_add_test(tc_s21_mult_matrix_2, test_s21_mult_matrix_2);

  TCase *tc_s21_mult_matrix_3 = tcase_create("test_s21_mult_matrix_3");
  suite_add_tcase(s, tc_s21_mult_matrix_3);
  tcase_add_test(tc_s21_mult_matrix_3, test_s21_mult_matrix_3);

  TCase *tc_s21_mult_matrix_4 = tcase_create("test_s21_mult_matrix_4");
  suite_add_tcase(s, tc_s21_mult_matrix_4);
  tcase_add_test(tc_s21_mult_matrix_4, test_s21_mult_matrix_4);

  TCase *tc_s21_mult_matrix_5 = tcase_create("test_s21_mult_matrix_2");
  suite_add_tcase(s, tc_s21_mult_matrix_5);
  tcase_add_test(tc_s21_mult_matrix_5, test_s21_mult_matrix_5);

  TCase *tc_s21_mult_matrix_6 = tcase_create("test_s21_mult_matrix_6");
  suite_add_tcase(s, tc_s21_mult_matrix_6);
  tcase_add_test(tc_s21_mult_matrix_6, test_s21_mult_matrix_6);

  TCase *tc_s21_mult_matrix_7 = tcase_create("test_s21_mult_matrix_7");
  suite_add_tcase(s, tc_s21_mult_matrix_7);
  tcase_add_test(tc_s21_mult_matrix_7, test_s21_mult_matrix_7);

  TCase *tc_s21_mult_matrix_8 = tcase_create("test_s21_mult_matrix_8");
  suite_add_tcase(s, tc_s21_mult_matrix_8);
  tcase_add_test(tc_s21_mult_matrix_8, test_s21_mult_matrix_8);

  TCase *tc_s21_mult_matrix_9 = tcase_create("test_s21_mult_matrix_9");
  suite_add_tcase(s, tc_s21_mult_matrix_9);
  tcase_add_test(tc_s21_mult_matrix_9, test_s21_mult_matrix_9);

  TCase *tc_s21_mult_matrix_10 = tcase_create("test_s21_mult_matrix_10");
  suite_add_tcase(s, tc_s21_mult_matrix_10);
  tcase_add_test(tc_s21_mult_matrix_10, test_s21_mult_matrix_10);

  TCase *tc_s21_mult_matrix_11 = tcase_create("test_s21_mult_matrix_11");
  suite_add_tcase(s, tc_s21_mult_matrix_11);
  tcase_add_test(tc_s21_mult_matrix_11, test_s21_mult_matrix_11);

  TCase *tc_s21_mult_matrix_12 = tcase_create("test_s21_mult_matrix_12");
  suite_add_tcase(s, tc_s21_mult_matrix_12);
  tcase_add_test(tc_s21_mult_matrix_12, test_s21_mult_matrix_12);

  TCase *tc_s21_transpose_0 = tcase_create("test_s21_transpose_0");
  suite_add_tcase(s, tc_s21_transpose_0);
  tcase_add_test(tc_s21_transpose_0, test_s21_transpose_0);

  TCase *tc_s21_transpose_1 = tcase_create("test_s21_transpose_1");
  suite_add_tcase(s, tc_s21_transpose_1);
  tcase_add_test(tc_s21_transpose_1, test_s21_transpose_1);

  TCase *tc_s21_transpose_2 = tcase_create("test_s21_transpose_2");
  suite_add_tcase(s, tc_s21_transpose_2);
  tcase_add_test(tc_s21_transpose_2, test_s21_transpose_2);

  TCase *tc_s21_transpose_3 = tcase_create("test_s21_transpose_3");
  suite_add_tcase(s, tc_s21_transpose_3);
  tcase_add_test(tc_s21_transpose_3, test_s21_transpose_3);

  TCase *tc_s21_determinant_0 = tcase_create("test_s21_determinant_0");
  suite_add_tcase(s, tc_s21_determinant_0);
  tcase_add_test(tc_s21_determinant_0, test_s21_determinant_0);

  TCase *tc_s21_determinant_1 = tcase_create("test_s21_determinant_1");
  suite_add_tcase(s, tc_s21_determinant_1);
  tcase_add_test(tc_s21_determinant_1, test_s21_determinant_1);

  TCase *tc_s21_determinant_2 = tcase_create("test_s21_determinant_2");
  suite_add_tcase(s, tc_s21_determinant_2);
  tcase_add_test(tc_s21_determinant_2, test_s21_determinant_2);

  TCase *tc_s21_determinant_3 = tcase_create("test_s21_determinant_3");
  suite_add_tcase(s, tc_s21_determinant_3);
  tcase_add_test(tc_s21_determinant_3, test_s21_determinant_3);

  TCase *tc_s21_determinant_4 = tcase_create("test_s21_determinant_4");
  suite_add_tcase(s, tc_s21_determinant_4);
  tcase_add_test(tc_s21_determinant_4, test_s21_determinant_4);

  TCase *tc_s21_determinant_5 = tcase_create("test_s21_determinant_5");
  suite_add_tcase(s, tc_s21_determinant_5);
  tcase_add_test(tc_s21_determinant_5, test_s21_determinant_5);

  TCase *tc_s21_determinant_6 = tcase_create("test_s21_determinant_6");
  suite_add_tcase(s, tc_s21_determinant_6);
  tcase_add_test(tc_s21_determinant_6, test_s21_determinant_6);

  TCase *tc_s21_determinant_7 = tcase_create("test_s21_determinant_7");
  suite_add_tcase(s, tc_s21_determinant_7);
  tcase_add_test(tc_s21_determinant_7, test_s21_determinant_7);

  TCase *tc_s21_determinant_8 = tcase_create("test_s21_determinant_8");
  suite_add_tcase(s, tc_s21_determinant_8);
  tcase_add_test(tc_s21_determinant_8, test_s21_determinant_8);

  TCase *tc_s21_determinant_9 = tcase_create("test_s21_determinant_9");
  suite_add_tcase(s, tc_s21_determinant_9);
  tcase_add_test(tc_s21_determinant_9, test_s21_determinant_9);

  TCase *tc_s21_determinant_10 = tcase_create("test_s21_determinant_10");
  suite_add_tcase(s, tc_s21_determinant_10);
  tcase_add_test(tc_s21_determinant_10, test_s21_determinant_10);

  TCase *tc_s21_determinant_11 = tcase_create("test_s21_determinant_11");
  suite_add_tcase(s, tc_s21_determinant_11);
  tcase_add_test(tc_s21_determinant_11, test_s21_determinant_11);

  TCase *tc_s21_determinant_12 = tcase_create("test_s21_determinant_12");
  suite_add_tcase(s, tc_s21_determinant_12);
  tcase_add_test(tc_s21_determinant_12, test_s21_determinant_12);

  TCase *tc_s21_determinant_13 = tcase_create("test_s21_determinant_13");
  suite_add_tcase(s, tc_s21_determinant_13);
  tcase_add_test(tc_s21_determinant_13, test_s21_determinant_13);

  TCase *tc_s21_determinant_14 = tcase_create("test_s21_determinant_14");
  suite_add_tcase(s, tc_s21_determinant_14);
  tcase_add_test(tc_s21_determinant_14, test_s21_determinant_14);

  TCase *tc_s21_determinant_15 = tcase_create("test_s21_determinant_15");
  suite_add_tcase(s, tc_s21_determinant_15);
  tcase_add_test(tc_s21_determinant_15, test_s21_determinant_15);

  TCase *tc_s21_determinant_16 = tcase_create("test_s21_determinant_16");
  suite_add_tcase(s, tc_s21_determinant_16);
  tcase_add_test(tc_s21_determinant_16, test_s21_determinant_16);

  TCase *tc_s21_determinant_17 = tcase_create("test_s21_determinant_17");
  suite_add_tcase(s, tc_s21_determinant_17);
  tcase_add_test(tc_s21_determinant_17, test_s21_determinant_17);

  TCase *tc_s21_calc_complements = tcase_create("test_s21_calc_complements");
  suite_add_tcase(s, tc_s21_calc_complements);
  tcase_add_test(tc_s21_calc_complements, test_s21_calc_complements);

  TCase *tc_s21_calc_complements_1 =
      tcase_create("test_s21_calc_complements_1");
  suite_add_tcase(s, tc_s21_calc_complements_1);
  tcase_add_test(tc_s21_calc_complements_1, test_s21_calc_complements_1);

  TCase *tc_s21_calc_complements_2 =
      tcase_create("test_s21_calc_complements_2");
  suite_add_tcase(s, tc_s21_calc_complements_2);
  tcase_add_test(tc_s21_calc_complements_2, test_s21_calc_complements_2);

  TCase *tc_s21_calc_complements_3 =
      tcase_create("test_s21_calc_complements_3");
  suite_add_tcase(s, tc_s21_calc_complements_3);
  tcase_add_test(tc_s21_calc_complements_3, test_s21_calc_complements_3);

  TCase *tc_s21_calc_complements_4 =
      tcase_create("test_s21_calc_complements_4");
  suite_add_tcase(s, tc_s21_calc_complements_4);
  tcase_add_test(tc_s21_calc_complements_4, test_s21_calc_complements_4);

  TCase *tc_s21_calc_complements_5 =
      tcase_create("test_s21_calc_complements_5");
  suite_add_tcase(s, tc_s21_calc_complements_5);
  tcase_add_test(tc_s21_calc_complements_5, test_s21_calc_complements_5);

  TCase *tc_s21_calc_complements_6 =
      tcase_create("test_s21_calc_complements_6");
  suite_add_tcase(s, tc_s21_calc_complements_6);
  tcase_add_test(tc_s21_calc_complements_6, test_s21_calc_complements_6);

  TCase *tc_s21_calc_complements_7 =
      tcase_create("test_s21_calc_complements_7");
  suite_add_tcase(s, tc_s21_calc_complements_7);
  tcase_add_test(tc_s21_calc_complements_7, test_s21_calc_complements_7);

  TCase *tc_s21_calc_complements_8 =
      tcase_create("test_s21_calc_complements_8");
  suite_add_tcase(s, tc_s21_calc_complements_8);
  tcase_add_test(tc_s21_calc_complements_8, test_s21_calc_complements_8);

  TCase *tc_s21_calc_complements_9 =
      tcase_create("test_s21_calc_complements_9");
  suite_add_tcase(s, tc_s21_calc_complements_9);
  tcase_add_test(tc_s21_calc_complements_9, test_s21_calc_complements_9);

  TCase *tc_s21_calc_complements_10 =
      tcase_create("test_s21_calc_complements_10");
  suite_add_tcase(s, tc_s21_calc_complements_10);
  tcase_add_test(tc_s21_calc_complements_10, test_s21_calc_complements_10);

  TCase *tc_s21_calc_complements_11 =
      tcase_create("test_s21_calc_complements_11");
  suite_add_tcase(s, tc_s21_calc_complements_11);
  tcase_add_test(tc_s21_calc_complements_11, test_s21_calc_complements_11);

  TCase *tc_s21_inverse_matrix_0 = tcase_create("test_s21_inverse_matrix_0");
  suite_add_tcase(s, tc_s21_inverse_matrix_0);
  tcase_add_test(tc_s21_inverse_matrix_0, test_s21_inverse_matrix_0);

  TCase *tc_s21_inverse_matrix_1 = tcase_create("test_s21_inverse_matrix_1");
  suite_add_tcase(s, tc_s21_inverse_matrix_1);
  tcase_add_test(tc_s21_inverse_matrix_1, test_s21_inverse_matrix_1);

  TCase *tc_s21_inverse_matrix_2 = tcase_create("test_s21_inverse_matrix_2");
  suite_add_tcase(s, tc_s21_inverse_matrix_2);
  tcase_add_test(tc_s21_inverse_matrix_2, test_s21_inverse_matrix_2);

  TCase *tc_s21_inverse_matrix_3 = tcase_create("test_s21_inverse_matrix_3");
  suite_add_tcase(s, tc_s21_inverse_matrix_3);
  tcase_add_test(tc_s21_inverse_matrix_3, test_s21_inverse_matrix_3);

  TCase *tc_s21_inverse_matrix_4 = tcase_create("test_s21_inverse_matrix_4");
  suite_add_tcase(s, tc_s21_inverse_matrix_4);
  tcase_add_test(tc_s21_inverse_matrix_4, test_s21_inverse_matrix_4);

  TCase *tc_s21_inverse_matrix_5 = tcase_create("test_s21_inverse_matrix_5");
  suite_add_tcase(s, tc_s21_inverse_matrix_5);
  tcase_add_test(tc_s21_inverse_matrix_5, test_s21_inverse_matrix_5);

  TCase *tc_s21_inverse_matrix_6 = tcase_create("test_s21_inverse_matrix_6");
  suite_add_tcase(s, tc_s21_inverse_matrix_6);
  tcase_add_test(tc_s21_inverse_matrix_6, test_s21_inverse_matrix_6);

  TCase *tc_s21_inverse_matrix_7 = tcase_create("test_s21_inverse_matrix_7");
  suite_add_tcase(s, tc_s21_inverse_matrix_7);
  tcase_add_test(tc_s21_inverse_matrix_7, test_s21_inverse_matrix_7);

  TCase *tc_s21_inverse_matrix_8 = tcase_create("test_s21_inverse_matrix_8");
  suite_add_tcase(s, tc_s21_inverse_matrix_8);
  tcase_add_test(tc_s21_inverse_matrix_8, test_s21_inverse_matrix_8);

  TCase *tc_s21_inverse_matrix_9 = tcase_create("test_s21_inverse_matrix_9");
  suite_add_tcase(s, tc_s21_inverse_matrix_9);
  tcase_add_test(tc_s21_inverse_matrix_9, test_s21_inverse_matrix_9);

  TCase *tc_s21_inverse_matrix_10 = tcase_create("test_s21_inverse_matrix_10");
  suite_add_tcase(s, tc_s21_inverse_matrix_10);
  tcase_add_test(tc_s21_inverse_matrix_10, test_s21_inverse_matrix_10);

  TCase *tc_s21_inverse_matrix_11 = tcase_create("test_s21_inverse_matrix_11");
  suite_add_tcase(s, tc_s21_inverse_matrix_11);
  tcase_add_test(tc_s21_inverse_matrix_11, test_s21_inverse_matrix_11);

  TCase *tc_s21_inverse_matrix_12 = tcase_create("test_s21_inverse_matrix_12");
  suite_add_tcase(s, tc_s21_inverse_matrix_12);
  tcase_add_test(tc_s21_inverse_matrix_12, test_s21_inverse_matrix_12);

  TCase *tc_s21_inverse_matrix_13 = tcase_create("test_s21_inverse_matrix_13");
  suite_add_tcase(s, tc_s21_inverse_matrix_13);
  tcase_add_test(tc_s21_inverse_matrix_13, test_s21_inverse_matrix_13);

  return s;
}

int main() {
  int no_failed = 0;

  Suite *s = s21_matrix_suite();

  SRunner *runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
