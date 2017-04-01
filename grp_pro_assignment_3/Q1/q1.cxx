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


/*********************** Miscelleneous Utility Functions **********************/
/* Function to generate array of random numbers */
void generate_array(llint_ * array, int array_len)
{

    std::srand (std::time (NULL));

    for (int i = 0; i < array_len; i++){
        array[i] = (std::rand() % INTEGER_SIZE);
    }

}

/* Simply prints the array, due to large size print them in column */
void print_array (llint_ * array, int size)
{

    for (int i = 0; i < size; i++){

        std::cout <<  array [i]  << '\n';

    }
    std::cout << std::endl;
}

/* This function copies the generated array into two so that Quick and Merge
 * sort both work on the same array, for better comparision. */
void copy_array (llint_ * array, llint_ * array_copy, int size)
{

    for (int i = 0; i < size; i++) {

        array_copy [i] = array [i];

    }

}
/*****************************************************************************/

/************************** Merge Sort Functions *****************************/
/* Function to merge two individually sorted arrays*/
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

/* Function to sort */
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
/*****************************************************************************/



/************************** Quick Sort Functions *****************************/
/* Functio for placing the pivot at its correct position in the array. */
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

/* Function to sort */
void quick_sort (llint_ array [], int l, int r)
{

    if (l < r) {

        int i = partition (array, l, r);
        print_array (array, ARRAY_SIZE);
        quick_sort (array, l, i - 1);
        quick_sort (array, i + 1, r);

    }
}
/*****************************************************************************/


int main()
{

    llint_ array [ARRAY_SIZE];
    llint_ array_copy [ARRAY_SIZE];
    generate_array (array, ARRAY_SIZE);
    copy_array (array, array_copy, ARRAY_SIZE);
    print_array (array, ARRAY_SIZE);

    merge_sort (array, 0, ARRAY_SIZE - 1);
    quick_sort (array_copy, 0, ARRAY_SIZE -1);

    print_array (array, ARRAY_SIZE);
    print_array (array_copy, ARRAY_SIZE);

}
