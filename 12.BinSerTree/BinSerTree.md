### 二叉搜索树

二叉搜索树（Binary Search Trees，BST）是一种经典的数据结构，它既有链表的快速插入与删除操作的特点，又有数组快速查找的优势，所以应用十分广泛。

涉及本文的全部代码与实例已全部上传至[Github](https://github.com/sswaccount/CLRS/tree/master/12.BinSerTree)。

#### 定义节点

每一个节点就是一个对象，其中主要包含键值、左右孩子指针和父亲指针，更泛泛地说还可以包含其他数据对象。

所以首先定义节点结构：

```cpp
template <typename T>
struct TreeNode
{
    T _key;
    TreeNode<T> *_left;
    TreeNode<T> *_right;
    TreeNode<T> *_p;
    TreeNode(T data)
        : _key(data), 
        _left(nullptr), 
        _right(nullptr), 
        _p(nullptr) {}
};
```

#### 性质以及创建BST对象

$\forall 节点x\in BST,x所有左孩子.key\leq x.key,x所有右孩子.key\geq x.key$

构建BST需要先创建$Tree$对象:

```cpp
template <typename T>
class Tree
{
private:
    TreeNode<T> *root;

public:
    Tree() : root(nullptr) {}
    Tree(TreeNode<T> *_root) : root(_root) {}
    Tree(T key) : root(new TreeNode<T>(key)) {}
    TreeNode<T> *GetRoot() const 
    { 
        return this->root; 
    }    
}
```

定义私有数据根节点所以为了访问添加了`GetRoot`方法。其次提供了三种构造函数方法：

1. 无参数构建空树
2. 输入参数为结构对象，直接赋值根节点。
3. 输入参数为基本数据类型，内部转化为结构对象。

#### 插入节点

根据上述BST性质描述，插入过程调用函数时需要修改BST对象与插入节点的一些属性。

首先输入作为常规数据类型，之后创建节点数据对象，内部逻辑根据性质可以解释为：

1. 首先从根节点开始找到合适的位置：待插入节点$<$当前节点则遍历左孩子，反之则遍历右孩子直到当前节点为空；
2. 将待插入节点父亲指针指向当前节点，然后将待插入节点放到该放的地方。

```cpp
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
```

#### 前中后序遍历

前中后序遍历的三种方法都是使用递归的方式遍历所有子节点，最关键的区别就是根节点、左孩子节点、右孩子节点的访问顺序，而前中后序遍历就表明了根节点的相对位置：

- 前序遍历：根节点，左孩子，右孩子；

- 中序遍历：左孩子，根节点，右孩子；

- 后序遍历：左孩子，右孩子，根节点。

```cpp
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
void Tree<T>::PostorderTreeWalk(TreeNode<T> *_root) const
{
    if (_root != nullptr)
    {
        PostorderTreeWalk(_root->_left);
        PostorderTreeWalk(_root->_right);
        cout << _root->_key << ' ';
    }
}
```

#### 查找操作

查找整个树或某子树的某个键值节点时，依据的仍然是比较`查询节点`和`当前访问到的节点`的大小关系，有四种情况：

- `查询节点`$<$`当前访问到的节点`：向左子树查询；
- `查询节点`$>$`当前访问到的节点`：向右子树查询；
- `查询节点`$=$`当前访问到的节点`：返回当前节点指针；
- `当前访问到的节点`$=$`NULL`：返回空指针。

给出递归与迭代两种方式查询：

```cpp
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
```

#### 最小值最大值

由于：子树的左子树所有元素$\leq$子树根节点元素，子树的右子树所有元素$\geq$子树根节点元素。

所以可以描述出查询最小最大值的方法分别为：向左或向右递归至根节点。

```cpp
template <typename T>
TreeNode<T> *TreeMinNum(TreeNode<T> *x) const
{
    while (x->_left != nullptr)
        x = x->_left;
    return x;
}
template <typename T>
TreeNode<T> *TreeMaxNum(TreeNode<T> *x) const
{
    while (x->_right != nullptr)
        x = x->_right;
    return x;
}
```

#### 后继前驱

- 前驱：比当前查询节点键值小的第一个元素；
- 后继：比当前查询节点键值大的第一个元素。

两个信息都是对称的所以对后继做解释：

1. 若该节点存在右孩子，那么由于性质“子树的右子树所有元素$\geq$子树根节点元素”可以得到节点的后继为右子树的最小值，可以由上面的方式得到；

2. 反之该节点不存在左孩子，但该节点为根节点时，由于性质“子树的左子树所有元素$\leq$子树根节点元素”得到该点在树上没有后继；

3. 除此之外，则还有可能是该节点作为左孩子或右孩子：

   - 作为右孩子时可以发现，当前节点大于父亲节点与父亲节点的左孩子（若左孩子存在）
   - 作为左孩子时，父亲节点将是第一个大于该节点的节点，因为父亲的右孩子将会全部大于等于父亲节点

   所以这类情况需要向上查询直到作为左孩子出现时，当前查询节点的父亲节点将作为后继。

```cpp
template <typename T>
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
template <typename T>
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
```

##### 删除节点

删除某一节点将会有三种可能性：

1. 待删除节点无孩子节点：直接删除
2. 待删除结点只有一个孩子节点：将孩子节点替换至当前节点
3. 待删除结点有两个孩子节点：找到该节点的后继节点并与之做交换

**首先**，可以看出删除过程最常用的方法是交换两个节点的位置，但在程序中还需要维护其指针信息，所以解释为`Translant`方法，传入参数为`*u`:待替换结点指针、`*v`:替换结点指针，分为几种情况：

- `u`为`根节点`，则直接将`根节点`指向`v`；
- `u`为其父节点的左（右）孩子，将其父节点的左（右）指针指向`v`；

最终维护`v`节点的父亲节点信息。

```cpp
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
```

之后进行删除的相关操作：

- 若左孩子为空：交换右孩子和当前节点；

- 若右孩子为空而左孩子非空：交换左孩子和当前节点；

- 存在两个孩子时

  <img src="C:\Users\SSW\AppData\Roaming\Typora\typora-user-images\image-20220321012838116.png" alt="image-20220321012838116" style="zoom:45%;" />

  查找右子树的最小值（当前根节点的后继节点）的指针`y`，当`y`的深度较深（父节点不是待删除节点时），需要额外操作==将`y`的右孩子替换到`y`并维护相关信息==，之后替换`y`和待删除结点在维护相关信息。

```cpp
template <typename T>
void Tree<T>::TreeDelete(TreeNode<T> *z)
{
    if (z->_left == nullptr)
        Translant(z, z->_right);
    else if (z->_right == nullptr)
        Translant(z, z->_left);
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
```

