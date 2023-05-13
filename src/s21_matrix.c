#include "s21_matrix.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int conformity_check(matrix_t *A) {
  int back = 1;
  if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0) {
    back = 0;
  }
  return back;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int back = 0;
  if (conformity_check(A)) {
    double res = 0;
    s21_determinant(A, &res);
    if ((res != 0) && (A->rows == A->columns)) {
      if (A->rows == 1) {
        s21_create_matrix(A->rows, A->columns, result);
        result->matrix[0][0] = 1 / A->matrix[0][0];
      } else {
        matrix_t minor, buf;
        s21_calc_complements(A, &minor);
        s21_transpose(&minor, &buf);
        s21_remove_matrix(&minor);
        s21_mult_number(&buf, (1.0 / res), result);
        s21_remove_matrix(&buf);
      }
    } else {
      back = 2;
    }
  } else {
    back = 1;
  }
  return back;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int back = 0;
  if (!conformity_check(A) || s21_create_matrix(A->rows, A->columns, result)) {
    back = 1;
  } else if (A->rows != A->columns) {
    back = 2;
  } else if (A->rows <= 1) {
    back = 2;
  } else {
    calc_complements_basic_calculations(A, result);
  }
  return back;
}

int calc_complements_basic_calculations(matrix_t *A, matrix_t *result) {
  matrix_t mat_buf;
  int back = 0;
  s21_create_matrix(A->rows - 1, A->columns - 1, &mat_buf);
  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < A->columns; ++j) {
      back = calc_complements_one_member(A, result, &mat_buf, i, j);
    }
  }
  s21_remove_matrix(&mat_buf);
  return back;
}

int calc_complements_one_member(matrix_t *A, matrix_t *result,
                                matrix_t *mat_buf, int i, int j) {
  int o = 0, p = 0, back = 0;
  for (int k = 0; k < A->rows; ++k) {
    for (int l = 0; l < A->columns; ++l) {
      if ((k != i) && (l != j)) {
        mat_buf->matrix[o][p] = A->matrix[k][l];
        p++;
        if (p == A->columns - 1) {
          p = 0;
          o++;
        }
      }
    }
  }
  double res;
  back = s21_determinant(mat_buf, &res);
  if (res != 0) result->matrix[i][j] = res * pow(-1, i + j + 2);
  return back;
}

int s21_determinant(matrix_t *A, double *result) {
  int back = 0;
  *result = 1;
  if (!conformity_check(A)) {
    back = 1;
  } else if (A->rows != A->columns) {
    back = 2;
  } else if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    twoXtwo(A, result);
  } else {
    determinant_main_loop(A, result);
  }
  return back;
}

void determinant_main_loop(matrix_t *A, double *result) {
  matrix_t mat_buf;
  s21_create_matrix(A->rows, A->columns, &mat_buf);
  doubler(A, &mat_buf);
  int flag_swap = 0;
  if (mat_buf.matrix[0][0] == 0) {
    if (swap_str_no_zero(&mat_buf) == 0) {
      (*result) = 0;
    }
    flag_swap++;
  }
  for (int i = 0; i < mat_buf.columns && (*result) != 0; ++i) {
    for (int j = i + 1; j < mat_buf.rows && (*result) != 0; ++j) {
      if (mat_buf.matrix[j][i] != 0) {
        if (mat_buf.matrix[i][i] != 0) {
          double buf = make_factor(mat_buf.matrix[i][i], mat_buf.matrix[j][i]);
          sum_srt(buf, i, j, &mat_buf);
        } else {
          if (swap_str(&mat_buf, i, i)) {
            flag_swap++;
          } else {
            *result = 0;
          }
        }
      }
    }
  }
  for (int i = 0; i < mat_buf.columns; ++i) (*result) *= mat_buf.matrix[i][i];
  if (flag_swap % 2 == 1) (*result) *= -1;
  s21_remove_matrix(&mat_buf);
}

int swap_str(matrix_t *A, int str1, int columns) {
  int str2 = str1, back = 1;
  for (int i = str2; i < A->rows; ++i) {
    if (A->matrix[i][columns] != 0) {
      str2 = i;
    }
  }
  for (int i = 0; i < A->columns; ++i) {
    double buf = A->matrix[str1][i];
    A->matrix[str1][i] = A->matrix[str2][i];
    A->matrix[str2][i] = buf;
  }
  if (str2 == str1) back = 0;
  return back;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int back = 0;
  if (conformity_check(A) && !s21_create_matrix(A->columns, A->rows, result)) {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  } else {
    back = 1;
  }
  return back;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int back = 0;
  if (!conformity_check(A) || !conformity_check(B) ||
      s21_create_matrix(A->rows, B->columns, result)) {
    back = 1;
  } else if (A->columns != B->rows) {
    back = 2;
  } else {
    for (int i = 0; i < result->rows; ++i) {
      for (int j = 0; j < result->columns; ++j) {
        double buf = 0;
        for (int k = 0; k < A->columns; ++k) {
          buf += A->matrix[i][k] * B->matrix[k][j];
        }
        result->matrix[i][j] = buf;
      }
    }
  }
  return back;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int back = 0;
  if (!conformity_check(A) || s21_create_matrix(A->rows, A->columns, result)) {
    back = 1;
  } else {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return back;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int back = 0;
  if (!conformity_check(A) || !conformity_check(B) ||
      s21_create_matrix(A->rows, A->columns, result)) {
    back = 1;
  } else if ((A->rows != B->rows) || (A->columns != B->columns)) {
    back = 2;
  } else {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return back;
}
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int back = 0;
  if (!conformity_check(A) || !conformity_check(B) ||
      s21_create_matrix(A->rows, A->columns, result)) {
    back = 1;
  } else if ((A->rows != B->rows) || (A->columns != B->columns)) {
    back = 2;
  } else {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return back;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int back = 1;
  if (!conformity_check(A) || !conformity_check(B) || (A->rows != B->rows) ||
      (A->columns != B->columns)) {
    back = 0;
  } else {
    for (int i = 0; (i < A->rows) && (back != 0); ++i) {
      for (int j = 0; (j < A->columns) && (back != 0); ++j) {
        if (fabs(A->matrix[i][j]) - fabs(B->matrix[i][j]) >= 1e-7) {
          back = 0;
        }
      }
    }
  }
  return back;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int back = 0;
  if (result == NULL) {
    back = 1;
  } else if ((rows <= 0) || (columns <= 0)) {
    back = 1;
  } else if ((result->matrix = (double **)malloc(rows * sizeof(double *))) ==
             NULL) {
    back = 1;
  } else {
    for (int i = 0; i < rows; ++i) {
      if ((result->matrix[i] = (double *)malloc(columns * sizeof(double))) ==
          NULL) {
        back = 1;
        break;
      }
    }
    if (!back) {
      for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
          result->matrix[i][j] = 0;
        }
      }
      result->rows = rows;
      result->columns = columns;
    }
  }
  return back;
}

void s21_remove_matrix(matrix_t *A) {
  if (conformity_check(A)) {
    for (int i = 0; i < A->rows; ++i) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

double make_factor(double a_main, double a_side) {
  double back = 0;
  back = -(a_side / a_main);
  return back;
}

void sum_srt(double factor, int str_main, int str_side, matrix_t *A) {
  for (int i = 0; i < A->columns; ++i) {
    A->matrix[str_side][i] += factor * A->matrix[str_main][i];
  }
}

int twoXtwo(matrix_t *A, double *result) {
  int back = 0;
  if ((A->rows == A->columns) && (A->rows == 2)) {
    (*result) =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    back = 1;
  }
  return back;
}

int swap_str_no_zero(matrix_t *A) {
  int work_rows = 0;
  for (int i = 1; i < A->rows; ++i) {
    if ((A->matrix[i][0] != 0) && (A->matrix[i][0] > A->matrix[work_rows][0]))
      work_rows = i;
  }
  for (int i = 0; i < A->columns; ++i) {
    double buf = A->matrix[0][i];
    A->matrix[0][i] = A->matrix[work_rows][i];
    A->matrix[work_rows][i] = buf;
  }
  return work_rows;
}

void doubler(matrix_t *A, matrix_t *result) {
  for (int i = 0; i < A->rows; ++i) {
    for (int j = 0; j < A->columns; ++j) {
      result->matrix[i][j] = A->matrix[i][j];
    }
  }
}
