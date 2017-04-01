/*******************************
 * Recursive Naive Quick Sort
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

#define ARRAY_SIZE      int (1e1)
#define NUM_AVARAGE     int (1e1)
#define INTEGER_SIZE    int (1e1)
#define BENCHMARKING    false

// This function generates random number array of
void generate_array(llint_ * array, int array_len)
{

    std::srand (std::time (NULL));

    for (int i = 0; i < array_len; i++){
        array[i] = (std::rand() % INTEGER_SIZE);
    }

}

void print_array (llint_ * array, int size)
{

    for (int i = 0; i < size; i++){

        std::cout <<  array [i]  << '\n';

    }
    std::cout << std::endl;
}

int partition (llint_ array [], int l, int r)
{
    llint_ pivot = array [r];
    llint_ temp = 0;
    int i = l, j = l - 1;

    for (; i < r; i++) {

        if (array [i] <= pivot) {

            j++;
            temp = array [i];
            array [i] = array [j];
            array [j] = temp;

        }
    }

        temp = array [j + 1];
        array [j + 1] = pivot;
        array [r] = temp;


    return j + 1;
}

void quick_sort (llint_ array [], int l, int r)
{
    if (l < r) {

        int i = partition (array, l, r);
        print_array (array, ARRAY_SIZE);
        quick_sort (array, l, i - 1);
        quick_sort (array, i + 1, r);

    }
}

int main ()
{

    llint_ array[ARRAY_SIZE];
    generate_array (array, ARRAY_SIZE);
    print_array (array, ARRAY_SIZE);

    quick_sort (array, 0, ARRAY_SIZE - 1);

    print_array (array, ARRAY_SIZE);

}
