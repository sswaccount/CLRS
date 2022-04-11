/*
 * @Descripttion:
 * @Author: ssw
 * @Date: 2022-04-11 18:53:02
 * @LastEditors: ssw
 * @LastEditTime: 2022-04-11 21:50:40
 */

#include <vector>
using namespace std;

bool cmp(const pair<pair<int, int>, int> &a, const pair<pair<int, int>, int> &b)
{
    return a.second < b.second;
}

struct NextNode
{
    char adjvex;
    NextNode *NEXT;
    NextNode(char name = ' ')
        : adjvex(name),
          NEXT(nullptr) {}
};

struct Vertex
{
    char _name;
    Vertex *_pi;
    int _key;
    NextNode *_first;
    Vertex(char name = ' ')
        : _name(name),
          _pi(nullptr),
          _key(1000),
          _first(nullptr) {}
    bool operator<(Vertex x)
    {
        return _key < x._key;
    }
    bool operator>(Vertex x)
    {
        return _key > x._key;
    }
};

class Heap
{
private:
    vector<Vertex> data;
    int heap_size = 0;
    int MinNum = -1;
    map<char, int> indexfind;
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
    void MinHeapify(int i)
    {
        int l = Left(i);
        int r = Right(i);
        int largest = i;
        if (l <= heap_size && data[l] < data[i])
            largest = l;
        else
            largest = i;
        if (r <= heap_size && data[r] < data[largest])
            largest = r;
        if (largest != i)
        {
            swap(data[i], data[largest]);
            swap(indexfind[data[i]._name], indexfind[data[largest]._name]);
            MinHeapify(largest);
        }
    }

public:
    Heap(vector<Vertex> vT)
    {
        data.push_back(Vertex(' '));
        //插入数据维护哈希name信息：
        for (auto i : vT)
        {
            data.push_back(i);
            indexfind[i._name] = ++heap_size;
        }
    }

    void BuildMinHeap()
    {
        for (int i = heap_size >> 1; i >= 1; i--)
            MinHeapify(i);
    }
    Vertex HeapMinimum() const
    {
        return data[1];
    }
    int HeapExtractMin()
    {
        int key = data[1]._key;
        swap(indexfind[data[1]._name], indexfind[data[heap_size]._name]);
        data[1] = data[heap_size--];
        MinHeapify(1);
        return key;
    }
    void HeapDecreaseKey(char name, int key)
    {
        int i = indexfind[name];
        if (key > data[i]._key)
            return;

        data[i]._key = key;
        while (i > 1 && data[Parent(i)] > data[i])
        {
            swap(data[i], data[Parent(i)]);
            swap(indexfind[data[i]._name], indexfind[data[Parent(i)]._name]);
            i = Parent(i);
        }
    }
    bool empty()
    {
        if (heap_size > 0)
            return false;
        return true;
    }
    void show()
    {
        cout << "------------------" << endl;
        for (int i = 1; i <= heap_size; ++i)
            cout << data[i]._name << ' ' << data[i]._key << endl;
        cout << "------------------" << endl
             << endl;
    }
};