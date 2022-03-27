/*
 * @Descripttion:
 * @Author: ssw
 * @Date: 2022-03-27 18:42:36
 * @LastEditors: ssw
 * @LastEditTime: 2022-03-27 20:59:00
 */

#include <algorithm>
#include <iostream>
#include "BasicGraph.h"
int main()
{
    char ver[8] = {'r', 's', 't', 'u', 'v', 'w', 'x', 'y'};
    Graph x(8, 10, ver);

    freopen("BFS.dot", "w", stdout);
    cout << "digraph Tree{" << endl;

    x.AddEdge('r', 'v', true);
    x.AddEdge('r', 's', true);
    x.AddEdge('s', 'w', true);
    x.AddEdge('w', 't', true);
    x.AddEdge('w', 'x', true);
    x.AddEdge('t', 'x', true);
    x.AddEdge('u', 't', true);
    x.AddEdge('u', 'y', true);
    x.AddEdge('u', 'x', true);
    x.AddEdge('x', 'y', true);
    x.BFS('s');

    cout << "}" << endl;
    fclose(stdout);
    return 0;
}