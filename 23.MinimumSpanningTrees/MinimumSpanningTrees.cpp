/*
 * @Descripttion:
 * @Author: ssw
 * @Date: 2022-04-03 17:03:14
 * @LastEditors: ssw
 * @LastEditTime: 2022-04-06 18:58:51
目标：①21.1②17.2③...
17.2扩展表
21.1并查集实现
21.2带路径压缩的按秩合并
23.2最小生成树实现
28.2矩阵运算
24...图
29...线性规划
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
    int FindSet(int x)
    {
        if (p[x - 1] != x)
            p[x - 1] = FindSet(p[x - 1]);
        return p[x - 1];
    }
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
        cout << endl<<"rank  : ";
        for (auto i : rank)
            cout << i << ' ';
        cout << endl;
    }
};

int main()
{
    DisjiontSet x = DisjiontSet(3);
    x.show();
    x.Union(1, 2);
    x.show();
    x.Union(1, 3);
    x.show();
    return 0;
}