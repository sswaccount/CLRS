/*
 * @Descripttion:
 * @Author: ssw
 * @Date: 2022-04-03 17:03:14
 * @LastEditors: ssw
 * @LastEditTime: 2022-04-11 21:52:04
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
#include <map>
#include <iostream>
#include <algorithm>
#include <queue>
#include "Heap.h"
#include "DisjiontSet.h"
using namespace std;

// typedef pair<pair<int, int>, int> PII_I;
class Graph
{
private:
    int V, E;

public:
    vector<pair<pair<int, int>, int>> G;
    vector<Vertex> Gprime;
    map<char, int> index;
    Graph(int v, int e)
        : V(v), E(e)
    {
        for (int i = 0; i < v; ++i)
        {
            char num = i + 'a';
            Gprime.push_back(Vertex(num));
            index.insert({num, i});
        }
        // for(auto i :Gprime)
        //     cout << i._name << endl;
    }
    void add(char u, char v, int w)
    {
        add(u - 'a' + 1, v - 'a' + 1, w);
        addPrim(u, v, true);
    }
    void add(int u, int v, int w)
    {
        G.push_back({{u, v}, w});
    }
    void addPrim(char u, char v, bool flag = false)
    {
        NextNode *e = new NextNode(v);
        if (Gprime[index[u]]._first == nullptr)
            Gprime[index[u]]._first = e;
        else
        {
            NextNode *p = Gprime[index[u]]._first;
            while (p->NEXT)
                p = p->NEXT;
            p->NEXT = e;
        }
        if (flag)
            addPrim(v, u);
    }
    void addPrim(int u, int v, bool flag = false)
    {
        addPrim(u - 1 + 'a', v - 1 + 'a');
    }
    void MST_KRUSKAL();
    void MST_PRIM(char root = 'a');
};

void Graph::MST_PRIM(char root)
{
    Gprime[root - 'a']._key = 0;

    Heap Q = Heap(Gprime);
    Q.BuildMinHeap();
    vector<bool> judge(V, false);
    for (auto i : Gprime)
    {
        judge[i._name - 'a'] = true;
    }
    map<pair<int, int>, int> EdgeIndex(G.begin(), G.end());
    for (auto i : G)
        EdgeIndex[{i.first.second, i.first.first}] = i.second;

    while (!Q.empty())
    {
        Vertex u = Q.HeapMinimum();
        Q.HeapExtractMin();
        int index = u._name - 'a';
        judge[index] = false;
        if (u._name != root)
            cout << u._first->adjvex << ' '
                 << u._name << ' '
                 << u._key << endl;
        for (auto v = Gprime[index]._first; v; v = v->NEXT)
        {
            int next_index = v->adjvex - 'a';
            int w = EdgeIndex[{index + 1, next_index + 1}];
            if (judge[next_index] && w < Gprime[next_index]._key)
            {
                Gprime[next_index]._pi = &u;
                Gprime[next_index]._key = w;
                Q.HeapDecreaseKey(Gprime[next_index]._name, w);
            }
        }
    }
}

void Graph::MST_KRUSKAL()
{
    vector<pair<int, int>> A;
    DisjiontSet x = DisjiontSet(V);
    sort(G.begin(), G.end(), cmp);
    for (auto i : G)
    {
        // cout << i.second << endl;
        if (x.FindSet(i.first.second) != x.FindSet(i.first.first))
        {
            A.push_back({i.first.first, i.first.second});
            x.Union(i.first.first, i.first.second);
        }
    }
    for (auto i : A)
        cout << (char)(i.first + 'a' - 1)
             << ' '
             << (char)(i.second + 'a' - 1)
             << endl;
}

int main()
{
    Graph g = Graph(9, 14);
    {
        g.add('a', 'b', 4);
        g.add('a', 'h', 8);
        g.add('b', 'h', 11);
        g.add('h', 'i', 7);
        g.add('h', 'g', 1);
        g.add('b', 'c', 8);
        g.add('i', 'c', 2);
        g.add('i', 'g', 6);
        g.add('c', 'f', 4);
        g.add('g', 'f', 2);
        g.add('c', 'd', 7);
        g.add('d', 'f', 14);
        g.add('d', 'e', 9);
        g.add('f', 'e', 10);
    }

    // g.MST_KRUSKAL();
    g.MST_PRIM('a');
    return 0;
}