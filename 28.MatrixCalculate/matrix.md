计算机求解线性方程组$Ax=b$过程中，更多的是采用数值计算方法求解而取代数学意义上效率更高的求逆运算，其中一个重要的问题是数值的稳定性。

上述线性方程组中$A$为$n$阶方阵，其中实际求解问题中只针对非奇异矩阵的情况下，这里首先介绍一种较为常见的$LUP$分解方式求解方法。

#### $LUP$方法求解

原理为找出满足条件的三个$n$阶方阵$LUP$使得
$$
PA=LU
$$
其中$L$为下三角矩阵，$U$为上三角矩阵，$P$为置换矩阵，在原方程$Ax=b$中会得到
$$
\begin{aligned}
PAx&=Pb\\
LUx&=Pb\\
\end{aligned}
$$
其中定义$Ux=y$得到$Ly=Pb$这时该位置向量$y$会被更容易的求得，之后将$Ux=y$以类似方式求解，其中做回推：
$$
\begin{aligned}
A&=P^{-1}LU\\
Ax&=P^{-1}LUx\\
Ax&=P^{-1}Ly\\
Ax&=P^{-1}Pb\\
Ax&=b\\
\end{aligned}
$$
上述两步$Ly=Pb$和$Ux=y$为三角矩阵求解未知数，用前者表示说明：

<img src="C:\Users\SSW\Desktop\Ly=Pb.png" style="zoom:33%;" />

由于$P$为置换矩阵所以$Pb$只是被替换顺序的原先列向量，而$L$是对角线元素为$1$的下三角矩阵，那么求解过程可以很容易的表示为：
$$
y_i=b_{\pi[i]}-\sum^{i-1}_{j=1}l_{ij}y_j
$$
可以看出方式为朴素的从上到下迭代求解，时间复杂度为$O(n^2)$，第二步的上三角矩阵反向推得可知：

<img src="C:\Users\SSW\Desktop\Ux=y.png" style="zoom:33%;" />

这里$U$为对角线不为1的上三角矩阵，那么求解过程不仅仅要自下而上并且需要有除法进行，其中计算机内进行过程中会涉及到数值精度问题。
$$
x_i=(y_i-\sum_{j=i+1}^nu_{ij}x_j)/u_{ii}
$$
这里的置换矩阵$P$提高了解决问题的数值稳定性，主要解决的是分解矩阵时存在$u_{ii}$趋近于零的情况，本文暂时讨论$LUP$分解计算方法，这里给出$Python$上述对应的的求解方法：

```python
import numpy as np
def LUPSolve(L, U, pi, b):
    n = L.shape[0]
    y = np.zeros((n, 1))
    x = np.zeros((n, 1))
    for i in range(n):
        y[i] = b[pi[i]] - np.dot(L[i], y)
    for i in range(n-1, -1, -1):
        x[i] = (y[i]-np.dot(U[i], x))/U[i, i]
    return x
```

其中各项数据及其输出为：

```python
L = np.array([[1, 0, 0], [0.2, 1, 0], [0.6, 0.5, 1]])
U = np.array([[5, 6, 3], [0, 0.8, -0.6], [0, 0, 2.5]])
b = np.array([3, 7, 8])
pi = np.array([2, 0, 1])
print(LUPSolve(L, U, pi, b))
->[[-1.4] [ 2.2] [ 0.6]]
```

前三个变量以知，$pi$的角色扮演为索引数组取代了运算中置换矩阵的作用

#### 计算$LU$分解

