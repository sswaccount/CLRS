/*
 * @Descripttion:
 * @Author: ssw
 * @Date: 2022-03-27 18:42:36
 * @LastEditors: ssw
 * @LastEditTime: 2022-04-02 17:31:44
 */

#include <algorithm>
#include <iostream>
#include "BasicGraph.h"
int main()
{
    // string ver[9] = {"领带", "裤子", "内裤", "袜子", "手表", "鞋", "腰带", "衬衣", "夹克"};
    string ver[8] = {"b", "e", "a", "c", "d", "f", "g", "h"};
    // for (int i = 0; i < 8; i++)
    //     ver[i] = 'a' + i;
    // for (auto i : ver)
    //     cout << i << endl;
    Graph x(8, 14, ver);

    // freopen("mirr.dot", "w", stdout);
    // cout << "digraph Tree{" << endl;
    // cout << "rankdir=LR" << endl;
    // x.AddEdge("r", "v", true);
    // x.AddEdge("r", "s", true);
    // x.AddEdge("s", "w", true);
    // x.AddEdge("w", "t", true);
    // x.AddEdge("w", "x", true);
    // x.AddEdge("t", "x", true);
    // x.AddEdge("u", "t", true);
    // x.AddEdge("u", "y", true);
    // x.AddEdge("u", "x", true);
    // x.AddEdge("x", "y", true);
    // x.AddEdge("袜子", "鞋");
    // x.AddEdge("内裤", "鞋");
    // x.AddEdge("内裤", "裤子");
    // x.AddEdge("裤子", "鞋");
    // x.AddEdge("裤子", "腰带");
    // x.AddEdge("衬衣", "腰带");
    // x.AddEdge("衬衣", "领带");
    // x.AddEdge("领带", "夹克");
    // x.AddEdge("腰带", "夹克");
    x.AddEdge("a", "b");
    x.AddEdge("e", "a");
    x.AddEdge("b", "e");
    x.AddEdge("b", "f");
    x.AddEdge("e", "f");
    x.AddEdge("b", "c");
    x.AddEdge("f", "g", true);
    x.AddEdge("c", "g");
    x.AddEdge("c", "d", true);
    x.AddEdge("g", "h");
    x.AddEdge("d", "h");
    x.AddEdge("h", "h");
    // x.BFS("s");
    // x.PrintPath("s", "y");
    // x.DFS(true);
    x.StronglyConnectedComponents();
    // x.TopoLogicSort();
    // cout << "}" << endl;
    // fclose(stdout);
    return 0;
}