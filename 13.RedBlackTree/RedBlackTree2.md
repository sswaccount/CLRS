### 绘制红黑树函数修正

在基类中添加了针对红黑树的颜色显示`flag`布尔参数，且采用队列出队时刻节点输出相应颜色描述，确保数据不重复增加`dot`文件数据量，同理针对`NIL`指针特殊对待使其颜色描述输出一次。

```cpp
TreeOut(TreeNode<T> *x, string name, bool flag)
...
cout << "digraph Tree{" << endl;
queue<TreeNode<T> *> q;
if (x->_p != nullptr)
    cout << x->_key << "->" << x->_p->_key << endl;
q.push(x);
while (q.size())
{
    TreeNode<T> *tmp = q.front();
    q.pop();
    if (flag && tmp->_key != -1)
    {
        cout << tmp->_key 
            << " [style=filled,fillcolor=";
        if (tmp->color == RED)
            cout << "lightcoral,color=red]\n";
        else
            cout << "grey49,color=black]\n";
    }
    if (tmp->_left)
    {
        cout << tmp->_key << "->" 
            << tmp->_left->_key << endl;
        q.push(tmp->_left);
    }
    if (tmp->_right)
    {
        cout << tmp->_key << "->" 
            << tmp->_right->_key << endl;
        q.push(tmp->_right);
    }
}
if (flag)
    cout << "-1 [style=filled,fillcolor=grey49,color=black]\n";
cout << "}" << endl;
...
```

添加本地可视化后能够针对插入数据和删除数据，子类直接调用`TreeOut()`方法加入红黑树布尔参数即可：

<img src="E:\2022\IA\13.RedBlackTree\before.png" style="zoom:50%;" />

添加节点`11`后调用`InsertFixup()`方法使得全局变化后结果为：

<img src="E:\2022\IA\13.RedBlackTree\after.png" style="zoom:50%;" />

这里由于全局展示了`NIL`节点所以未使用二叉树的格式化版式。

这里提供三个描述`Graphviz`的简要语法以及相关美化操作的网站：

```
Graphviz详细操作介绍：https://leojhonsong.github.io/zh-CN/2020/03/12/Graphviz%E7%AE%80%E8%A6%81%E8%AF%AD%E6%B3%95/
美化Graphviz：https://sketchviz.com/new
数据结构可视化：https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
```

### 删除节点

重温红黑树五条基本性质：

1. 每个节点颜色有红黑两种；
2. 根节点为黑色；
3. 每个叶子节点都为黑色；
4. 若当前节点为红色，那么其两个子节点为黑色；
5. 任意节点从自身到达叶子节点路径上经过的黑色节点数目是相等的。

#### `Transplant()`

类比$BST$方法删除节点也同样需要`Transplant`方法使得节点被替换，有改动的是红黑树加入的`NIL`节点，所以：

```cpp
template <typename T>
void RBTree<T>::Transplant(TreeNode<T> *u, TreeNode<T> *v)
{
    if (u->_p == NIL)
        Tree<T>::SetRoot(v);
    else if (u == u->_p->_left)
        u->_p->_left = v;
    else
        u->_p->_right = v;
    v->_p = u->_p;
}
```

其中根节点的父节点指向`NIL`所以最后无论`u`是否为根节点都需要做一个指向，同时`Transplant()`方法的替换主要范围是替换"上部分内容"，或者说是维护被替换节点的父节点与替换节点的交互指针信息。

#### `Delete()`

同比参考`BST`的删除节点，红黑树的方法相比会更加复杂，主要更多的是维护五条主要性质，从而确保引理描述的高度上限。

维护颜色的主要目的是确定是否进入最终的`DeleteFixup()`方法，删除过程分为两个主要方向：

- 当被删除节点不同时存在两个孩子节点时，维护的`x`是指填充至删除节点的子树或者说子节点（若`x`为`NIL`也有可能这种情况下维护的同样算是一类特殊的子节点），维护的`y`是被删除的节点，可以看到同时也记录了`y`的原始颜色；

- 当删除节点存在两个子节点时，就需要查找被删除节点的右子树的最小节点`y`（被删除节点的后继节点），同时记录了其节点颜色，会出现两种小情况：

  1. 一种是后继节点的父节点就是被删除节点，此时因为这是最小节点所以`y`肯定没有左孩子，记录`y`的右孩子为`x`（同样可能是空），这时不需要其他操作，因为替换后`x`和`y`的相对位置没有改变。
  2. 另一种是`y`在更下方的位置，这时需要将`x`填补至`y`原先的位置同时维护父子节点指针信息。

  最后调用`Transplant()`方法把`x`替换`y`，或者说是维护`y`和`x`父节点的相关信息，即便父节点为`NIL`，之后维护的就是`y`和`z`的子节点的指针信息。

```cpp
template <typename T>
void RBTree<T>::TreeDelete(TreeNode<T> *z)
{
    TreeNode<T> *y = z;
    TreeNode<T> *x = nullptr;
    COLOR y_originalcolor = y->color;
    if (z->_left == NIL)
    {
        x = z->_right;
        Translant(z, z->_right);
    }
    else if (z->_right == NIL)
    {
        x = z->_left;
        Translant(z, z->_left);
    }
    else
    {
        y = Tree<T>::TreeMinNum(z->_right);
        y_originalcolor = y->color;
        x = y->_right;
        if (y->_p == z)
            x->_p = y;
        else
        {
            Translant(y, y->_right);
            y->_right = z->_right;
            y->_right->_p = y;
        }
        Translant(z, y);
        y->_left = z->_left;
        y->_left->_p = y;
        y->color = z->color;
    }
    if (y_originalcolor = BALCK)
        DeleteFixup(x);
}
```

最终依据`y_originalcolor`（`y`节点的最开始的颜色）来确定是否需要再次维护树中节点的颜色关系，这里还是分为两大类问题讨论：

- 当被删除节点不同时存在两个孩子节点时，上面提到`y`的颜色其实就维护的是删除的节点颜色，如果节点为黑色意味着违背了`性质5`，因为无论哪个节点替代了原先的黑色节点，替换后根节点到其子树的经历的黑色节点个数都会被减少1；此外如果被删除节点是根节点的话，`x`节点的颜色不能被保证一定是黑色，所以可能会违背`性质2`。
- 当删除节点存在两个子节点时，`y`的原始颜色信息被提前保留，之后被替换到`z`的位置，并且颜色被更新为`z`的颜色，所以不用考虑`z`，但是如果`y`原始是黑色的，那么它的父节点和子节点的颜色不会被保证同时不为红色，这将违背`性质4`。

#### `DeleteFixup()`

所以上述解释说明了什么情况下要调用`DeleteFixup()`方法，但还要明白为什么参数传入的是`x`。

由于`y`的问题所以为了维护根节点到子节点的`性质5`，包含`x`的这条路径就需要多一个黑色节点贡献值，但如果是上面所述被删除节点没有两个孩子的情况，那么`y`节点传入`DeleteFixup()`方法也就变得没有意义，现在压力给到了`x`节点，所以`x`节点有两种可能性：

- `x`节点信息显示为红色，那么它自身其实背负着一个黑节点的任务，所以参考书中把这个点的状态叫做“红黑节点”；
- `x`节点信息显示为黑色，同样在这个任务下，它被称为“双黑节点”。

有如此的情况违反了`性质1`，因为`x`包含了一个以上的颜色属性，所以该方法的目的就是解决这个问题。

<img src="E:\2022\IA\13.RedBlackTree\case4.png" style="zoom:50%;" />

其中解决问题分为四种情况，同样类比红黑树的插入维护颜色方法，这四种情况和插入维护的三种方法都是不完全独立的问题，这个问题同样因为左右子树的对称，所以这里只讨论左子树的维护问题：

先对颜色做一个解释：

- 黑色节点颜色信息为黑色
- 浅灰色节点颜色信息自由，因为和问题讨论无关
- 深灰色节点颜色信息为红色
- 标记`x`节点不论显示什么颜色，都会隐含着一个黑色节点的贡献的任务，除非`x`指向深灰色节点，则可以把其变为黑色，贡献就完成了。

然后阐述这四种情况（大前提都是`x`为黑色，若`x`为红色直接赋黑色即可）：

1. [兄弟节点为红色]因为想把隐含的黑色贡献到红色节点，所以不能对父节点下手（当父亲节点为黑色时），对应的情况1就是这样，为了更好的找机会贡献，如果兄弟节点为红色就要对其好好利用，将父亲节点和兄弟节点颜色互换且在父节点做左旋操作，这样得到的树中父节点为红色就会变换到情况2~4。

2. [兄弟节点为黑色，兄弟的两个孩子也是黑色]因为性质4，所以这种情况可以很顺利地将兄弟节点变为红色，之后把父节点变黑解决了`x`的隐藏贡献问题。

   但这是在父节点为红色的情况下会得到解决，若父节点为黑色，那么压力给到了父节点，因为`x`位置上升到父节点，原先的父节点需要解决隐含黑色人物的问题，这时问题就又回归了需要调用`DeleteFixup()`方法的情况（循环操作即可），但如果父节点或者迭代的节点为根节点时问题同样也就被解决了，因为根节点黑色的多少不会影响其他子树了（没有其他子树）。

3. [兄弟节点为黑色，兄弟左孩子为红，兄弟右孩子为黑]交换兄弟节点和兄弟节点做孩子的颜色之后对兄弟节点做右旋，这时的`性质5`同样没有被改变，可以从拉丁字母到图中根节点的变换前后黑色节点数量来验证。

   但问题依旧没有被解决，而是转化到了情况4。

4. [兄弟节点为黑色，兄弟右孩子为红]将兄弟节点定义为红，父节点和兄弟的右孩子定义为黑，在父节点上做左旋，这种情况得到的结果就是为`x`这条分支添加了一个黑色贡献，而右子树不变，这是问题也得到了解决。

只给出左侧情况，其余情况阅读原文在$Github$中获得。

```cpp
template <typename T>
void RBTree<T>::DeleteFixup(TreeNode<T> *x)
{
    while (x != Tree<T>::GetRoot() && x->color == BALCK)
    {
        if (x == x->_p->_left)
        {
            TreeNode<T> *w = x->_p->_right;
            if (w->color == RED)
            {//情况1
                w->color = BALCK;
                x->_p->color = RED;
                LeftRotate(x->_p);
                w = x->_p->_right;
            }
            if (w->_left->color == BALCK && w->_right->color == BALCK)
            {//情况2
                w->color = RED;
                x = x->_p;
            }
            else
            {
                if (w->_right->color == BALCK)
                {//情况3
                    w->_left->color = BALCK;
                    w->color = RED;
                    RightRotate(w);
                    w = w->_p->_right;
                }//情况4
                w->color = x->_p->color;
                x->_p->color = BALCK;
                w->_right->color = BALCK;
                LeftRotate(x.p);
                x = Tree<T>::GetRoot();
            }
        }
        else{...}
    }
}
```

