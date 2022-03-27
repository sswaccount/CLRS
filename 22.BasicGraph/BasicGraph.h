/*
 * @Descripttion:
 * @Author: ssw
 * @Date: 2022-03-27 18:49:52
 * @LastEditors: ssw
 * @LastEditTime: 2022-03-27 21:16:43
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
    char adjvex;
    NextNode *NEXT;
    NextNode(char name = ' ')
        : adjvex(name),
          NEXT(nullptr) {}
};

struct Vertex
{
    char _name;
    VerClolor _color;
    Vertex *_pi;
    int _d;
    NextNode *_first;
    Vertex(char name = ' ')
        : _name(name),
          _color(WHITE),
          _pi(nullptr),
          _d(0),
          _first(nullptr) {}
};

class Graph
{
private:
    int vertex, edge;
    vector<Vertex> G;
    map<char, int> index;

public:
    Graph(int v, int e, char *vs)
        : vertex(v), edge(e)
    {
        for (int i = 0; i < v; ++i)
        {
            G.push_back(Vertex(vs[i]));
            index.insert({vs[i], i});
        }
    }
    void AddEdge(char x, char y, bool flag = false);
    void BFS(char s);
};

void Graph::AddEdge(char x, char y, bool flag)
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
    if (flag)
        AddEdge(y, x);
    
    cout << x << "->" << y << endl; 
}

void Graph::BFS(char s)
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

    queue<char> Q;
    Q.push(s);
    while (Q.size())
    {
        char u = Q.front();
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
        
        cout << u << " [style=filled,fillcolor=\".3 .";
        if(G[index[u]]._d==0)
            cout << 0;
        else if(G[index[u]]._d==1)
            cout << 3;
        else if(G[index[u]]._d==2)
            cout << 6;
        else if(G[index[u]]._d==3)
            cout << 9;
        cout << " 1.0\"]" << endl;
    }

    
}