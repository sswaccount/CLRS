/*
 * @Descripttion:
 * @Author: ssw
 * @Date: 2022-03-27 18:49:52
 * @LastEditors: ssw
 * @LastEditTime: 2022-03-31 18:56:51
 */
#include <iostream>
#include <vector>
#include <map>
#include <queue>
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
    NextNode *NEXT;
    NextNode(string name = "")
        : adjvex(name),
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
};

class Graph
{
private:
    int vertex, edge;
    vector<Vertex> G;
    vector<Vertex> GT;
    map<string, int> index;
    int time;
    int count;
    vector<string> topo;

public:
    Graph(int v, int e, string *vs)
        : vertex(v), edge(e)
    {
        for (int i = 0; i < v; ++i)
        {
            G.push_back(Vertex(vs[i]));
            GT.push_back(Vertex(vs[i]));
            index.insert({vs[i], i});
        }
    }
    void AddEdge(string x, string y, bool flag = false);
    void BFS(string s);
    void PrintPath(string v, string s);
    void DFS(bool flag = false);
    void DFSVisit(string u, bool flag);
    void DFSVisit(string u);
    void TopoLogicSort();
    void StronglyConnectedComponents();
};

void Graph::AddEdge(string x, string y, bool flag)
{
    NextNode *e = new NextNode(y);
    if (G[index[x]]._first == nullptr)
        G[index[x]]._first = e;
    else
    {
        NextNode *p = G[index[x]]._first;
        while (p->NEXT)
            p = p->NEXT;
        p->NEXT = e;
    }

    NextNode *eT = new NextNode(x);
    if (GT[index[y]]._first == nullptr)
        GT[index[y]]._first = eT;
    else
    {
        NextNode *p = GT[index[y]]._first;
        while (p->NEXT)
            p = p->NEXT;
        p->NEXT = eT;
    }
    
    if (flag)
        AddEdge(y, x);
    // cout << y << "->" << x << endl;
    
}

void Graph::BFS(string s)
{
    for (auto u : G)
        if (u._name != s)
        {
            u._color = WHITE;
            u._d = 0x7fffffff;
            u._pi = nullptr;
        }
    G[index[s]]._color = GRAY;
    G[index[s]]._d = 0;
    G[index[s]]._pi = nullptr;

    queue<string> Q;
    Q.push(s);
    while (Q.size())
    {
        string u = Q.front();
        Q.pop();
        for (auto v = G[index[u]]._first; v; v = v->NEXT)
            if (G[index[v->adjvex]]._color == WHITE)
            {
                G[index[v->adjvex]]._color = GRAY;
                G[index[v->adjvex]]._d = G[index[u]]._d + 1;
                G[index[v->adjvex]]._pi = &G[index[u]];
                Q.push(v->adjvex);
            }
        G[index[u]]._color = BLACK;

        // cout << u << " [style=filled,fillcolor=\".3 .";
        // if (G[index[u]]._d == 0)
        //     cout << 0;
        // else if (G[index[u]]._d == 1)
        //     cout << 3;
        // else if (G[index[u]]._d == 2)
        //     cout << 6;
        // else if (G[index[u]]._d == 3)
        //     cout << 9;
        // cout << " 1.0\"]" << endl;
    }
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
        // cout << G[index[u]]._name << ' '
        //      << G[index[u]]._d << ' '
        //      << G[index[u]]._f << endl;
        topo.push_back(u);
    }
}

void Graph::TopoLogicSort()
{
    
    for (int i = 1; i < topo.size(); ++i)
        cout << topo[i - 1] << "--" << topo[i] << endl;
}


void Graph::StronglyConnectedComponents()
{
    DFS(true);
    reverse(topo.begin(), topo.end());
    
    for (auto i : GT)
    {
        i._color = WHITE;
        i._pi = nullptr;
        // cerr << "dsadsa : " << i._name << endl;
    }
    time = 0;
    for (auto i : topo)
    {
        if (GT[index[i]]._color == WHITE)
        {
            DFSVisit(GT[index[i]]._name);
            cout << endl;
        }
    }
}

void Graph::DFSVisit(string u)
{
    GT[index[u]]._d = ++time;
    GT[index[u]]._color = GRAY;
    for (auto v = GT[index[u]]._first; v; v = v->NEXT)
        if (GT[index[v->adjvex]]._color == WHITE)
        {
            GT[index[v->adjvex]]._pi = &GT[index[u]];
            DFSVisit(v->adjvex);
        }
    GT[index[u]]._color = BLACK;
    GT[index[u]]._f = ++time;
    cout << u << ' ';
}