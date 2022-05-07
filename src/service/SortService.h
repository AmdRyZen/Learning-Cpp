//
// Created by 天使之王·彦 on 2021/11/16.
//

#ifndef LEARNING_CPP_SORTSERVICE_H
#define LEARNING_CPP_SORTSERVICE_H

class SortService
{
public:
    static void QuickSort(int* array, int left, int right);

    static void BubbleSort(int* array, int len);

    [[maybe_unused]] static int *GenerateRandomArray(int n, int l, int r);

private:
    inline static void Swap(int &a, int &b);
};

#endif //LEARNING_CPP_SORTSERVICE_H
