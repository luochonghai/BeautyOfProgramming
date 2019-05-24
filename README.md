# Contents
## Chapter 1 游戏之乐
### 1.1 让CPU占用率曲线听你指挥
CPU占用率曲线为正弦曲线的效果图
<img src="https://github.com/luochonghai/BeautyOfProgramming/blob/master/Fun_In_Games/1.1/20sec.gif"  alt="1.1图"/>
### 1.2 中国象棋将帅问题
### 1.3 一摞烙饼的排序
扩展问题2：先按照朴素的pancake_sort方法将烙饼按大小排序；然后对于每个正面不朝上的第i个烙饼，先将它翻到顶部，然后单独翻转它，再将前i个烙饼翻转。 
<br/>扩展问题3:2/3
### 1.4 买书问题
#### （1）能否对动态规划进行某种状态压缩呢？
#### （2）能否用其他思路来解决问题呢？
### 1.6 饮料供货
一般来说，多种商品、多种指标的题目都与动态规划有关；动态规划能否转换为贪心算法，从而提高运算速度，则是一个关键点。
### 1.15 构造数独
给定一个数独，通过转置、调换一组行或者一组列、互换所有的某两个数对的位置，就可以生成新的数独（只实现了调换一组行的操作）。

## Chapter 2 数字之谜
### 2.1 求2进制数中1的个数
（位运算的）一些技巧
### 2.2 不要被阶乘吓倒
位运算的一些应用（如果将数看成是某种进制数位幂的连加）
### 2.3 寻找发帖的“水王”
妙用抵消法
有一个地方存疑：对于N-1个元素，需要多少次遍历才能得到结果？
### 2.4 1的数目
#### (1)Number of digit one(Leetcode 233)
#### (2)估算上确界后求解
### 2.6 精确表达浮点数
有限小数部分和无限循环小数部分的分母求最小公倍数。
### 2.7 最大公约数问题
妙用位运算，使得算法复杂度降到log2(max(x,y)).
### 2.10 寻找数组中的最大值和最小值
拓展：如果找的是次大值，则采用空间换时间的做法，需要O(lgn)的空间复杂度，将比较次数从O(3n/2)降到O(n+lg(n))。
### 2.16 求数组中最长递增子序列
动态规划经典问题
### 2.18 分割数组
这道题给出的两种动态规划算法分别适用于数组元素多而数值范围小，和数组元素少但数值范围大两种情况。
书上给出的第三个算法似乎有些问题，因此我做了些微调。
扩展问题：如果数组中有负数，怎么办？
我取最小的那个负数的绝对值为偏置量，让每个数都加上这个偏置量即可。

## Chapter 3 结构之法
### 3.1 字符串移位包含的问题
### 3.2 电话号码对应英语单词
将循环化为递归（代码变得简洁，不过需要的栈更大了）
### 3.3 计算字符串的相似度
编辑距离问题(leetcode 72.Edit distance)
### 3.10 分层遍历二叉树
leetcode 102.Binary Tree Level Order Traversal
本质上是两种做法：BFS和DFS

## Chapter 4 数学之趣
### 4.1金刚坐飞机问题
在实验中，problem2的结果似乎与书上的结果不符。我坚持相信实验的结果是正确的，或许是我在题意上理解有偏差吧。

若N = 2,金刚排第2个上飞机，选择了第1,2,3位置坐的时候，满足要求的序列有：(2,3,1),(3,2,1),(1,3,2),(1,2,3).

出去金刚所在的位置2，那么另外两个出现在各自原位的概率都是1/2。

如果金刚的上飞机顺序也不固定（这与题意貌似相悖），那么同样可以得到其他乘客出现在原位的概率均为1/3。

### 4.2 瓷砖覆盖地板（扩展问题即poj 2411）
#### 方法简介
#### 用pre表示前一行的二进制形式，now表示后一行的二进制形式，c表示当前操作的列号。c，pre，now初值都为0.由于是从左边位模拟到最右边的位，所以对应3种操作的结果为： 

#### 当前位不放，则前行的当前位必定为1才能兼容且后行为0：c=c+1，(pre<<1)|1,now<<1 

#### 当前位上方，则前行的当前位必定为0才能兼容且后行为1：c=c+1，(pre<<1),(now<<1)|1 

#### 当前位右方，则前行的当前2位必定为1才能兼容且后行当前2位为1：c=c+2，(pre<<1)|3,(now<<1)|3 

#### 且要注意到：如果执行以上操作而使得c==m，则表明生成了一个兼容对。如果c>m，则表明生成了一非法的长度越界兼容对，要抛弃。
### 4.3 买票找零
该问题属于卡特兰数的一种变体。当然，另一种以前在离散数学课上学到的解法也很巧妙。
### 4.4 点是否在三角形内
#### 判断点是否在三角形内的方法有：
#### （1）根据面积来判断
#### （2）根据点是否都在线的一侧来判断
#### （3）根据行列式计算出的三角形有向面积正负号来判断（前两种方法本质上就是第三种方法的变形）

#### 拓展问题：
#### （1）如何辨别点在边上的情形：
#### 查看三角形面积是否为零（叉积为零）
#### （2）判断点在凸多边形内
#### 可以沿用上述方法，不过假定有m个点待检测，该多边形有n条边，则时间复杂度为O(mn).
#### 可以通过二分法给出O(mlg(n))的算法（待完成POJ.1584）
#### （3）如何判断点是否在不自交多边形内
#### 可以使用图形学算法来计算（待完成）
#### （4）如何判断点是否在四面体内
#### 通过行列式来计算有向体积的方向（四阶行列式）
### 4.6 桶中取黑白球
一道推理题，之后符号化推理过程的思想很漂亮。
### 4.7 蚂蚁爬杆
考虑一只蚂蚁的爬行的最长时间，除了考虑这只蚂蚁的爬行方向之外，还需要考虑其他蚂蚁的爬行方向。
### 4.9 数独知多少
简化版推理：https://philoscience.iteye.com/blog/1525673
详见http://www.afjarvis.staff.shef.ac.uk/sudoku/
### 4.11 挖雷游戏的概率
当地雷从10个变化到240个，P(A),P(B),P(C)的三条曲线图
<img src="https://github.com/luochonghai/BeautyOfProgramming/blob/master/Interest_On_Maths/4.11/values.png"  alt="4.11图"/>
