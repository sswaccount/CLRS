<!--
 * @Descripttion: 
 * @Author: ssw
 * @Date: 2022-03-20 20:09:48
 * @LastEditors: ssw
 * @LastEditTime: 2022-03-20 20:47:15
-->

### 二叉搜索树

#### 定义节点

每一个节点就是一个对象，其中主要包含键值、左右孩子指针和父级指针，更泛泛的说还可以包含其他数据对象。

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

#### 依据主要性质构建BST

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

