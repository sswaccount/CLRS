/*
 * @Descripttion:
 * @Author: ssw
 * @Date: 2022-03-24 14:46:29
 * @LastEditors: ssw
 * @LastEditTime: 2022-03-25 23:52:20
 */
#include <iostream>
#include "../12.BinSerTree/binSerTree.h"
using namespace std;
using namespace std;

template <typename T>
class RBTree : public Tree<T>
{
private:
    // TreeNode<T> *NIL = new TreeNode<T>(nullptr);
    TreeNode<T> *NIL = new TreeNode<T>();

public:
    BRTree();
    BRTree(TreeNode<T> *_root);
    BRTree(T key);
    void InsertNode(T z);
    void InsertFixup(TreeNode<T> *z);
    void RightRotate(TreeNode<T> *x);
    void LeftRotate(TreeNode<T> *x);
    void Translant(TreeNode<T> *u, TreeNode<T> *v);
};

template <typename T>
void RBTree<T>::LeftRotate(TreeNode<T> *x)
{
    TreeNode<T> *y = x->_right;
    x->_right = y->_left;
    if (y->_left != NIL)
        y->_left->_p = x;
    y->_p = x->_p;
    if (x->_p == NIL)
        Tree<T>::SetRoot(y);
    else if (x == x->_p->_left)
        x->_p->_left = y;
    else
        x->_p->_right = y;
    y->_left = x;
    x->_p = y;
}

template <typename T>
void RBTree<T>::RightRotate(TreeNode<T> *y)
{
    TreeNode<T> *x = y->_left;
    y->_left = x->_right;
    if (x->_right != NIL)
        x->_right->_p = y;
    x->_p = y->_p;
    cout << "RR : " << x->_p->_key << endl;
    if (y->_p == NIL)
        Tree<T>::SetRoot(x);
    else if (y == y->_p->_left)
        y->_p->_left = x;
    else
        y->_p->_right = x;
    x->_right = y;
    y->_p = x;
}
template <typename T>
void RBTree<T>::InsertNode(T z)
{

    TreeNode<T> *NowNode = new TreeNode<T>(z);
    TreeNode<T> *y = NIL;
    TreeNode<T> *x = Tree<T>::GetRoot();

    // cout << "insert test 1" << endl;
    // 如果构造函数是空节点会被赋值空指针
    // 如果单纯检验是否为NIL不全面
    while (x && x != NIL)
    {
        // cout << "find null" << endl;
        y = x;
        if (NowNode->_key < x->_key)
            x = x->_left;
        else
            x = x->_right;
    }
    // cout << "insert test 2" << endl;
    NowNode->_p = y;
    if (y == NIL)
        Tree<T>::SetRoot(NowNode);
    else if (NowNode->_key < y->_key)
        y->_left = NowNode;
    else
        y->_right = NowNode;

    // cout << "inside inorder : ";
    // Tree<T>::InorderTreeWalk(Tree<T>::GetRoot());
    // cout << endl;
    // cout << nullptr << endl;
    // cout << "insert test 3" << endl;
    NowNode->_left = NIL;
    NowNode->_right = NIL;
    NowNode->color = RED;
    InsertFixup(NowNode);
}

template <typename T>
void RBTree<T>::InsertFixup(TreeNode<T> *z)
{
    cout << "fix : " << z->_key << endl;
    // if()
    while ((z->_p != NIL) && z->_p->color == RED)
    {
        cout << "ddd" << endl;
        if ((z->_p->_p) && (z->_p == z->_p->_p->_left))
        {
            cout << "xxx11111111" << endl;
            TreeNode<T> *y = z->_p->_p->_right;
            if (y->color == RED)
            {
                cout << "1.1" << endl;
                z->_p->color = BALCK;
                y->color = BALCK;
                z->_p->_p->color = RED;
                z = z->_p->_p;
            }
            else
            {
                if (z == z->_p->_right)
                {
                    cout << "1.2" << endl;
                    z = z->_p;
                    LeftRotate(z);
                }
                cout << "------------" << endl;
                cout << z->_key << endl;
                cout << z->_p->_key << endl;
                cout << "------------" << endl;
                cout << "1.3" << endl;
                z->_p->color = BALCK;
                z->_p->_p->color = RED;
                RightRotate(z->_p->_p);
                cout << Tree<T>::GetRoot()->_key << endl;
            }
            cout << "over xxx111111111" << endl;
        }
        else if ((z->_p->_p) && z->_p == z-> _p->_p->_right)
        {
            cout << "xxx22222222" << endl;
            TreeNode<T> *y = z->_p->_p->_left;
            if (y->color == RED)
            {
                cout << "2.1" << endl;
                z->_p->color = BALCK;
                y->color = BALCK;
                z->_p->_p->color = RED;
                z = z->_p->_p;
            }
            else
            {
                if (z == z->_p->_left)
                {
                    cout << "2.2" << endl;
                    z = z->_p;
                    RightRotate(z);
                }
                cout << "2.3" << endl;
                z->_p->color = BALCK;
                z->_p->_p->color = RED;
                LeftRotate(z->_p->_p);
            }
            cout << "over xxx2222222222222" << endl;
        }
    }
    cout << "fixok : " << z->_key << endl;
    Tree<T>::SetRootColor(BALCK);
}

template <typename T>
void RBTree<T>::Translant(TreeNode<T> *u, TreeNode<T> *v)
{
    if (u->_p == NIL)
        SetRoot(v);
    else if (u == u->_p->_left)
        u->_p->_left = v;
    else
        u->_p->_right = v;
    v->_p = u->_p;
}