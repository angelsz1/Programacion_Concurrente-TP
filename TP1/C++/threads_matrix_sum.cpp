#include <iostream>
#include <cstdlib> //rand
#include <iomanip> //setw %d
#include <thread>

#define MATRIX_COLUMN_SIZE 5
#define MATRIX_ROW_SIZE 5
#define MIN_VALUE_RANDOM -32
#define MAX_VALUE_RANDOM 32

bool compare_matrix(short* m1, short* m2, short row_size, short column_size)
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

void sum_array(short* a1, short* a2, short* a_res, short count)
{
    for (short i = 0; i < count; i++)
    {
        *a_res = *a1 + *a2;
        a_res++;
        a1++;
        a2++;
    }
}

void sum_matrix_concurrently(short * m1, short* m2, short*m_res, short row_size, short column_size)
{
    short threads_quantity = row_size;
    std::thread threads[threads_quantity];

    for (short i = 0; i < threads_quantity; i++)
    {
        short * row_array_1 = m1 + (column_size * i); 
        short * row_array_2 = m2 + (column_size * i); 
        short * row_array_res = m_res + (column_size * i);
        threads[i] = std::thread(sum_array, row_array_1, row_array_2, row_array_res, column_size);
    }

    for (short j = 0; j < threads_quantity; j++)
    {
        threads[j].join();
    }
}

void sum_matrix_sequentially(short * m1, short* m2, short*m_res, short row_size, short column_size)
{
    short count = row_size * column_size;
    sum_array(m1, m2, m_res, count);
}

short get_random_number(short min_value, short max_value)
{
    return rand() % (max_value - min_value + 1) + min_value;
}

void fill_array_with_random_numbers(short* array, short count)
{
    for (short i = 0; i < count; i++)
    {
        *array = get_random_number(MIN_VALUE_RANDOM, MAX_VALUE_RANDOM);
        array++;
    }
}

void show_matrix(short * matrix,short row_size, short column_size )
{
    for (short r = 0; r < row_size; r++)
    {
        for (short c = 0; c < column_size; c++)
        {
            std::cout<< std::setw(5) << *matrix;
            matrix++;           
        }
        std::cout<<std::endl;
    }
}

int main() {
    short matrix_A[MATRIX_ROW_SIZE][MATRIX_COLUMN_SIZE];
    short matrix_B[MATRIX_ROW_SIZE][MATRIX_COLUMN_SIZE];
    short matrix_SC[MATRIX_ROW_SIZE][MATRIX_COLUMN_SIZE];
    short matrix_CC[MATRIX_ROW_SIZE][MATRIX_COLUMN_SIZE];

    fill_array_with_random_numbers(&matrix_A[0][0], MATRIX_ROW_SIZE * MATRIX_COLUMN_SIZE);
    fill_array_with_random_numbers(&matrix_B[0][0], MATRIX_ROW_SIZE * MATRIX_COLUMN_SIZE);

    std::cout<<std::endl<<"--------------A--------------"<<std::endl;
    show_matrix(&matrix_A[0][0], MATRIX_ROW_SIZE, MATRIX_COLUMN_SIZE);
    
    std::cout<<std::endl<<"--------------B--------------"<<std::endl;
    show_matrix(&matrix_B[0][0], MATRIX_ROW_SIZE, MATRIX_COLUMN_SIZE);
    
    std::cout<<std::endl<<"--------------SC--------------"<<std::endl;
    sum_matrix_sequentially(&matrix_A[0][0], &matrix_B[0][0], &matrix_SC[0][0], MATRIX_ROW_SIZE, MATRIX_COLUMN_SIZE);
    show_matrix(&matrix_SC[0][0], MATRIX_ROW_SIZE, MATRIX_COLUMN_SIZE);
    
    std::cout<<std::endl<<"--------------CC--------------"<<std::endl;
    sum_matrix_concurrently(&matrix_A[0][0], &matrix_B[0][0], &matrix_CC[0][0], MATRIX_ROW_SIZE, MATRIX_COLUMN_SIZE);
    show_matrix(&matrix_CC[0][0], MATRIX_ROW_SIZE, MATRIX_COLUMN_SIZE);

    bool is_same_res = compare_matrix(&matrix_SC[0][0], &matrix_CC[0][0], MATRIX_ROW_SIZE, MATRIX_COLUMN_SIZE);
    std::cout<<(is_same_res?"Son iguales": "No son iguales")<<std::endl;

    return EXIT_SUCCESS;
}