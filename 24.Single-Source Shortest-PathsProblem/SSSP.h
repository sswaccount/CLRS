/*
 * @Descripttion:
 * @Author: ssw
 * @Date: 2022-04-16 16:46:46
 * @LastEditors: ssw
 * @LastEditTime: 2022-04-23 00:08:49
 */
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

enum VerClolor
{
    WHITE,
    GRAY,
    BLACK,
};

struct NextNode
{
    string adjvex;
    int w;
    NextNode *NEXT;
    NextNode(string name = "", int weight = 0)
        : adjvex(name),
          w(weight),
          NEXT(nullptr) {}
};

struct Vertex
{
    string _name;
    VerClolor _color;
    Vertex *_pi;
    int _d;
    int _f;
    NextNode *_first;
    Vertex(string name = "")
        : _name(name),
          _color(WHITE),
          _pi(nullptr),
          _d(0),
          _f(0),
          _first(nullptr) {}
    bool operator<(Vertex x)
    {
        return _d < x._d;
    }
    bool operator>(Vertex x)
    {
        return _d > x._d;
    }
};

class Heap
{
private:
    vector<Vertex> data;
    int heap_size = 0;
    int MinNum = -1;
    map<string, int> indexfind;
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
        data.push_back(Vertex(" "));
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
        int key = data[1]._d;
        swap(indexfind[data[1]._name], indexfind[data[heap_size]._name]);
        data[1] = data[heap_size--];
        MinHeapify(1);
        return key;
    }
    void HeapDecreaseKey(string name, int key)
    {
        int i = indexfind[name];
        if (key > data[i]._d)
            return;

        data[i]._d = key;
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
            cout << data[i]._name << ' ' << data[i]._d << endl;
        cout << "------------------" << endl
             << endl;
    }
};

class Graph
{
private:
    int vertex, edge;
    vector<Vertex> G;
    map<string, int> index;
    map<pair<string, string>, int> weight;
    vector<string> topo;
    int Maxnum = 10000;
    int time;
    int count;
    Heap *Q;

public:
    Graph(int v, int e, string *vs)
        : vertex(v), edge(e)
    {
        for (int i = 0; i < v; ++i)
        {
            G.push_back(Vertex(vs[i]));
            index.insert({vs[i], i});
        }
    }
    void AddEdge(string x, string y, int w, bool flag = false);
    void AddEdge(int x, int y, int w);
    void PrintPath(string v, string s);
    void InitializeSingleSource(string s);
    void Relax(string u, string v, bool flag = false);
    bool BellmanFord(string root);
    void DFS(bool flag = false);
    void DFSVisit(string u, bool flag);
    void TopoLogicSort();
    void DagShortestPath(string s);
    void Dijkstar(string s);
    friend ostream &operator<<(ostream &os, Graph data);
    void InitDiff();
    bool BellmanFord();
};

void Graph::AddEdge(int x, int y, int w)
{
    string xx, yy;
    xx.push_back(x + 'a');
    yy.push_back(y + 'a');
    AddEdge(xx, yy, w, false);
}

void Graph::AddEdge(string x, string y, int w, bool flag)
{
    weight[{x, y}] = w;
    NextNode *e = new NextNode(y, w);
    if (G[index[x]]._first == nullptr)
        G[index[x]]._first = e;
    else
    {
        NextNode *p = G[index[x]]._first;
        while (p->NEXT)
            p = p->NEXT;
        p->NEXT = e;
    }

    if (flag)
        AddEdge(y, x, w);
    // cout << y << "->" << x << endl;
}

void Graph::PrintPath(string s, string v)
{
    if (v == s)
        cout << s << ' ';
    else if (G[index[v]]._pi == nullptr)
        cout << "NO Path" << endl;
    else
    {
        PrintPath(s, G[index[v]]._pi->_name);
        cout << v << ' ';
    }
}

void Graph::InitializeSingleSource(string s)
{
    for (auto &i : G)
    {
        i._d = Maxnum;
        i._pi = nullptr;
    }
    G[index[s]]._d = 0;
}

void Graph::Relax(string u, string v, bool flag)
{
    if (G[index[v]]._d > G[index[u]]._d + weight[{u, v}])
    {
        G[index[v]]._d = G[index[u]]._d + weight[{u, v}];
        G[index[v]]._pi = &G[index[u]];
        if (flag)
            Q->HeapDecreaseKey(v, G[index[v]]._d);
    }
}

bool Graph::BellmanFord(string root)
{
    InitializeSingleSource(root);
    for (int i = 1; i < vertex; i++)
        for (auto it : weight)
            Relax(it.first.first, it.first.second);
    for (auto it : weight)
        if (G[index[it.first.second]]._d > G[index[it.first.first]]._d + it.second)
            return false;

    for (auto i : G)
        cout << i._name << ' ' << i._d << endl;
    return true;
}

void Graph::DFS(bool flag)
{
    for (auto i : G)
    {
        i._color = WHITE;
        i._pi = nullptr;
        // cerr << "dsadsa : " << i._name << endl;
    }
    time = 0;
    count = 0;
    for (auto i : G)
    {
        // cout << "test : " << i._name << endl;
        if (i._color == WHITE)
            DFSVisit(i._name, flag);
    }
    if (flag)
        reverse(topo.begin(), topo.end());
}

void Graph::DFSVisit(string u, bool flag)
{
    G[index[u]]._d = ++time;
    G[index[u]]._color = GRAY;
    for (auto v = G[index[u]]._first; v; v = v->NEXT)
        if (G[index[v->adjvex]]._color == WHITE)
        {
            G[index[v->adjvex]]._pi = &G[index[u]];
            DFSVisit(v->adjvex, flag);
        }
    G[index[u]]._color = BLACK;
    G[index[u]]._f = ++time;

    if (flag)
    {
        topo.push_back(u);
    }
}

void Graph::TopoLogicSort()
{
    cout << topo[0];
    for (int i = 1; i < topo.size(); ++i)
        cout << " -- " << topo[i];
    cout << endl;
}

void Graph::DagShortestPath(string s)
{
    DFS(true);
    InitializeSingleSource(s);
    for (auto u : topo)
        for (auto v = G[index[u]]._first; v; v = v->NEXT)
            Relax(u, v->adjvex);
    for (auto i : G)
        cout << i._name << ' ' << i._d << endl;
}

void Graph::Dijkstar(string s)
{
    InitializeSingleSource(s);
    Q = new Heap(G);
    Q->BuildMinHeap();
    while (!Q->empty())
    {
        Vertex u = Q->HeapMinimum();
        Q->HeapExtractMin();
        string inx = u._name;
        for (auto v = G[index[inx]]._first; v; v = v->NEXT)
        {
            Relax(inx, v->adjvex, true);
        }
        cout << u._name << ' ' << u._d << endl;
    }
}

ostream &operator<<(ostream &os, Graph data)
{
    for (auto i : data.G)
        os << i._name << ' ' << i._d << endl;
    return os;
}

void Graph::InitDiff()
{
    for (auto &i : G)
    {
        i._d = 0;
        i._pi = nullptr;
    }
}
bool Graph::BellmanFord()
{
    InitDiff();
    for (int i = 1; i < vertex; i++)
        for (auto it : weight)
            Relax(it.first.first, it.first.second);
    for (auto it : weight)
        if (G[index[it.first.second]]._d > G[index[it.first.first]]._d + it.second)
            return false;
    return true;
}