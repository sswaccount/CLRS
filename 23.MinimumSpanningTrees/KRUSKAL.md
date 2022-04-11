### $Kruskal$算法

又称作为克鲁斯卡尔算法，是基于贪心的一种最小生成树算法，根据前两部分了解到的安全边规则与不相交集合的数据结构（并查集），即可实现该算法的内容：

$Kruskal$方法的中心思想是在图中寻找一条权重最小的连接两个不相交集合的边即为所寻找的安全边。可以理解为找的边$(u,v)$符合横向切割的轻量级边的要求且一定尊重某最小生成树集合$A$，是否尊重节点$u$代表的或者节点$v$代表的某棵正在发现过程中的最小生成树集合很容易。

上述表述的是权重最小且连接两个不相交子集和，那么可以在图$G(V,E)$展开描述为：

- 将$E$中所有边按照边权从小到大排序；
- 遍历排序后的边时进行并查集查询，判断当前边两节点是否在同一集合中；
- 若不在同一集合中将当前边添加最小生成树中；

##### 程序复现

```cpp
class Graph
{
private:
    int V, E;
public:
    vector<pair<pair<int, int>, int>> G;
    Graph(int v, int e)
        : V(v), E(e) {}
    void add(char u, char v, int w)
    {
        add(u - 'a' + 1, v - 'a' + 1, w);
    }
    void add(int u, int v, int w)
    {
        G.push_back({{u, v}, w});
    }
    void MST_KRUSKAL();
};
```

以上内容为定义类型，核心代码程序为：

```cpp
void Graph::MST_KRUSKAL()
{
    vector<pair<int, int>> A;
    DisjiontSet x = DisjiontSet(V);
    sort(G.begin(), G.end(), cmp);
    for (auto i : G)
        if (x.FindSet(i.first.second) != x.FindSet(i.first.first))
        {
            A.push_back({i.first.first, i.first.second});
            x.Union(i.first.first, i.first.second);
        }
}
```

排序过程中按照权重进行排序，其次此处不相交数据结构采用了上一节描述的路径压缩的按秩合并方法，时间复杂度$O((V+E)\alpha(V))$（合并操作+初始化节点），其中$\alpha$函数是一个增长极慢的函数，可以近似理解为线性操作。

在图较大时，排序的时间复杂度会比并查集大的多，所以主要时间复杂度会表示在排序上，稠密图中时间复杂度表示为$O(ElogE)$。

##### 实际计算

<img src="C:\Users\SSW\Desktop\act.png" style="zoom:33%;" />

按照上述样例输入后输出集合$A$内边集合为：

```
h g
i c
g f
a b
c f
c d
a h
d e
```

注：中文书中伪代码判断是否同意集合存在异常，修改为：

```
if FIND-SET(u)≠FIND-SET(v)
```

全部代码阅读原文获取