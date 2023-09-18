#include <iostream>
#include <cstdlib> //rand
#include <iomanip> //setw %d

#define MATRIX_COLUMN_SIZE 5
#define MATRIX_ROW_SIZE 5
#define MIN_VALUE_RANDOM -32
#define MAX_VALUE_RANDOM 32

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
        std::cout<<std::endl;
        for (short c = 0; c < column_size; c++)
        {
            std::cout<< std::setw(5) << *matrix;
            matrix++;           
        }
        
    }
}

int main() {
    short matrix_A[MATRIX_ROW_SIZE][MATRIX_COLUMN_SIZE];
    fill_array_with_random_numbers(&matrix_A[0][0], MATRIX_ROW_SIZE * MATRIX_COLUMN_SIZE);
    show_matrix(&matrix_A[0][0], MATRIX_ROW_SIZE, MATRIX_COLUMN_SIZE);
    return 0;
}