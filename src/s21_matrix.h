#ifndef S21_MATRIX_H_
#define S21_MATRIX_H_

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

void output(matrix_t *A);
int swap_str(matrix_t *A, int str1, int columns);
void determinant_main_loop(matrix_t *A, double *result);
int threeXthree(matrix_t *A, double *result);
int twoXtwo(matrix_t *A, double *result);
void sum_srt(double factor, int str_main, int str_side, matrix_t *A);
double make_factor(double a_main, double a_side);
int swap_str_no_zero(matrix_t *A);
void doubler(matrix_t *A, matrix_t *result);
int conformity_check(matrix_t *A);
void output(matrix_t *A);
int calc_complements_basic_calculations(matrix_t *A, matrix_t *result);
int calc_complements_one_member(matrix_t *A, matrix_t *result,
                                matrix_t *mat_buf, int i, int j);

#endif  // S21_MATRIX_H_
