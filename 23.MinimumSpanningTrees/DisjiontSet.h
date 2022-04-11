/*
 * @Descripttion:
 * @Author: ssw
 * @Date: 2022-04-11 18:55:18
 * @LastEditors: ssw
 * @LastEditTime: 2022-04-11 18:58:35
 */
#include <vector>
#include <iostream>
using namespace std;

class DisjiontSet
{
private:
    int n;
    vector<int> p;
    vector<int> rank;

    void Link(int x, int y)
    {
        if (rank[x - 1] > rank[y - 1])
            p[y - 1] = x;
        else
        {
            p[x - 1] = y;
            if (rank[x - 1] == rank[y - 1])
                rank[y - 1]++;
        }
    }

public:
    DisjiontSet(int num = 0)
        : n(num)
    {
        for (int i = 1; i <= num; ++i)
        {
            p.push_back(i);
            rank.push_back(0);
        }
    }
    void Union(int x, int y)
    {
        Link(FindSet(x), FindSet(y));
    }
    void show()
    {
        cout << "parent: ";
        for (auto i : p)
            cout << i << ' ';
        cout << endl
             << "rank  : ";
        for (auto i : rank)
            cout << i << ' ';
        cout << endl;
    }
    int FindSet(int x)
    {
        if (p[x - 1] != x)
            p[x - 1] = FindSet(p[x - 1]);
        return p[x - 1];
    }
};