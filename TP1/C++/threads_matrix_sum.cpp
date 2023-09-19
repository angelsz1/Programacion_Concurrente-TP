#include <iostream>
#include <cstdlib> //rand
#include <iomanip> //setw
#include <thread>
#include "threads_matrix_sum.h"

int main()
{
    short matrix_A[MATRIX_ROW_SIZE][MATRIX_COLUMN_SIZE];
    short matrix_B[MATRIX_ROW_SIZE][MATRIX_COLUMN_SIZE];
    short matrix_SC[MATRIX_ROW_SIZE][MATRIX_COLUMN_SIZE];
    short matrix_CC[MATRIX_ROW_SIZE][MATRIX_COLUMN_SIZE];

    fill_array_with_random_numbers(&matrix_A[0][0], MATRIX_ROW_SIZE * MATRIX_COLUMN_SIZE);
    fill_array_with_random_numbers(&matrix_B[0][0], MATRIX_ROW_SIZE * MATRIX_COLUMN_SIZE);

    std::cout << std::endl << "--------------A--------------" << std::endl;
    show_matrix(&matrix_A[0][0], MATRIX_ROW_SIZE, MATRIX_COLUMN_SIZE);

    std::cout << std::endl << "--------------B--------------" << std::endl;
    show_matrix(&matrix_B[0][0], MATRIX_ROW_SIZE, MATRIX_COLUMN_SIZE);

    std::cout << std::endl << "--------------SC--------------" << std::endl;
    sum_matrix_sequentially(&matrix_A[0][0], &matrix_B[0][0], &matrix_SC[0][0], MATRIX_ROW_SIZE, MATRIX_COLUMN_SIZE);
    show_matrix(&matrix_SC[0][0], MATRIX_ROW_SIZE, MATRIX_COLUMN_SIZE);

    std::cout << std::endl << "--------------CC--------------" << std::endl;
    sum_matrix_concurrently(&matrix_A[0][0], &matrix_B[0][0], &matrix_CC[0][0], MATRIX_ROW_SIZE, MATRIX_COLUMN_SIZE);
    show_matrix(&matrix_CC[0][0], MATRIX_ROW_SIZE, MATRIX_COLUMN_SIZE);

    bool is_same_res = compare_matrix(&matrix_SC[0][0], &matrix_CC[0][0], MATRIX_ROW_SIZE, MATRIX_COLUMN_SIZE);
    std::cout << (is_same_res ? "Son iguales" : "No son iguales") << std::endl;

    return EXIT_SUCCESS;
}

void fill_array_with_random_numbers(short *array, short count)
{
    for (short i = 0; i < count; i++)
    {
        *array = get_random_number(MIN_VALUE_RANDOM, MAX_VALUE_RANDOM);
        array++;
    }
}

short get_random_number(short min_value, short max_value)
{
    return rand() % (max_value - min_value + 1) + min_value;
}

void sum_matrix_sequentially(const short *m1, const short *m2, short *m_res, short row_size, short column_size)
{
    short count = row_size * column_size;
    sum_array(m1, m2, m_res, count);
}

void sum_matrix_concurrently(const short *m1, const short *m2, short *m_res, short row_size, short column_size)
{
    short threads_quantity = row_size;
    std::thread threads[threads_quantity];
    short *p1 = (short *)m1;
    short *p2 = (short *)m2;

    for (short i = 0; i < threads_quantity; i++)
    {
        short *row_array_1 = p1 + (column_size * i);
        short *row_array_2 = p2 + (column_size * i);
        short *row_array_res = m_res + (column_size * i);
        threads[i] = std::thread(sum_array, row_array_1, row_array_2, row_array_res, column_size);
    }

    for (short j = 0; j < threads_quantity; j++)
    {
        threads[j].join();
    }
}

void sum_array(const short *a1, const short *a2, short *a_res, short count)
{
    for (short i = 0; i < count; i++)
    {
        *a_res = *a1 + *a2;
        a_res++;
        a1++;
        a2++;
    }
}

bool compare_matrix(const short *m1, const short *m2, short row_size, short column_size)
{
    short count = row_size * column_size;
    bool is_equal = true;
    short i = row_size * column_size;

    while (is_equal && i > 0)
    {
        if (*m1 != *m2)
        {
            is_equal = false;
        }
        m1++;
        m2++;
        i--;
    }
    return is_equal;
}

void show_matrix(const short *matrix, short row_size, short column_size)
{
    for (short r = 0; r < row_size; r++)
    {
        for (short c = 0; c < column_size; c++)
        {
            std::cout << std::setw(5) << *matrix;
            matrix++;
        }
        std::cout << std::endl;
    }
}