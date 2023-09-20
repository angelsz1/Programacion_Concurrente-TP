#ifndef FILENAME_H
#define FILENAME_H

#define MATRIX_COLUMN_SIZE 5
#define MATRIX_ROW_SIZE 5
#define MIN_VALUE_RANDOM -32
#define MAX_VALUE_RANDOM 32

void fill_array_with_random_numbers(short *array, short count);
short get_random_number(short min_value, short max_value);

void sum_matrix_sequentially(const short *m1, const short *m2, short *m_res, short row_size, short column_size);
void sum_matrix_concurrently(const short *m1, const short *m2, short *m_res, short row_size, short column_size);
void sum_array(const short *a1, const short *a2, short *a_res, short count);

bool compare_matrix(const short *m1, const short *m2, short row_size, short column_size);
void show_matrix(const short *matrix, short row_size, short column_size);

#endif