#include <cstdlib>
#include <iostream>

typedef long long int llint_;

#define ARRAY_SIZE      1e2
#define AVERAGE_SIZE    1e2

void merge_arrays (llint_ array[], int l, int r)
{
    int mid     = l / 2 + r / 2;
    int l_size  = mid - l;
    int r_size  = r - mid + 1;
    llint_ left_arr [l_size];
    llint_ right_arr [r_size];

    for (int i = 0; i < l_size;  i ++) {
        left_arr [i] = array [l + i];
    }
    for (int i = 0; i < r_size;  i ++) {
        right_arr [i] = array [i + mid];
    }

    while (i < l_size && j < r_size) {
        :q

    }
}

void merge_sort (int array[], int l, int r)
{
    if (l == r)
        return;
    else {

    int mid = (l / 2) + (r / 2);

    merge_sort (array, l, mid - 1);
    merge_sort (array, mid, r);

    merge_arrays (array, l, mid, r);
    }
}


void generate_array(llint_ * array, int array_len)
{

    for (int i = 0; i < array_len; i++){
        array[i] = (std::rand() % 100);
    }

}

void print_array (llint_ * array, int size)
{
    for (int i = 0; i < size; i++){
        std::cout <<  array [i]  << '\n';
    }
}

int main()
{
    int array_len = 10;
    llint_ array[array_len];
    generate_array (array, array_len);

    merge_sort (array, 0, array_len - 1);

    print_array (array, 10);
}
