/*
 * @Descripttion:
 * @Author: ssw
 * @Date: 2022-01-14 20:22:40
 * @LastEditors: ssw
 * @LastEditTime: 2022-03-25 20:46:05
 */
#include <iostream>
#include "RedBlackTree.h"
using namespace std;
int main()
{
    // Tree<int> x;
    // TreeNode<int> xx(1);
    // xx.color = BALCK;
    // cout << xx.color << endl;
    RBTree<int> x;

    x.InsertNode(6);
    x.InsertNode(8);
    x.InsertNode(3);
    x.InsertNode(7);
    x.InsertNode(2);
    // x.InsertNode(1);

    cout << (x.GetRoot()->_p == nullptr) << endl;

    x.InorderTreeWalk(x.GetRoot());
    return 0;
}