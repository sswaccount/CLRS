#### Bellman-Ford算法

该算法的特性是针对更广泛情况下的最短路径查询，其中边权可以为负数，并且会针对数据判断图中是否有从源节点到达负权环路的路径。

方法依旧基于`Class<Graph>`实现，其中对少数地方做了对应修正，在带权边最短路算法中需要两个最基本的操作：

- 初始化操作：使得除了根节点以外的节点`d`属性设置为$\infty$，前驱节点设置为空，这里的`d`属性表示的是该节点距离源节点的上界或标准最小值；

  ```cpp
  void Graph::InitializeSingleSource(string s)
  {
      for (auto &i : G)
      {
          i._d = Maxnum;
          i._pi = nullptr;
      }
      G[index[s]]._d = 0;
  }
  ```

- 松弛操作：对于一条有向边`(u,v)`，其边权不变化，但如果出边点距离发生优化，则入边点就需要及时更新：

  ```cpp
  void Graph::Relax(string u, string v)
  {
      if (G[index[v]]._d > G[index[u]]._d + weight[{u, v}])
      {
          G[index[v]]._d = G[index[u]]._d + weight[{u, v}];
          G[index[v]]._pi = &G[index[u]];
      }
  }
  ```

上述两个基本操作组成了`Bellman-Ford`算法的基本要素，之后要进行的就是组装。

由于上述提到的其算法可以检测是否存在负权环边，那么函数的就会被定义为布尔类型，此外检测负权环边要根据其特性：无限循环的情况下会被无限优化至负无穷（所以说负无穷的逻辑定义也是数值上定义同步的）,最终算法过程被描述为：

```cpp
bool Graph::BellmanFord(string root)
{
    InitializeSingleSource(root);
    for (int i = 1; i < vertex; i++)
        for (auto it : weight)
            Relax(it.first.first, it.first.second);
    for (auto it : weight)
        if (G[index[it.first.second]]._d > G[index[it.first.first]]._d + it.second)
            return false;
    return true;
}
```

主要分为三个步骤：

- 初始化；
- $|V|-1$次遍历所有边并松弛；
- 结束松弛后判断是否能继续被松弛，若可以则证明其存在负权环边；

并且该算法依旧采用了临界链表储存，而边值为了便于操作选择了`map<pair<str,str>,int>`实现，这里为了便于实现而并不代表实际性能。

<img src="C:\Users\SSW\Desktop\dsa.png" style="zoom:25%;" />

采用图中数据做测验，输出点的`d`属性为：

```
s 0
t 2
x 4
y 7
z -2
```

#### 分析

##### 算法时间复杂度

从上述描述可以得出算法主要消耗在$|V|-1$次对所有边的遍历以及常数的松弛操作，所以`Bellman-Ford`算法的时间复杂度为$O(VE)$。

##### 算法正确性

> 引理：$G=(V,E)$为一个带权且源节点为$s$的有向图，若图中不包含负权环路，则算法进行$|V|-1$次后对于所有其他从源节点出发的点`v`有$v.d=\delta(s,v)$。

考虑路径$p$为源节点到`v`的最短路径：
$$
p=<v_0,v_1,...,v_k>
$$
上节所提到的最短路均不包含环路（最短的意义扩展到边的数量上），所以$|p|\le |V|-1$，由此在图中优化$|V|-1$次保证了最远的点的所有边都被遍历优化过，结果成立。

> 推论：在上述的图的前提下，存在一条从源节点$s$到任意节点$v$的路径当且仅当算法终止时$v.d< \infty$。

假设有一条最短路径存在，那么根据上述引理，最短路径一定存在且被松弛到非无穷的数值范围内；

反过来看如果存在$v.d< \infty$，那么在此过程中一定被某个相邻的点进行过松弛优化，所以该点给`v`的前驱节点，在最短路搜索树中根节点为`s`，既然在搜索过程中被更新说明根节点是`v`的前驱的祖先，那么同样也是`v`的祖先，所以存在一条最短路径。

> [定理]`Bellman-Ford`的正确性：依旧在上述图的背景下，若图中不存在负权环路则返回`True`且对于所有节点的前驱组成的前驱子图是一棵最短路径树；相反若存在负权环路则算法返回`False`。

当图中不包含负权环路时，上述引理证明了算法终止时，源节点到某一节点`v`可达状态下存在$v.d=\delta(s,v)$，不可达其同样满足（值为$\infty$）。所以在上述要求下，前驱子图确定是一棵最短路径树，同时在最终检验中，因为不存在负权环路所以没有边会在检验中被优化，最终算法返回`True`。

当图中包含一条负权环路：
$$
p=<v_0,v_1,...,v_k>
$$
同时$v_0=v_k$，则会得出结论：
$$
\sum_{i=1}^{k} w\left(v_{i-1}, v_{i}\right)<0
$$
假设最终返回了`True`，则一定保证不会再检验时跳出换句话说就是所有的边满足了：
$$
v_{i} . d \leq v_{i-1} . d+w\left(v_{i-1}, v_{i}\right)
$$
对其进行加和处理：
$$
\begin{aligned}
\sum_{i=1}^{k} v_{i} \cdot d & \leq \sum_{i=1}^{k}\left(v_{i-1} \cdot d+w\left(v_{i-1}, v_{i}\right)\right) \\
&=\sum_{i=1}^{k} v_{i-1} \cdot d+\sum_{i=1}^{k} w\left(v_{i-1}, v_{i}\right)
\end{aligned}
$$
可以明显看出两个$v.d$的加和函数是错位的，但是由于$v_0=v_k$，那么上式可以抵消两个对属性`d`的求和函数得到：
$$
0 \leq \sum_{i=1}^{k} w\left(v_{i-1}, v_{i}\right)
$$
可以看到与最初的结论相矛盾，所以该问题得证。