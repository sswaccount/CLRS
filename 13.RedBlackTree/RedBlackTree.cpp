/*
 * @Descripttion:
 * @Author: ssw
 * @Date: 2022-01-14 20:22:40
 * @LastEditors: ssw
 * @LastEditTime: 2022-03-25 23:56:35
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
    // cout << x.GetRoot() << endl;
    // cout << "Inorder : " << endl;
    // x.InorderTreeWalk(x.GetRoot());
    // cout << "Insert : " << endl;
    x.InsertNode(6);
    x.InsertNode(4);
    x.InsertNode(5);
    x.InsertNode(8);
    x.InsertNode(7);
    // x.InsertNode(1);
    // x.InsertNode(4);
    // x.InsertNode(9);
    // x.InsertNode(10);
    
    // cout << "Inorder : " << endl;
    // x.InorderTreeWalk(x.GetRoot());
    // cout << (x.GetRoot()->_p == nullptr) << endl;
    // cout << x.GetRoot() << endl;
    // x.InorderTreeWalk(x.GetRoot());
    x.TreeOut(x.GetRoot(), "RB");
    // TreeNode<int> *test = new TreeNode<int>(0);
    // cout << test->_key << endl;

    return 0;
}