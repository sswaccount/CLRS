/*
 * @Descripttion:
 * @Author: ssw
 * @Date: 2022-04-22 22:59:24
 * @LastEditors: ssw
 * @LastEditTime: 2022-04-23 00:05:44
 */
#include <iostream>
#include "SSSP.h"

class Diff
{
private:
    Graph *g;

public:
    Diff(int n, int m, int **data)
    {
        string *vs = new string[n];
        for (int i = 0; i < n; ++i)
        {
            string s;
            s.push_back('a' + i);
            vs[i] = s;
        }
        g = new Graph(n, m, vs);
        for (int i = 0; i < m; ++i)
        {
            cout << *data[i] << endl;
            int positive, negative;
            for (int j = 0; j < n; ++j)
            {
                // if(data[i][j]==1)
                //     positive = j;
                // if(data[i][j]==-1)
                //     negative = j;
            }
            cout << positive << ' ' << negative << endl;
        }
    }
};
int main()
{
    int data[8][6] = {{1, -1, 0, 0, 0, 0},
                      {1, 0, 0, 0, -1, -1},
                      {0, 1, 0, 0, -1, 1},
                      {-1, 0, 1, 0, 0, 5},
                      {-1, 0, 0, 1, 0, 4},
                      {0, 0, -1, 1, 0, -1},
                      {0, 0, -1, 0, 1, -3},
                      {0, 0, 0, -1, 1, -3}};
    string *vs = new string[5];
    for (int i = 0; i < 5; ++i)
    {
        string s;
        s.push_back('a' + i);
        vs[i] = s;
    }
    Graph *g = new Graph(5, 8, vs);
    for (int i = 0; i < 8; ++i)
    {
        int positive, negative;
        for (int j = 0; j < 6 - 1; ++j)
        {
            if (data[i][j] == 1)
                positive = j;
            if (data[i][j] == -1)
                negative = j;
        }
        g->AddEdge(negative, positive, data[i][5]);
    }
    g->BellmanFord();
    cout << *g << endl;
    return 0;
}