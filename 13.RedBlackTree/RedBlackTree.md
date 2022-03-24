### 基本性质

红黑树是一棵二叉搜索树，所以基本性质继续保留：

> 对树中的任意节点，左孩子关键字均小于其节点关键字，右孩子均大于等于其关键字。（等于的情况跟随实际定义效果）

除此之外又附加了其他性质使其更加稳定，树中每个节点除基本二叉搜索树包含的`key`，`left`，`right`，`p`之外，还包含`color`属性。

1. 每个节点颜色有红黑两种；
2. 根节点为黑色；
3. 每个叶子节点都为黑色；
4. 若当前节点为红色，那么其两个子节点为黑色；
5. 任意节点从自身到达叶子节点路径上经过的黑色节点数目是相等的。

满足上述要求的二叉搜索树就是一棵红黑树，此外这里描述与先前$BST$不同，红黑树的另一个规则是一个节点没有子节点或父节点，那么它将指向`NULL`，如下图所示，所以会得到第三条叶子节点都为黑色的结论。

![红黑树](C:\Users\SSW\Desktop\QQ图片20220324175533.png)

第五条性质带来的改变就是定义了新的概念`黑高`，表示某个节点$x$到达叶子节点`NULL`时所需要经过的黑色节点个数，记作$bh(x)$。

> 引理： 一棵有$n$个内部节点的红黑树高度至多为$2log_2(n+1)$。

从引理给出的性质了解到不同于$BST$，红黑树的高度（这里的高度是整体高度而并非定义的`黑高`）是和节点数量相联系并被限制的，引理的证明分为两步：

- 第一步证明以$x$为根的树至多包含$2^{bh(x)}-1$个内部节点（不含`NULL`）。

  [数学归纳法]

  当高度为$0$时，这棵树的`黑高`也为$0$，那么至多为$2^0-1=0$个内部节点；

  现有节点$x$包含两个孩子节点，那么至少当两个孩子节点都为红色时，总体节点数量至少为：
  $$
  2(2^{bh(x)-1}-1)+1=2^{bh(x)}-1
  $$
  ${bh(x)-1}$说明的是两个子节点都是红色，之后描述总体节点数量；

- 第二步有`从根节点出发到叶子节点最少有一半黑色节点`证明引理结论：

  有上述性质得到`黑高`$\ge\frac{h}{2}$
  $$
  \begin{aligned}
  n\ge&2^{\frac{h}{2}}-1\\
  log_2(n+1)\ge& \frac{h}{2}\\
  h\le&2log_2(n+1)
  \end{aligned}
  $$

### cpp模板元实现



可以由前面所说的“红黑树是一棵二叉搜索树”得出，实现红黑树的方法可以继承$BST$的部分代码，当红黑树失去颜色时，插入节点数据将退化为朴素的$BST$，所以可以发现红黑树相对继承代码后，需要修改颜色，更进一步地说，插入节点和删除节点的情况需要重载父类$BST$的相应方法。

#### 继承$BST$

```cpp
#include "../12.BinSerTree/binSerTree.h"
template <typename T>
class RBTree : public Tree<T>
{
private:
    TreeNode<T> *NIL = nullptr;
public:
    BRTree();
    BRTree(TreeNode<T> *_root);
    BRTree(T key);
    void InsertNode(T z);
    ... ...
};
```

新增`NULL`参数并在子类构造函数中添加父类的对应参数。

#### 添加属性

红黑树对于添加或删除节点的操作主要还是以先操作节点为主，之后通过检查修改节点颜色从而维护树的性质，首先需要在原二叉搜索树定义节点中添加新的属性以及颜色的枚举类型：

```cpp
enum COLOR
{
    RED,
    BALCK,
};
template <typename T>
struct TreeNode
{
    T _key;
    TreeNode<T> *_left;
    TreeNode<T> *_right;
    TreeNode<T> *_p;
    COLOR color;
    TreeNode(T data)
        : _key(data),
          _left(nullptr),
          _right(nullptr),
          _p(nullptr),
          color(RED) {}
};
```

初始定义为红色是为了后续的修正操作。

#### 旋转

仅仅是朴素的修正颜色可以看得出相当于是$BST$加入了颜色属性，所以同理红黑树给出了左旋与右旋的两个操作维护：

![旋转](C:\Users\SSW\Desktop\QQ图片20220324185408.png)

两个操作对称，根据$BST$性质可以看到左旋是将右侧大端保留，小端变换至新节点的大端上，交换两节点从而维护性质，右旋则是对称操作。但因为红黑树添加了`NULL`所以整体切换为：

```cpp
template <typename T>
void RBTree<T>::LeftRotate(TreeNode<T> *x)
{
    TreeNode<T> *y = x->_right;
    x->_right = y->_left;
    if (y->_left != NIL)
        y->_left->_p = x;
    y->_p = x->_p;
    if (x->_p == NIL)
        Tree<T>::GetRoot() = y;
    else if (x == x->_p->_left)
        x->_p->_left = y;
    else
        x->_p->_right = y;
    y->_left = x;
    x->_p = y;
}
```

#### 插入

插入操作除了因为添加整体`NULL`之外还需要针对颜色做一些调整：

```cpp
template <typename T>
void RBTree<T>::InsertNode(T z)
{
    TreeNode<T> *NowNode = new TreeNode<T>(z);
    TreeNode<T> *y = NIL;
    TreeNode<T> *x = Tree<T>::GetRoot();
    while (x != NIL){...}
    ...
    NowNode->_left = NIL;
    NowNode->_right = NIL;
    NowNode->color = RED;
    InsertFixup(NowNode);
}
```

可以注意到添加了默认颜色为红色的操作与`Fixup`方法，最后两行的目标是维护树的性质。

插入后的颜色位置相对处理主要分为六种情况，由于左右孩子节点对称，所以分为三种，详细可以分解为（左端举例子）：

##### [情况1]

<img src="C:\Users\SSW\Desktop\第一种情况.png" style="zoom:50%;" />

 $z$初始定义为红色，当其祖父节点存在且父节点和叔节点（祖父节点的另一个孩子）均为红色时，无论$z$节点是左孩子还是右孩子，均可以通过修改父节点和叔节点颜色为黑色、修改祖父节点为红色解决问题：

- 修改父节点和叔节点为黑色的原因是性质4（父节点为红色，子节点均为黑色）；
- 修改祖父节点为红色的原因是性质5（每条根节点到叶子节点路径上黑色节点数量保持相等）；

##### [情况2$or$3]

<img src="C:\Users\SSW\Desktop\第二三种情况.png" style="zoom:50%;" />

同样是在左侧，叔节点为黑色的情况下：

- 比较容易的情况3中，需要在祖父节点做右旋操作并将祖父节点颜色变为红，父节点颜色变为黑，这样维护了性质4；
- 相对更繁琐的情况2中，需要将当前位置移至父节点做左旋操作后这样使得情况2变为更好处理的情况3。

以上情况基于父节点为红色且祖父节点存在的条件下，若父节点不为红色也就不需要讨论这个问题了，若祖父节点不存在，那么就是父节点为根节点的情况，无论怎么样最后都将根节点设置为黑色即维护了树的性质，这里更深得意义讲可以参考`循环不变式`。

实现方法较长给出左边三类情况的讨论（所有代码均上传至$Github$，点击阅读原文即可）：

```cpp
template <typename T>
void RBTree<T>::InsertFixup(TreeNode<T> *z)
{
    while (z->_p->color == RED)
    {
        if (z->_p == z->_p->_p->_left)
        {
            TreeNode<T> *y = z->_p->_p->_right;
            if (y->color == RED)
            {
                z->_p->color = BALCK;
                y->color = BALCK;
                z->_p->_p->color = RED;
                z = z->_p->_p;
            }
            else
            {
                if (z == z->_p->_right)
                {
                    z = z->_p;
                    LeftRotate(z);
                }
                z->_p->color = BALCK;
                z->_p->_p->color = RED;
                RightRotate(z->_p->_p);
            }
        }
        else if (z->_p == z->_p->_p->_right)
        //对称方法
    }
    SetRootColor(BALCK);
}
```

