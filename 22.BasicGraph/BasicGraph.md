书中在第二十二章图的基本算法中主要提到了以下几个部分：

- 图的表示
- `BFS`
- `DFS`
- 拓扑排序
- 强连通分量

相关算法题目的语言实现操作这里不做阐述，主要实现书中提到的伪代码实现与证明过程：

#### 图的表示

<img src="C:\Users\SSW\AppData\Roaming\Typora\typora-user-images\image-20220327183100049.png" alt="image-20220327183100049" style="zoom:50%;" />

对于$G=(V,E)$主要针对点集为$V$，边集为$E$的有向图和无向图，其中两种标准的方法是邻接链表和邻接矩阵：

- 邻接矩阵可以看作是空间复杂度为$O(V\times V)$的`01矩阵`，当边带权重时则矩阵内部的信息会出现边权取代`01`值；
- 邻接链表通过链表方式记录每个节点连接的邻居节点，空间复杂度为$O(E)$。

有向图与无向图对于邻接矩阵的区别就是当作为无向图时$Matrix(x,y)=Matrix(y,x)$，但空间消耗方面无变化；邻接链表可以理解为对称的把一条边当作两条有向边记录两次，空间小号常数倍增加，在数据量较小时邻接矩阵操作更加灵敏，数据量增加朴素的邻接矩阵效率会低于邻接链表。

更灵活的，算法题目中存图的方式是邻接链表的变种邻接表，相比之下去掉了更加复杂的链表操作用数组映射关系取代。

##### 实现图的表示创建

- 定义三种颜色`VerClolor`（搜索算法书中的理解要求，描述的是搜索中的已完成搜索、临近节点正在搜索和未搜索三种状态）

- 定义链表头节点`Vertex`，其中包含名称、颜色、前驱节点（搜索的一个先后状态）、距离（搜索算法使用参数）和指向后面临边的指针
- 定义`NextNode`结构体用于连接链表头节点或者连接临边结构体

```cpp
enum VerClolor
{
    WHITE,
    GRAY,
    BLACK,
};
struct Vertex
{
    char _name;
    VerClolor _color;
    Vertex *_pi;
    int _d;
    NextNode *_first;
    Vertex(char name = ' ')
        : _name(name),
          _color(WHITE),
          _pi(nullptr),
          _d(0),
          _first(nullptr) {}
};
struct NextNode
{
    char adjvex;
    NextNode *NEXT;
    NextNode(char name = ' ')
        : adjvex(name),
          NEXT(nullptr) {}
};
```

之后创建图类：

其中包含维护点数和边数的参数，构造函数直接读入点的名称数组以便于建图，由于名称不是整型，所以为了方便这部分添加了哈希表维护，因为实际运用名称直接使用下标，所以插入查找哈希表时间复杂度不计入其中。

```cpp
class Graph
{
private:
    int vertex, edge;
    vector<Vertex> G;
    map<char, int> index;

public:
    Graph(int v, int e, char *vs)
        : vertex(v), edge(e)
    {
        for (int i = 0; i < v; ++i)
        {
            G.push_back(Vertex(vs[i]));
            index.insert({vs[i], i});
        }
    }
    void AddEdge(char x, char y, bool flag = false);
};
```

此外添加了方法：`AddEdge()`用于添加边，设置布尔参数的目的是区分是否定义有向图和无向图，添加边的过程有两种情况：

- 当链表头指向临边结构体的指针为空时直接添加数据
- 当链表头指针不空时从指针指向的结构体开始往下查找直到链表指针为空后添加数据

```cpp
void Graph::AddEdge(char x, char y, bool flag)
{
    NextNode *e = new NextNode(y);
    if (G[index[x]]._first == nullptr)
        G[index[x]]._first = e;
    else
    {
        NextNode *p = G[index[x]]._first;
        while (p->NEXT)
            p = p->NEXT;
        p->NEXT = e;
    }
    if (flag)
        AddEdge(y, x);
}
```

#### BFS

广度优先搜索意义就是用队列维护，优先的去先搜索离目标地点最近的节点，所以很容易得出广搜的应用场景包含`最短路径`等等。

这里参照书中的方法和思想所以在节点头中定义了很多看起来和建图无关的信息（颜色、前驱节点、距离）。

广度优先搜索的目的是找出图中所有点距离目标点的最小值，因为该图为无向无权图所以距离指的是单位距离，主要步骤有三个：

<img src="C:\Users\SSW\AppData\Roaming\Typora\typora-user-images\image-20220327213140519.png" alt="image-20220327213140519" style="zoom:50%;" />

1. 将目标点之外的其他节点颜色置为白色，距离设置为无限大，前驱节点指针设置为空；同时将目标点设置为灰色，距离设置为0，由于目标点就是整体图的搜索父节点所以前驱节点也是空；

   ```cpp
   for (auto u : G)
           if (u._name != s)
           {
               u._color = WHITE;
               u._d = 0x7fffffff;
               u._pi = nullptr;
           }
       G[index[s]]._color = GRAY;
       G[index[s]]._d = 0;
       G[index[s]]._pi = nullptr;
   ```

2. 创建队列并放入目标节点开始搜索；

   ```cpp
   queue<char> Q;
   Q.push(s);
   ```

3. 拿出队列头部的节点，对其进行临边的搜索，如果搜索的临边颜色为白色证明它没有被搜索过，或者说这样意味着该搜索过程第一次经过临边节点，这就等同于找到了到达该节点的最近距离。

   之后将该节点颜色改为灰色证明已经作为搜索点的相邻节点被探索过，之后前驱节点改为刚刚拿出的队列头部节点，最后当前节点的距离等于前驱节点距离的值加一（因为这是最近的方式，且无权图距离都是单位长度，为什么是最近的节点之后做细致讨论）。

   直到队列为空搜索结束，每个列表头节点对应的距离也就是距离目标点的最近距离。

   ```cpp
   while (Q.size())
   {
       char u = Q.front();
       Q.pop();
       for (auto v = G[index[u]]._first; v; v = v->NEXT)
           if (G[index[v->adjvex]]._color == WHITE)
           {
               G[index[v->adjvex]]._color = GRAY;
               G[index[v->adjvex]]._d = G[index[u]]._d + 1;
               G[index[v->adjvex]]._pi = &G[index[u]];
               Q.push(v->adjvex);
           }
       G[index[u]]._color = BLACK;
   }
   ```

一切代码以$Github$上传为准，详细阅读原文获得。

最终代码实现上述数据可视化后结果为（图中颜色代表的是距离，颜色越深距离越远）：

![](E:\2022\IA\22.BasicGraph\test.png)





