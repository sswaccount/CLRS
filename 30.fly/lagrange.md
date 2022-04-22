#### 插值多项式唯一性

继续上一节中假设的多项式$L(x)$，但此时为了便于分析定义最高次数为$n$：
$$
L_n(x)=\sum_{j=0}^{n} a_{j} x^{j}
$$

> 定理（插值多项式的唯一性）：对任意$n+1$个互不相同的点集合$\{(x_i,y_i)|i=0...n\}$会存在唯一的次数界为$n+1$的多项式$L_n(x)$满足$L_n(x_i)=y_i$。

其中将点集合带入多项式$L_n(x)$中结果为：
$$
&\begin{cases}
	a_0+a_1x_0+a_2x_0^2+\cdots +a_{n}x_0^{n}=y_0\\
	a_0+a_1x_1+a_2x_1^2+\cdots +a_{n}x_1^{n}=y_1\\
	\cdots \,\,\cdots \,\,\cdots \,\,\cdots\\
	a_0+a_1x_{n}+a_2x_{n}^2+\cdots +a_{n}x_{n}^{n}=y_{n}\\
\end{cases}
$$
转换为矩阵表达：
$$
\left(\begin{array}{ccccc}
1 & x_{0} & x_{0}^{2} & \cdots & x_{0}^{n} \\
1 & x_{1} & x_{1}^{2} & \cdots & x_{1}^{n} \\
\vdots & \vdots & \vdots & \ddots & \vdots \\
1 & x_{n} & x_{n}^{2} & \cdots & x_{n}^{n}
\end{array}\right)\left(\begin{array}{c}
a_{0} \\
a_{1} \\
\vdots \\
a_{n}
\end{array}\right)=\left(\begin{array}{c}
y_{0} \\
y_{1} \\
\vdots \\
y_{n}
\end{array}\right)
$$
上述方程的代数表达形式为：
$$
AX=Y
$$
由于：
$$
|A|=\prod_{0 \leq j<k \leq n-1}\left(x_{k}-x_{j}\right)\ne0
$$
所以方程组有唯一解，推导出$L_n(x)$唯一存在。

##### 插值方程求解

```mathematica
(*提供数据点*)
X = {x0, x1, x2, x3} = {10, 11, 12, 13}; 
Y = {y0, y1, y2, y3} = {2.3026, 2.3979, 2.4849, 2.5649}; 
(*生成4×4表后转置变为矩阵格式*)
A = Transpose[Table[{x0^j, x1^j, x2^j, x3^j}, {j, 0, 3}]]; 
MatrixForm[%]; 
(*解方程近似解并生成函数Ln*)
AA = LinearSolve[A, Y] // N
X1 = {1, x, x^2, x^3};
X1.AA 
(*使用上述结果替换全部x得到对应函数值*)
N[% /. x -> 11.75]
```

最终输出：

```mathematica
X1.AA = 0.6071 + 0.260883 x - 0.0113 x^2 + 0.000216667 x^3
L(11.75) = 2.46386
```

##### 拉格朗日插值法

形如$P_n(x)=\sum_{j=0}^{n} a_{j} x^{j}$的插值多项式由基函数和系数组成：

- 基函数：
  $$
  1,x^1,x^2,...,x^n
  $$

- 系数：
  $$
  a_0,a_1,a_2,...,a_n
  $$

先讨论$n=1$的线性插值多项式，$x_0,x_1$上两点：
$$
y_0=f(x_0),y_1=f(x_1)
$$
其中线性插值多项式$L_1(x)$满足:
$$
L_1(x_0)=y_0,L_1(x_1)=y_1,
$$
根据点斜式方程描述为：
$$
L_{1}(x)=y_{0}+\frac{y_{1}-y_{0}}{x_{1}-x_{0}}\left(x-x_{0}\right)
$$
将其根据$y_i$做拆解后为：
$$
L_{1}(x)=\frac{x-x_{1}}{x_{0}-x_{1}} y_{0}+\frac{x-x_{0}}{x_{1}-x_{0}} y_{1}
$$
此时可以发现式子可以表达为：
$$
L_{1}(x)=y_{0} l_{0}(x)+y_{1} l_{1}(x)
$$
由于上式为线性插值，所以$l_i(x)$也可以看作是线性插值的基函数，且：
$$
l_{0}(x)=\frac{x-x_{1}}{x_{0}-x_{1}}, \quad l_{1}(x)=\frac{x-x_{0}}{x_{1}-x_{0}}
$$

$$
\begin{array}{ll}
l_{0}\left(x_{0}\right)=1, & l_{0}\left(x_{1}\right)=0 \\
l_{1}\left(x_{0}\right)=0, & l_{1}\left(x_{1}\right)=1
\end{array}
$$

所以推测发现插值基函数的一个性质为：
$$
l_{j}\left(x_{k}\right)=\left\{\begin{array}{ll}
1, & k=j \\
0, & k \neq j
\end{array} \quad(j, k=0,1, \cdots, n)\right.
$$
这样的插值基函数性质可以使得在插值多项式$L_{n}(x)=\sum_{i=0}^{n} y_{i} l_{i}(x)$中，带入当初的某个已知点$x_i$时，其他点对应的插值基函数值为零，而当前点对应的基函数值为$1$且多项式结果为对应的$y_i$。

所以更详细的将基函数描述为：
$$
l_{i}(x)=\frac{\left(x-x_{0}\right) \cdots\left(x-x_{i-1}\right)\left(x-x_{i+1}\right) \cdots\left(x-x_{n}\right)}{\left(x_{i}-x_{0}\right) \cdots\left(x_{i}-x_{i-1}\right)\left(x_{i}-x_{i+1}\right) \cdots\left(x_{i}-x_{n}\right)}
$$
其分子保证非$x_i$元素值全为0，分母保证了若输入正确对应元素则将值全部抵消为1，所以拉格朗日插值公式可以被描述为：
$$
L_n(x)=\sum_{k=0}^{n} y_{k} \frac{\prod_{j \neq k}\left(x-x_{j}\right)}{\prod_{j \neq k}\left(x_{k}-x_{j}\right)}
$$

##### 函数表示

定义$n+1$次特殊函数：
$$
\omega_{n+1}(x)=\left(x-x_{0}\right)\left(x-x_{1}\right) \ldots\left(x-x_{n}\right)
$$
很容易看出这时针对插值基函数分子的构造，但相比之下分母更需要一个值的表达式，但直接取值会等于零，所以采取求导会是个好的选择：
$$
\omega_{n+1}^{\prime}\left(x_{k}\right)=\left(x_{k}-x_{0}) \ldots\left(x_{k}-x_{k-1}\right)\left(x_{k}-x_{k+1}\right) \ldots\left(x_{k}-x_{n}\right)\right.
$$
这时发现只需要在分母上添加需要被约去的表达式$(x-x_i)$即可：
$$
l_i(x)=\frac{\omega_{n+1}(x)}{\left(x-x_{i}\right) \omega_{n+1}^{\prime}\left(x_{i}\right)}
$$
此时就做出了更容易进行分析的多项式插值表达式：
$$
L_{n}(x)=\sum_{k=0}^{n} y_{k} \frac{\omega_{n+1}(x)}{\left(x-x_{k}\right) \omega_{n+1}^{\prime}\left(x_{k}\right)}
$$
由此可见拉格朗日插值形式的优缺点：

- 优点：结构紧凑
- 缺点：改变一个节点则需要重新计算

##### `mathematica`实现

```mathematica
(*输入数据检测维度*)
xx = {1, 2, 3, 4, 5};
yy = {1, 3, 6, 10, 16};
n = Length[xx];
(*omega函数表示*)
w[x_] := Product[(x - xx[[i]]), {i, 1, n}];
(*约掉连乘式中项，生成插值基函数*)
q[i_, x_] := Simplify[w[x]/(x - xx[[i]])];
l[i_, x_] := Simplify[q[i, x]]/(Simplify[q[i, x]] /. x -> xx[[i]]);
(*构造拉格朗日插值公式并化简输出*)
Lagrange[x_] := Sum[yy[[i]]*l[i, x], {i, 1, n}];
Simplify[Lagrange[x]]
```

最终输出：

```
1/24 (24 - 38 x + 47 x^2 - 10 x^3 + x^4)
```

![](C:\Users\SSW\Desktop\QQ图片20220415192336.png)













可以很直观的发现这是一个范德蒙德行列式，其行列式值为$(x_i\ne x_j|i\neq j)$：
$$
\prod_{0 \leq j<k \leq n-1}\left(x_{k}-x_{j}\right)
$$
所以该矩阵是可逆的，所以上述定理证明的多项式是唯一的，此外，拉格朗日插值公式是基于上述描述的更快的表达方法：

