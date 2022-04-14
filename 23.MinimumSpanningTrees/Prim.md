### Prim算法

中文被称为普利姆算法，作为一种最小生成树的常见算法，与上节所介绍的$Kruskal$算法存在的区别为：

- $Kruskal$算法：将边权从小到大排序后选择作为两个树的连接边的边加入集合作为最小生成树边集；
- $Prim$算法：一棵最小生成树中的所有连接不同树木的临边选择边权最小的边加入集合作为最小生成树边集合；

上述两个方法前者更倾向于以边位主连接不同森林，后者则更倾向于以一颗树开始找不同森林的边，如此操作的终止条件都为：

- 图中没有一个点是没有被操作过的。

用简单的方法形容$Kruskal$方法为散点聚少成多，$Prim$方法则为单点逐渐壮大；

综上所述$Prim$算法的主要操作流程为：

1. 从图中任意的根节点开始作为集合$A$；
2. 在$A$集合以及其他点集合之间找到一条轻量级边加入$A$中；
3. 没有其他点集合（算法终止），$A$为一颗最小生成树；

其中第二步寻找轻量级边的过程是一个动态排序并取最小值的过程，二叉最小优先队列是一个极佳的选择，但要注意优先队列维护的是$A$集合外所有点距离最小生成树$A$距离最小的边值`Key`。

当将点加入集合时，标记之余更重要的是将加入的边的新临边加入优先队列，这里我们基于上一节的优先队列思想创建一个关于节点的优先队列类：

#### 优先队列类

因为基于节点，所以首先定义结构体：

```cpp
struct Vertex
{
    char _name;
    Vertex *_pi;
    int _key;
    NextNode *_first;
    Vertex(char name = ' ')
        : _name(name),
          _pi(nullptr),
          _key(1000),
          _first(nullptr) {}
    bool operator<(Vertex x)
    {
        return _key < x._key;
    }
    bool operator>(Vertex x)
    {
        return _key > x._key;
    }
};
```

可以发现结构基本基于22章内容，其中增加了便于比较的运算符重载过程。

如果要完成的模拟出基于原理的运算流程，那么会发现使用`HeapDecreaseKey()`方法进行对某键值进行更改时，键值也需要做一个哈希维护，来确保过程中能够用`name`属性定位到二叉优先队列目标树中的节点：

```cpp
class Heap
{
private:
    vector<Vertex> data;
    int heap_size = 0;
    map<char, int> indexfind;
    void MinHeapify(int i)
    {
        int l = Left(i);
        int r = Right(i);
        int largest = i;
        if (l <= heap_size && data[l] < data[i])
            largest = l;
        else
            largest = i;
        if (r <= heap_size && data[r] < data[largest])
            largest = r;
        if (largest != i)
        {
            swap(data[i], data[largest]);
            swap(indexfind[data[i]._name], indexfind[data[largest]._name]);
            MinHeapify(largest);
        }
    }
public:
    Heap(vector<Vertex> vT)
    {
        data.push_back(Vertex(' '));
        //插入数据维护哈希name信息：
        for (auto i : vT)
        {
            data.push_back(i);
            indexfind[i._name] = ++heap_size;
        }
    }
    void BuildMinHeap()
    {
        for (int i = heap_size >> 1; i >= 1; i--)
            MinHeapify(i);
    }
    ...
};
```

通过上述构造函数中的哈希表维护索引，之后进行建立优先队列，如果需要交换节点信息则默认连同索引值一起做交换。

```cpp
int HeapExtractMin()
{
    int key = data[1]._key;
    swap(indexfind[data[1]._name], indexfind[data[heap_size]._name]);
    data[1] = data[heap_size--];
    MinHeapify(1);
    return key;
}
void HeapDecreaseKey(char name, int key)
{
    int i = indexfind[name];
    if (key > data[i]._key)
        return;

    data[i]._key = key;
    while (i > 1 && data[Parent(i)] > data[i])
    {
        swap(data[i], data[Parent(i)]);
        swap(indexfind[data[i]._name], indexfind[data[Parent(i)]._name]);
        i = Parent(i);
    }
}
```

此外删除节点信息也应做同步的索引调整，其他逻辑等价于优先队列操作。

#### 主体操作

前面提到$Prim$算法提供了一个根节点开始计算，所以说默认根节点的`Key`值被赋`0`，前置节点为空，其余点的`Key`被赋值正无穷，此处为理想化的”正无穷“。

![](C:\Users\SSW\Desktop\Prim.png)

此后需要将图中的节点对象复制到优先队列中，伪代码第9行判断是否在集合中除了循环外在语言中实现中更好的方法是用标记数组判断来优化时间，之后需要注意的是节点复制后并不会同步到优先队列中，所以需要进行扩展（节点更新与优先队列对应键值更新）。

程序表达为：

```cpp
void Graph::MST_PRIM(char root)
{
    Gprime[root - 'a']._key = 0;

    Heap Q = Heap(Gprime);
    Q.BuildMinHeap();
    vector<bool> judge(V, false);
    for (auto i : Gprime)
    {
        judge[i._name - 'a'] = true;
    }
    map<pair<int, int>, int> EdgeIndex(G.begin(), G.end());
    for (auto i : G)
        EdgeIndex[{i.first.second, i.first.first}] = i.second;

    while (!Q.empty())
    {
        Vertex u = Q.HeapMinimum();
        Q.HeapExtractMin();
        int index = u._name - 'a';
        judge[index] = false;
        if (u._name != root)
            cout << u._first->adjvex << ' '
                 << u._name << ' '
                 << u._key << endl;
        for (auto v = Gprime[index]._first; v; v = v->NEXT)
        {
            int next_index = v->adjvex - 'a';
            int w = EdgeIndex[{index + 1, next_index + 1}];
            if (judge[next_index] && w < Gprime[next_index]._key)
            {
                Gprime[next_index]._pi = &u;
                Gprime[next_index]._key = w;
                Q.HeapDecreaseKey(Gprime[next_index]._name, w);
            }
        }
    }
}
```

很显然程序表达会更加繁琐，尤其是增加了临边键值对的维护，因为哈希表的查询时间，此处的维护不作为优化而是一种操作的便捷化，当图较小时更简易使用邻接矩阵作为判断。

![](C:\Users\SSW\Desktop\流程.png)

最终基于优先队列实现的$Prim$算法通过样例实现为：

```
a b 4
a h 8
h g 1
c f 2
b c 4
h i 2
c d 7
d e 9
```

存在差异的原因是该处描述的二叉优先队列中优先级排列只包含`Key`第一关键字，等号情况并不依赖字典序但结果不变依旧满足最小生成树。

#### 分析

##### 循环不变式

该过程的循环不变式维护的性质有三个：

1. 集合$A\{(v,v.\pi)\}$中只包含除了定义根节点和队列中节点的其余节点（$v\in V-root-Q$）。
2. 已经加入最小生成树的点集合为$V-Q$。
3. 任意一个优先队列中的节点前驱存在时，关键字`Key`一定被优化过且数值表示为该节点连接最小生成树的轻量级边的权重。

##### 时间复杂度

伪代码部分可以看出动态排序（优先队列）是算法中相对更损耗时间性能的地方，其他方面线性程度，其中要动态删除节点时间为：$O(VlgV)$，遍历所有的临边参照无向图邻接链表的遍历时间为$O(2E)$，遍历过程中隐含了修改键值操作所以遍历过程时间为：$O(ElgV)$，最终时间复杂度为：
$$
O(VlgV+ElgV)=O(ElgV)
$$
全部代码点击原文获取