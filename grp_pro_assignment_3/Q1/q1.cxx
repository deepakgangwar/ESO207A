#include <ctime>
#include <chrono>
#include <cstdlib>
#include <iostream>

typedef long long int llint_;
typedef std::chrono::duration<float> fsec;
typedef std::chrono::high_resolution_clock Time;

/****************************************************************************
 * ARRAY_SIZE controls the size of the array, i.e 'n'.
 * NUM_AVARAGE is the number of executions after which avarage is calculated.
 * INTEGER_SIZE controls the size of individual elements.
 * Set BENCHMARKING true to get execution benchmarking related information.
 ****************************************************************************/

#define ARRAY_SIZE      int (1e2)
#define NUM_AVARAGE     int (1e3)
#define INTEGER_SIZE    int (1e2)
#define BENCHMARKING    true

/* Global variables for the number of comparisons for both the algorithms */
llint_ m_comp = 0;
llint_ q_comp = 0;

/* Globally declared arrays for merge sort to segmentation fault due to memory
 * crunch */
llint_  left_arr [ARRAY_SIZE / 2];
llint_  right_arr [ARRAY_SIZE / 2];

/*********************** Miscelleneous Utility Functions **********************/
/* Function to generate array of random numbers */
void generate_array(llint_ * array, int array_len)
{

    for (int i = 0; i < array_len; i++){
        array[i] = (std::rand() % INTEGER_SIZE);
    }

}

/* Simply prints the array, due to large size prints them in column */
void print_array (llint_ * array, int size)
{

    for (int i = 0; i < size; i++){

        std::cout <<  array [i]  << '\n';

    }
    std::cout << std::endl;
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

    for (i = 0; i < l_size;  i ++) {

        left_arr [i] = array [l + i];

    }

    for (i = 0; i < r_size;  i ++) {

        right_arr [i] = array [i + mid + 1];

    }

    i = 0, j = 0;
    while (i < l_size && j < r_size) {

        if (left_arr [i] < right_arr [j] && ++m_comp) {

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
void merge_sort (llint_ array [], int l, int r)
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

        if (array [i] <= pivot && ++q_comp) {

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
        quick_sort (array, l, i - 1);
        quick_sort (array, i + 1, r);

    }
}
/*****************************************************************************/


int main()
{

    llint_ array [ARRAY_SIZE];

    if (BENCHMARKING) {

        Time::time_point start  = Time::now();
        Time::time_point end    = Time::now();
        fsec q_time = start - end;
        fsec m_time = start - end;

        /* Variables for storing various benchmark values */
        int m_faster = 0;
        int m_comp_t = 0;
        int q_comp_t = 0;
        int m_c_avg  = 0;
        int q_c_avg  = 0;
        int q_5p     = 0;
        int q_10p    = 0;
        int q_20p    = 0;
        int q_30p    = 0;
        int q_40p    = 0;
        int q_50p    = 0;
        int q_100p   = 0;

        /* This array stores the times for each individual iteration for the
         * execution of quick sort. */
        fsec Q_time [NUM_AVARAGE];

        for (int i = 0; i < NUM_AVARAGE; i++) {

            /* The iteration num is used to seed for random number generation */
            std::srand (i + std::time(NULL));
            generate_array (array, ARRAY_SIZE);

            start = Time::now();
            quick_sort (array, 0, ARRAY_SIZE - 1);
            end = Time::now();
            Q_time [i] = end - start;
            q_time += Q_time [i];

            std::srand (i);
            generate_array (array, ARRAY_SIZE);

            start = Time::now();
            merge_sort (array, 0, ARRAY_SIZE - 1);
            end = Time::now();
            m_time += end - start;


            if (m_comp < q_comp)
                m_faster++;

            m_comp_t += m_comp;
            q_comp_t += q_comp;

            if (i % 10 == 0) {
                m_c_avg = m_c_avg / 2 + m_comp_t / 20;
                q_c_avg = q_c_avg / 2 + q_comp_t / 20;
                m_comp_t = 0;
                q_comp_t = 0;
            }
            m_comp = 0;
            q_comp = 0;

        }

        m_time = m_time / NUM_AVARAGE;
        q_time = q_time / NUM_AVARAGE;

//        m_comp_t = m_comp_t / NUM_AVARAGE;
//        q_comp_t = q_comp_t / NUM_AVARAGE;

        for (int i = 0; i < NUM_AVARAGE; i++) {

            if (Q_time [i].count () / q_time.count () <= 1.05)
                q_5p++;
            else if (Q_time [i].count () / q_time.count () <= 1.10)
                q_10p++;
            else if (Q_time [i].count () / q_time.count () <= 1.20)
                q_20p++;
            else if (Q_time [i].count () / q_time.count () <= 1.30)
                q_30p++;
            else if (Q_time [i].count () / q_time.count () <= 1.40)
                q_40p++;
            else if (Q_time [i].count () / q_time.count () <= 1.50)
                q_50p++;
            else if (Q_time [i].count () / q_time.count () <= 2.00)
                q_100p++;
        }

        std::cout << "quick time :" << q_time.count () << std::endl;
        std::cout << "merge time :" << m_time.count () << '\n' << std::endl;

        std::cout << "quick sort comp :" << q_c_avg << std::endl;
        std::cout << "merge sort comp :" << m_c_avg << '\n' << std::endl;

        std::cout << "merge sort faster :" << m_faster << std::endl;
        std::cout << "number of loops :" << NUM_AVARAGE << std::endl;

        std::cout << "exceeds by 5% :" << q_5p << std::endl;
        std::cout << "exceeds by 10% :" << q_10p << std::endl;
        std::cout << "exceeds by 20% :" << q_20p << std::endl;
        std::cout << "exceeds by 30% :" << q_30p << std::endl;
        std::cout << "exceeds by 40% :" << q_40p << std::endl;
        std::cout << "exceeds by 50% :" << q_50p << std::endl;
        std::cout << "exceeds by 100% :" << q_100p << std::endl;
    }

    else {

        std::srand (std::time(NULL));
        generate_array (array, ARRAY_SIZE);
        print_array (array, ARRAY_SIZE);

        quick_sort (array, 0, ARRAY_SIZE - 1);
        print_array (array, ARRAY_SIZE);

        std::srand (std::time(NULL));
        generate_array (array, ARRAY_SIZE);
        merge_sort (array, 0, ARRAY_SIZE - 1);
        print_array (array, ARRAY_SIZE);

    }

    return 0;
}
