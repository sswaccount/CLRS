/*
 * @Descripttion:
 * @Author: ssw
 * @Date: 2022-03-12 22:09:11
 * @LastEditors: ssw
 * @LastEditTime: 2022-03-14 13:42:46
 */
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "sort.h"
using namespace std;

int main()
{
    srand(time(0));
    // int a_size = rand() % 10 + 10;
    // int a[10000];
    // Random(a, a_size, 10, 50);
    // Print(a, a_size);
    // MergeSort(a, 1, a_size);
    // Print(a, a_size);

    // int b_size = 20;
    // int *b = new int[b_size + 1];
    // Random(b, b_size, -20, 20);
    // Print(b, b_size);
    // cout << FindMaxNumSubarray(b, 1, b_size).first.first << ' ';
    // cout << FindMaxNumSubarray(b, 1, b_size).first.second << ' ';
    // cout << FindMaxNumSubarray(b, 1, b_size).second << endl;
    // Print(b, b_size);
    // delete []b;

    // int b_size = rand() % 10 + 10;
    // int *b = new int[b_size + 1];
    // Random(b, b_size, 10, 99);
    // Print(b, b_size);
    // HeapSort(b, b_size);
    // Print(b, b_size);

    // int b_size = rand() % 10 + 10;
    // int *b = new int[1000];
    // Random(b, b_size, 10, 99);
    // Print(b, b_size);
    // BuildMaxHeap(b, b_size);
    // Print(b, b_size);
    // cout << HeapExtractMax(b, b_size) << endl;
    // Print(b, b_size);
    // MaxHeapInsert(b, 97, b_size);
    // Print(b, b_size);

    // int a_size = rand() % 10 + 10;
    // int a[10000];
    // Random(a, a_size, 10, 50);
    // Print(a, a_size);
    // QuickSort(a, 1, a_size);
    // Print(a, a_size);

    int a_size = rand() % 10 + 10;
    int a[10000];
    int b[10000];
    Random(a, a_size, 10, 50);
    Print(a, a_size);
    BuildMaxHeap(a, a_size);
    Print(a, a_size);
    CountSort(a, b, a[1], a_size);
    Print(b, a_size);
    return 0;
}