/*******************************
 * Naive Recursive Merge Sort
 * ****************************/

#include <ctime>
#include <cstdlib>
#include <iostream>

typedef long long int llint_;

/****************************************************************************
 * ARRAY_SIZE controls the size of the array, i.e 'n'.
 * NUM_AVARAGE is the number of executions after which avarage is calculated.
 * INTEGER_SIZE controls the size of individual elements.
 * Set BENCHMARKING true to get execution time related information.
 ****************************************************************************/

#define ARRAY_SIZE      int (1e2)
#define NUM_AVARAGE     int (1e3)
#define INTEGER_SIZE    int (1e2)
#define BENCHMARKING    false

void merge_arrays (llint_ array[], int l, int r)
{
    int mid     = l / 2 + r / 2;
    int l_size  = mid - l + 1;
    int r_size  = r - mid;
    int i = 0, j = 0;
    llint_ left_arr [l_size];
    llint_ right_arr [r_size];

    for (i = 0; i < l_size;  i ++) {

        left_arr [i] = array [l + i];

    }

    for (i = 0; i < r_size;  i ++) {

        right_arr [i] = array [i + mid + 1];

    }

    i = 0, j = 0;
    while (i < l_size && j < r_size) {

        if (left_arr [i] < right_arr [j]) {

            array [l + i + j] = left_arr [i];
            i++;

        }
        else {

            array [l + i + j] = right_arr [j];
            j++;

        }
    }

    while (i < l_size) {
        array [l + i + j] = left_arr [i];
        i++;
    }

    while (j < r_size) {
        array [l + i + j] = right_arr [j];
        j++;
    }
}

void merge_sort (llint_ array[], int l, int r)
{
    if (l >= r)
        return;
    else {

    int mid = (l / 2) + (r / 2);

    merge_sort (array, l, mid);

    merge_sort (array, mid + 1, r);

    merge_arrays (array, l, r);
    }
}


void generate_array(llint_ * array, int array_len)
{

    std::srand (std::time (NULL));

    for (int i = 0; i < array_len; i++){
        array[i] = (std::rand() % INTEGER_SIZE);
    }

}

void print_array (llint_ * array, int size)
/* Simply prints the array, due to large size print them in column */
{

    for (int i = 0; i < size; i++){

        std::cout <<  array [i]  << '\n';

    }
    std::cout << std::endl;
}

int main()
{

    llint_ array[ARRAY_SIZE];
    generate_array (array, ARRAY_SIZE);
    print_array (array, ARRAY_SIZE);

    merge_sort (array, 0, ARRAY_SIZE - 1);

    print_array (array, ARRAY_SIZE);

}
