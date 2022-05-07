//
// Created by 天使之王·彦 on 2021/11/16.
//

#include <src/service/SortService.h>
#include <cstdlib>
#include <ctime>

inline void SortService::Swap(int& a, int& b)
{
    int t=a;
    a=b;
    b=t;
}

void SortService::QuickSort(int* array, int left, int right) {
    if (array == nullptr) return;
    if (left >= right) return;

    //防止有序队列导致快速排序效率降低
    //srand((unsigned)time(NULL));
    int len = right - left;
    int k_index = rand() % (len + 1) + left;
    SortService::Swap(array[left], array[k_index]);

    int key = array[left], i = left, j = right;
    while (i < j) {
        while (array[j] >= key && i < j) --j;
        if (i < j) array[i] = array[j];
        while (array[i] < key && i < j) ++i;
        if (i < j) array[j] = array[i];
    }
    array[i] = key;
    SortService::QuickSort(array, left, i - 1);
    SortService::QuickSort(array, j + 1, right);
    return;
}

void SortService::BubbleSort(int *array, int len) {
    if (array == nullptr) return;
    if (len <= 1) return;
    for (int i = 0; i < len -1; ++i) {
        for (int j = 0; j < len - 1; ++j) {
            if (array[j] > array[j+1])
                SortService::Swap(array[j], array[j + 1]);
        }
    }
    return;
}

[[maybe_unused]] int *SortService::GenerateRandomArray(int n, int l, int r) {
    int *arr = new int[n];
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % (r - l + 1) + l;
    }
    return arr;
}
