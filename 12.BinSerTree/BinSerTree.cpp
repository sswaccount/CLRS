/*
 * @Descripttion:
 * @Author: ssw
 * @Date: 2022-03-17 18:09:09
 * @LastEditors: ssw
 * @LastEditTime: 2022-03-25 17:37:33
 */
#include <iostream>
#include "BinSerTree.h"

int main()
{
    Tree<int> x;
    x.InsertNode(6);
    x.InsertNode(4);
    x.InsertNode(10);
    x.InsertNode(12);
    x.InsertNode(2);
    x.InsertNode(5);
    x.InsertNode(7);
    x.InsertNode(8);
    
    //三种顺序遍历
    cout << "Inorder Tree Walk : ";
    x.InorderTreeWalk(x.GetRoot());
    cout << endl;
    cout << "Preorder Tree Walk : ";
    x.PreorderTreeWalk(x.GetRoot());
    cout << endl;
    cout << "Postorder Tree Walk : ";
    x.PostorderTreeWalk(x.GetRoot());
    cout << endl;
    //递归查找
    // if (x.TreeSearch(x.GetRoot(), 7) == nullptr)
    //     cout << "not found" << endl;
    // else
    //     cout << "found" << endl;
    // if (x.TreeSearch(x.GetRoot(), 3) == nullptr)
    //     cout << "not found" << endl;
    // else
    //     cout << "found" << endl;
    // //迭代查找
    // if (x.IterativeTreeSearch(x.GetRoot(), 7) == nullptr)
    //     cout << "7 not found" << endl;
    // else
    //     cout << "7 found" << endl;
    // if (x.IterativeTreeSearch(x.GetRoot(), 3) == nullptr)
    //     cout << "3 not found" << endl;
    // else
    //     cout << "3 found" << endl;
    //最大最小值
    // cout << "MaxNum : "
    //      << x.TreeMaxNum(x.GetRoot())->_key << endl;
    // cout << "MinNum : "
    //      << x.TreeMinNum(x.GetRoot())->_key << endl;
    //寻找根节点的前驱后继
    // cout << "Successor : "
    //      << x.Successor(x.GetRoot())->_key << endl;
    // cout << "Predecessor : "
    //      << x.Predecessor(x.GetRoot())->_key << endl;
    //删除根节点遍历
    // x.TreeDelete(x.GetRoot());
    // cout << "Inorder Tree Walk : ";
    // x.InorderTreeWalk(x.GetRoot());
    // cout << endl;
    // cout << "Preorder Tree Walk : ";
    // x.PreorderTreeWalk(x.GetRoot());
    // cout << endl;
    // cout << "Postorder Tree Walk : ";
    // x.PostorderTreeWalk(x.GetRoot());
    // cout << endl;
    cout << "TreeOut : " << endl;
    string name = "test";
    cout << x.GetRoot()->_key << endl;
    x.TreeOut(x.GetRoot(), "BST");
    return 0;
}