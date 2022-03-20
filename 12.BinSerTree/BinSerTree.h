/*
 * @Descripttion:
 * @Author: ssw
 * @Date: 2022-03-14 19:16:32
 * @LastEditors: ssw
 * @LastEditTime: 2022-03-20 18:55:23
 */
#include <iostream>
using namespace std;
using namespace std;

template <typename T>
struct TreeNode
{
    T _key;
    TreeNode<T> *_left;
    TreeNode<T> *_right;
    TreeNode<T> *_p;
    TreeNode(T data)
        : _key(data), _left(nullptr), _right(nullptr), _p(nullptr) {}
};

template <typename T>
class Tree
{
private:
    TreeNode<T> *root;

public:
    Tree() : root(nullptr) {}
    Tree(TreeNode<T> *_root) : root(_root) {}
    Tree(T key) : root(new TreeNode<T>(key)) {}

    TreeNode<T> *GetRoot() const { return this->root; }
    void InsertNode(T z);
    void InorderTreeWalk(TreeNode<T> *_root) const;
    void PreorderTreeWalk(TreeNode<T> *_root) const;
    void PostorderTreeWalk(TreeNode<T> *_root) const;
    TreeNode<T> *TreeSearch(TreeNode<T> *x, T k) const;
    TreeNode<T> *IterativeTreeSearch(TreeNode<T> *x, T k) const;
    void Translant(TreeNode<T> *u, TreeNode<T> *v);
    void TreeDelete(TreeNode<T> *z);
    TreeNode<T> *TreeMinNum(TreeNode<T> *x) const
    {
        while (x->_left != nullptr)
            x = x->_left;
        return x;
    }
    TreeNode<T> *TreeMaxNum(TreeNode<T> *x) const
    {
        while (x->_right != nullptr)
            x = x->_right;
        return x;
    }

    TreeNode<T> *Successor(TreeNode<T> *x) const
    {
        if (x->_right != nullptr)
            return TreeMinNum(x->_right);
        TreeNode<T> *y = x->_p;
        while (y != nullptr && x == y->_right)
        {
            x = y;
            y = x->_p;
        }
        return y;
    }
    TreeNode<T> *Predecessor(TreeNode<T> *x) const
    {
        if (x->_left != nullptr)
            return TreeMaxNum(x->_left);
        TreeNode<T> *y = x->_p;
        while (y != nullptr && x == y->_left)
        {
            x = y;
            y = x->_p;
        }
        return y;
    }
};

template <typename T>
void Tree<T>::InsertNode(T z)
{
    TreeNode<T> *NowNode = new TreeNode<T>(z);
    TreeNode<T> *y = nullptr, *x = this->root;
    // y保留当前节点，判断插入节点的数据，小于当前节点放左子树，大于当前放右子树
    // 直到指到空节点
    while (x != nullptr)
    {
        y = x;
        if (NowNode->_key < x->_key)
            x = x->_left;
        else
            x = x->_right;
    }
    // 插入节点，如果是空节点直接放根节点，如果小于当前节点放左子树，大于当前放右子树
    NowNode->_p = y;
    if (y == nullptr)
        this->root = NowNode;
    else if (NowNode->_key < y->_key)
        y->_left = NowNode;
    else
        y->_right = NowNode;
}

template <typename T>
void Tree<T>::InorderTreeWalk(TreeNode<T> *_root) const
{
    if (_root != nullptr)
    {
        InorderTreeWalk(_root->_left);
        cout << _root->_key << ' ';
        InorderTreeWalk(_root->_right);
    }
}

template <typename T>
void Tree<T>::PreorderTreeWalk(TreeNode<T> *_root) const
{
    if (_root != nullptr)
    {
        cout << _root->_key << ' ';
        PreorderTreeWalk(_root->_left);
        PreorderTreeWalk(_root->_right);
    }
}

template <typename T>
void Tree<T>::PostorderTreeWalk(TreeNode<T> *_root) const
{
    if (_root != nullptr)
    {
        PostorderTreeWalk(_root->_left);
        PostorderTreeWalk(_root->_right);
        cout << _root->_key << ' ';
    }
}

template <typename T>
TreeNode<T> *Tree<T>::TreeSearch(TreeNode<T> *x, T k) const
{
    if (x == nullptr || k == x->_key)
        return x;
    if (k < x->_key)
        return TreeSearch(x->_left, k);
    else
        return TreeSearch(x->_right, k);
}

template <typename T>
TreeNode<T> *Tree<T>::IterativeTreeSearch(TreeNode<T> *x, T k) const
{
    while (x != nullptr && k != x->_key)
    {
        if (k < x->_key)
            x = x->_left;
        else
            x = x->_right;
    }
    return x;
}

template <typename T>
void Tree<T>::Translant(TreeNode<T> *u, TreeNode<T> *v)
{
    if (u->_p == nullptr)
        root = v;
    else if (u == u->_p->_left)
        u->_p->_left = v;
    else
        u->_p->_right = v;
    if (v != nullptr)
        v->_p = u->_p;
}

template <typename T>
void Tree<T>::TreeDelete(TreeNode<T> *z)
{
    if (z->_left == nullptr)
        Translant(z, z->_right);
    else if (z->_right == nullptr)
        Translant(z, z->_right);
    else
    {
        TreeNode<T> *y = TreeMinNum(z->_right);
        if (y->_p != z)
        {
            Translant(y, y->_right);
            y->_right = z->_right;
            y->_right->_p = y;
        }
        Translant(z, y);
        y->_left = z->_left;
        y->_left->_p = y;
    }
}