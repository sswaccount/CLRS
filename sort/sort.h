/*
 * @Descripttion:
 * @Author: ssw
 * @Date: 2022-03-13 11:29:29
 * @LastEditors: ssw
 * @LastEditTime: 2022-03-14 13:44:15
 */
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <map>
using namespace std;
typedef pair<pair<int, int>, int> PPI;
const int MaxNum = 0x7fffffff;
const int MinNum = 0xffffffff;

void Random(int *a, int n, int l, int r)
{
    srand(time(0));
    for (int i = 1; i <= n; i++)
        a[i] = rand() % (r - l + 1) + l;
}

void Print(int *a, int n)
{
    for (int i = 1; i <= n; i++)
        cout << a[i] << ' ';
    cout << endl;
}

void Merge(int *a, int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;
    int *L = new int[n1 + 2];
    int *R = new int[n2 + 2];
    for (int i = 1; i <= n1; i++)
        L[i] = a[p + i - 1];
    for (int j = 1; j <= n2; j++)
        R[j] = a[q + j];
    L[n1 + 1] = R[n2 + 1] = MaxNum;
    int i = 1, j = 1;
    for (int k = p; k <= r; k++)
    {
        if (L[i] <= R[j])
            a[k] = L[i++];
        else
            a[k] = R[j++];
    }
    delete[] L;
    delete[] R;
}

void MergeSort(int *a, int p, int r)
{
    if (p < r)
    {
        int q = p + r >> 1;
        MergeSort(a, p, q);
        MergeSort(a, q + 1, r);
        Merge(a, p, q, r);
    }
}

PPI FindMaxCrossSubarrray(int *a, int low, int mid, int high)
{
    int left_sum = MinNum, right_sum = MinNum;
    int max_left = mid, max_right = mid + 1, sum = 0;
    for (int i = mid; i >= low; i--)
    {
        sum += a[i];
        if (sum > left_sum)
        {
            left_sum = sum;
            max_left = i;
        }
    }
    sum = 0;
    for (int j = mid + 1; j <= high; j++)
    {
        sum += a[j];
        if (sum > right_sum)
        {
            right_sum = sum;
            max_right = j;
        }
    }
    return {{max_left, max_right}, left_sum + right_sum};
}

PPI FindMaxNumSubarray(int *a, int low, int high)
{
    if (high == low)
        return {{low, high}, a[low]};
    else
    {
        int mid = low + high >> 1;
        PPI left = FindMaxNumSubarray(a, low, mid);
        PPI right = FindMaxNumSubarray(a, mid + 1, high);
        PPI cross = FindMaxCrossSubarrray(a, low, mid, high);

        if (left.second >= right.second && left.second >= cross.second)
            return left;
        else if (right.second >= left.second && right.second >= cross.second)
            return right;
        else
            return cross;
    }
}

int Parent(int i)
{
    return i >> 1;
}

int Left(int i)
{
    return i << 1;
}

int Right(int i)
{
    return (i << 1) + 1;
}

void MaxHeapify(int *a, int i, int heap_size)
{
    int l = Left(i);
    int r = Right(i);
    int largest = i;
    if (l <= heap_size && a[l] > a[i])
        largest = l;
    else
        largest = i;
    if (r <= heap_size && a[r] > a[largest])
        largest = r;
    if (largest != i)
    {
        swap(a[i], a[largest]);
        MaxHeapify(a, largest, heap_size);
    }
}

void BuildMaxHeap(int *a, int size)
{
    int heap_size = size;
    for (int i = heap_size >> 1; i >= 1; i--)
        MaxHeapify(a, i, heap_size);
}

void HeapSort(int *a, int size)
{
    BuildMaxHeap(a, size);
    int heap_size = size;
    for (int i = size; i > 1; i--)
    {
        swap(a[1], a[i]);
        MaxHeapify(a, 1, --heap_size);
    }
}

int HeapMaxiNum(int *a)
{
    return a[1];
}

int HeapExtractMax(int *a, int &size)
{
    if (size < 1)
        return -1;
    int max_num = a[1];
    a[1] = a[size];
    MaxHeapify(a, 1, --size);
    return max_num;
}

void HeapIncreaseKey(int *a, int i, int key)
{
    if (key < a[i])
        return;
    a[i] = key;
    while (i > 1 && a[Parent(i)] < a[i])
    {
        swap(a[i], a[Parent(i)]);
        i = Parent(i);
    }
}

void MaxHeapInsert(int *a, int key, int &size)
{
    size++;
    a[size] = MinNum;
    HeapIncreaseKey(a, size, key);
}

int Partition(int *a, int p, int r)
{
    int x = a[r];
    int i = p - 1;
    for (int j = p; j <= r; j++)
        if (a[j] < x)
            swap(a[++i], a[j]);
    swap(a[++i], a[r]);
    return i;
}

void QuickSort(int *a, int p, int r)
{
    if (p < r)
    {
        int q = Partition(a, p, r);
        QuickSort(a, p, q - 1);
        QuickSort(a, q + 1, r);
    }
}

void CountSort(int *a,int *b, int k, int a_size)
{
    int *c = new int[k + 1]();
    for (int j = 1; j <= a_size; j++)
        c[a[j]]++;
    for (int i = 1; i <= k; i++)
        c[i] += c[i - 1];
    for (int j = a_size; j >= 1; j--)
    {
        b[c[a[j]]--] = a[j];
    }
}
