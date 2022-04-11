#### 堆排序

一般来说堆排序针对的是二叉堆，这是一种数组结构，且表达为完全二叉树的形式：

> 完全二叉树：除最底层都是满的，且最下层节点从左到右依次排开。

这样的好处是能够通过简单的代数计算获得父节点、左孩子、右孩子节点在数组结构中的编号：

<img src="C:\Users\SSW\Desktop\完全二叉树.png" style="zoom:33%;" />

如此可以很简便的用代码表达为：

```cpp
int Parent(int i)
{
    return i >> 1;
}
int Left(int i)
{
    return i << 1;
}
int Right(int i)
{
    return (i << 1) + 1;
}
```

二叉堆分为大根堆和小根堆，从表面意思可以理解：

- 大根堆：$Value(parent(i))\ge Value(i)$；
- 小根堆：$Value(parent(i))\le Value(i)$；

##### 维护堆的性质

`Max-Heapify(i)`是维护大根堆的性质的过程（小根堆则相反），该方法用于维护数组索引为`i`位置的元素保持性质，其中默认的背景是只维护当前点（当前点的左右孩子均符合性质）：

```cpp
void MaxHeapify(int *a, int i, int heap_size)
{
    int l = Left(i);
    int r = Right(i);
    int largest = i;
    if (l <= heap_size && a[l] > a[i])
        largest = l;
    else
        largest = i;
    if (r <= heap_size && a[r] > a[largest])
        largest = r;
    if (largest != i)
    {
        swap(a[i], a[largest]);
        MaxHeapify(a, largest, heap_size);
    }
}
```

分别于左右孩子进行基于性质的比较，最终如果最大的值不是原先的父节点，那么交换两者，此时`largest`索引的元素位置即为被换下的父节点，这三个点的关系很明了，但当前`largest`索引为父节点的节点性质有可能被破坏了，所以如果改变后需要向下迭代维护性质。

![](C:\Users\SSW\Desktop\维护.png)

##### 建堆

上述已经说明二叉堆是数组结构，所以建堆的过程实际是维护堆性质的过程，那么叶子节点一定不用维护（因为这时叶子节点单个点一定能够满足堆的性质），依据二叉堆的性质：

> 完全二叉树编号为$(\lfloor \frac{n}{2}\rfloor ,n]$区间内的节点均为叶子节点。

证明：尝试找到最底层从左至右最右边的一个叶子节点编号为$n$，那么其父亲是上一层从左到右最右边的具有叶子节点的节点，其编号为$\lfloor\frac{n}{2}\rfloor$。

```cpp
void BuildMaxHeap(int *a, int size)
{
    int heap_size = size;
    for (int i = heap_size >> 1; i >= 1; i--)
        MaxHeapify(a, i, heap_size);
}
```

这里采用遍历前方具有孩子的节点进行维护，逆向维护的原因是维护性质方法`Max-Heapify`假设情况为左右子树均符合性质要求。

##### 堆排序

因为上述建堆的过程可以将最大的元素（此处说明的是大根堆），放置于顶端，所以依照此方案，每次都能在顶端取到最大元素，只要能把最大元素取出来。

> 讨论上述实现为什么使用数组长度`size`和堆数组长度`heap_size`两个变量描述过程：

取出来的操作可以抽象理解为不去管理当前元素，一个很好的办法就是将其放在数组最末端，堆数组长度自减使得不予理会该元素，那么最快捷的方法（最小元素交换次数）是将堆顶元素和堆尾元素交换其在数组中的实际索引：

<img src="C:\Users\SSW\Desktop\sort.png" style="zoom:33%;" />

直到堆长度为$1$，换句话说堆数组长度实际是虚拟的长度，其管辖范围内的长度，实现方法为：

```cpp
void HeapSort(int *a, int size)
{
    BuildMaxHeap(a, size);
    int heap_size = size;
    for (int i = size; i > 1; i--)
    {
        swap(a[1], a[i]);
        MaxHeapify(a, 1, --heap_size);
    }
}
```

#### 优先队列

优先队列会应用于图论的很多算法中，其中主要负责的是维护一组元素集合，可以是简单的数据，也可以是复杂的结构类型，其中维护的内容为每个元素节点的关键字$key$，使得整棵二叉树都遵循$key$的数量关系，用最大优先队列举例：

- `Insert()`：插入元素操作
- `Maximum()`：返回树中最大值
- `ExtractMax()`：弹出并返回最大值
- `Increase-Key()`：将某个节点键值`key`做改变

对应于最小优先队列则是减少某节点键值，因为这里其实更强调的是操作后是否对性质产生破坏。

#####　返回最大值

操作很显然，直接返回数组结构的第一位：

```cpp
int HeapMaxiNum(int *a)
{
    return a[1];
}
```

##### 弹出最大值并返回

类比堆排序，相比删除元素，弹出的意义同样是不加入推排序的管辖，所以只需要与堆数组最后一位做交换并维护对的性质即可：

```cpp
int HeapExtractMax(int *a, int &size)
{
    if (size < 1)
        return -1;
    int max_num = a[1];
    a[1] = a[size];
    MaxHeapify(a, 1, --size);
    return max_num;
}
```

##### 改变某元素的key

此时需要与父节点做比较，因为堆的性质中并没有针对孩子节点之间的要求，所以只要能满足大于孩子节点即找到了最佳解决方案，向上查找是个理性的方法：

```cpp
void HeapIncreaseKey(int *a, int i, int key)
{
    if (key < a[i])
        return;
    a[i] = key;
    while (i > 1 && a[Parent(i)] < a[i])
    {
        swap(a[i], a[Parent(i)]);
        i = Parent(i);
    }
}
```

这里描述中对于关键字的检验不是必须的，甚至如果愿意扩展，可以向下对二叉堆做性质的维护检查。

![](C:\Users\SSW\Desktop\inc.png)

##### 插入元素

插入元素更像是排序过程中取消管理权限的逆过程，增加管理权限需要对堆的长度做上述相反的维护，如果默认新扩展的数组单元为负无穷的话（这里对大根堆做描述所以为负无穷），对其的值的改变操作恰好符合了改变某元素`key`的方法，所以实现为：

```cpp
void MaxHeapInsert(int *a, int key, int &size)
{
    size++;
    a[size] = MinNum;
    HeapIncreaseKey(a, size, key);
}
```

注：在一个包含$n$个元素的队列中，所有操作均在$O(lgn)$时间内完成。

全部源码阅读原文获取:dog: