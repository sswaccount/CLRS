/*
 * @Descripttion:
 * @Author: ssw
 * @Date: 2022-04-16 16:46:46
 * @LastEditors: ssw
 * @LastEditTime: 2022-04-22 18:46:35
 */
#include <iostream>
#include "SSSP.h"
using namespace std;

int main()
{
    string sname[5] = {"s", "t", "x", "y", "z"};
    Graph g = Graph(5, 10, sname);
    g.AddEdge("s", "t", 10);
    g.AddEdge("s", "y", 5);
    g.AddEdge("t", "x", 1);
    g.AddEdge("y", "t", 3);
    g.AddEdge("t", "y", 2);
    g.AddEdge("y", "z", 2);
    g.AddEdge("y", "x", 9);
    g.AddEdge("x", "z", 4);
    g.AddEdge("z", "s", 7);
    g.AddEdge("z", "x", 6);
    g.Dijkstar("s");
    cout << g << endl;

    // string sname[6] = {"r", "s", "t", "x", "y", "z"};
    // Graph g = Graph(6, 10, sname);
    // g.AddEdge("r", "s", 5);
    // g.AddEdge("s", "t", 2);
    // g.AddEdge("t", "x", 7);
    // g.AddEdge("x", "y", -1);
    // g.AddEdge("y", "z", -2);
    // g.AddEdge("r", "t", 3);
    // g.AddEdge("s", "x", 6);
    // g.AddEdge("t", "y", 4);
    // g.AddEdge("t", "z", 2);
    // g.AddEdge("x", "z", 1);
    // g.DagShortestPath("s");
    // g.TopoLogicSort();
    return 0;
}