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
$$
\begin{aligned}
&y_{1} \quad&=b_{\pi[1]},\\
&l_{21} y_{1}+y_{2}&=b_{\pi[2]},\\
&l_{31} y_{1}+l_{32} y_{2}+y_{3}&=b_{\pi[3]},\\
&l_{n 1} y_{1}+l_{n 2} y_{2}+l_{n 3} y_{3}+\cdots+y_{n}&=b_{\pi[n]} .
\end{aligned}
$$
由于$P$为置换矩阵所以$Pb$只是被替换顺序的原先列向量，而$L$是对角线元素为$1$的下三角矩阵，那么求解过程可以很容易的表示为：
$$
y_i=b_{\pi[i]}-\sum^{i-1}_{j=1}l_{ij}y_j
$$
可以看出方式为朴素的从上到下迭代求解，时间复杂度为$O(n^2)$，第二步的上三角矩阵反向推得可知：
$$
\begin{aligned} u_{11} x_{1}+u_{12} x_{2}+\cdots+u_{1, n-2} x_{n-2}+u_{1, n-1} x_{n-1}+u_{1 n} x_{n} &=y_{1} \\ u_{22} x_{2}+\cdots+u_{2, n-2} x_{n-2}+u_{2, n-1} x_{n-1}+u_{2 n} x_{n} &=y_{2} \\ & \vdots \\ u_{n-2, n-2} x_{n-2}+u_{n-2, n-1} x_{n-1}+u_{n-2, n} x_{n} &=y_{n-2} \\ u_{n-1, n-1} x_{n-1}+u_{n-1, n} x_{n} &=y_{n-1} \\ u_{n, n} x_{n} &=y_{n} \end{aligned}
$$
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

首先考虑基础的不含$P$矩阵的$LU$分解，那么可以由高斯消元法推得：
$$
\begin{aligned} A &=\left(\begin{array}{c|ccc}a_{11} & a_{12} & \cdots & a_{1 n} \\ \hline a_{21} & a_{22} & \cdots & a_{2 n} \\ \vdots & \vdots & \ddots & \vdots \\ a_{n 1} & a_{n 2} & \cdots & a_{n n}\end{array}\right) \\ &=\left(\begin{array}{cc}a_{11} & w^{\mathrm{T}} \\ v & A^{\prime}\end{array}\right), \end{aligned}
$$
此处在方阵中采用的递推式消元，上述公式指明了消元的一个状态，而每个状态都能成功分解一层，由矩阵乘法验证可知：
$$
\begin{aligned} A &=\left(\begin{array}{cc}1 & 0 \\ v / a_{11} & I_{n-1}\end{array}\right)\left(\begin{array}{cc}a_{11} & w^{\mathrm{T}} \\ 0 & A^{\prime}-v w^{\mathrm{T}} / a_{11}\end{array}\right) \\ &=\left(\begin{array}{cc}1 & 0 \\ v / a_{11} & I_{n-1}\end{array}\right)\left(\begin{array}{cc}a_{11} & w^{\mathrm{T}} \\ 0 & L^{\prime} U^{\prime}\end{array}\right) \\ &=\left(\begin{array}{cc}1 & 0 \\ v / a_{11} & L^{\prime}\end{array}\right)\left(\begin{array}{cc}a_{11} & w^{\mathrm{T}} \\ 0 & U^{\prime}\end{array}\right) \\ &=L U \end{aligned}
$$
其中上述式子推导类似高等代数中分块矩阵乘法所应用的情景，最终通过迭代$n$次求解$LU$矩阵，可以看出并不用每一层处理后都进行分解，因为在递推的的状态下只需要将每层的数据保留继续计算下一层的$A$直至结束即可，最终上三角部分即为矩阵$U$，下三角部分使用$1$填补对角线即为矩阵$L$。

```python
def LUDecomposition(A):
    n = A.shape[0]
    L, U = np.eye(n), np.zeros((n, n))
    for k in range(n):
        U[k, k] = A[k, k]
        for i in range(k+1, n):
            L[i, k] = A[i, k]/U[k, k]
            U[k, i] = A[k, i]
        for i in range(k + 1, n):
            for j in range(k+1, n):
                A[i, j] -= L[i, k]*U[k, j]
    return L, U
```

由于$L$对角线为$1$所以提前设置为单位矩阵，之后每行遍历对应第$k$行：

- 计算$A_{kk}$到$A_{nn}$的子矩阵；

- 保留$A_{kk}$到矩阵$U$；

- 维护子矩阵第$k$列数据与第$k$行数据；

- 计算下一阶段子矩阵:
  $$
  A'=A'-\frac{vw^T}{A_{kk}}\\
  \because L_{ik}=\frac{A_{ik}}{U_{kk}}\\
  \therefore A_{ij}'=A_{ij}'-L_{ik}U_{kj}\\
  $$

#### 计算$LUP$分解

为了解决上述$u_{ii}$有可能为零的情况，$LUP$分解再分解过程中加入了选择步骤：

选择当前状态当前列的绝对值最大的行索引交换到当前行，并将过程中的交换内容保存在置换矩阵中，这里我们在数据实现部分将交换保存在了数组中，主要作用是减少占用空间且作为索引数组使用，记作$\pi[index]$。

其中推导过程下节结合舒尔补做进一步说明，这里给出实现程序：

```python
def LUPDecomposition(A):
    n = A.shape[0]
    pi = np.zeros((n, 1))
    for i in range(n):
        pi[i] = i
    for k in range(n):
        p = 0
        for i in range(k, n):
            if np.abs(A[i, k]) > p:
                p = np.abs(A[i, k])
                k_ = i
        if p == 0:
            error("singular matrix")
        pi[k], pi[k_] = pi[k_], pi[k]
        A[[k, k_], :] = A[[k_, k], :]
        for i in range(k+1, n):
            A[i, k] /= A[k, k]
            for j in range(k+1, n):
                A[i, j] -= A[i, k]*A[k, j]
    return A
```

全部程序点击下方阅读原文获取