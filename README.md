

# 如何使用Construct-Helper构造数据

这里将会介绍如何使用Construct-Helper来快速构造数据

## 树

必需参数:$n$ (节点数量)

可选参数:$l$ (边权下界)，$r$ (边权上界)，$unique$(边权是否唯一)

当可选参数都被填入时，会构造带边权的树，否则会构造不带边权的树

输入格式:

第一行为整数$n$，表示节点的数量

之后有$n-1$行，每行表示一条边，如果填入了可选参数，每行有三个用空格隔开的整数，分别表示这条边的出点，入点，权值。反之，每行只有两个数，表示一条边的出点，入点

```
//填入了可选参数
n
u1,v1,w1
u2,v2,w2
...
un,vn,wn
//没有填入可选参数
n
u1,v1
u2,v2
...
un,vn
```

注意:

```c++
return n<=1e7;

if(unique){
    return r-l>=n
}
```

## K叉树

必需参数:$n$ (节点数量)

可选参数:$l$ (边权下界)，$r$ (边权上界)，$unique$(边权是否唯一)

当$l,r,unique$都被填入时，会构造带边权的树，否则会构造不带边权的树

如果不填写参数k，则默认值为$2$

输入格式与注意事项同: **树**

## 有向无环图/有向带环图

必需参数:$n$ (节点数量)，$m$(边的数量)，$ring$(是否包含**正环**)

可选参数:$l$ (边权下界)，$r$ (边权上界)，$unique$(边权是否唯一)$k$ (每个节点的最大子节点数)

当$l,r,unique$都被填入时，会构造带边权的树，否则会构造不带边权的树

输入格式:

第一行有两个用空格分割的整数n,m

如果l，r，unique都被填入，接下来m行，每行有三个空格分割的数字u v w，表示一条边的出发点编号，结束点编号，权值

否则，接下来m行，每行有两个空格空格分割的数字u v，表示一条边的出发点编号，结束点编号

```
//填入了可选参数
n m
u1,v1,w1
u2,v2,w2
...
un,vn,wn
//没有填入可选参数
n m
u1,v1
u2,v2
...
un,vn
```

注意

```
return n<=1e7&&m<=1e7&&m>n-1;

if(unique){
    return r-l>=n
}

if(ring&&l<0)
    return ring&&l<0
```

## 无向带环图/无向无环图

必需参数:n (节点数量)，m(边的数量)，ring(是否包含**正环**)

可选参数:l(边权下界)，r(边权上界)，unique(边权是否唯一)，k(每个节点的最大子节点数)

当l，r，unique都被填入时，会构造带边权的图，否则会构造不带边权的图

输入格式与注意同: **有向无环图**

## 负环图

必需参数:n (节点数量)，m(边的数量)，l(边权下界)，r(边权上界)，

可选参数:unique(边权是否唯一)

为了保证生成图的随机性，程序会对图进行随机构造并检查负环。如果超过10次没有构造成功，就会将r设置为0再次构造。

注意:

```
l<0&&abs(l)<=r
```



## 二分图

必需参数:n (节点数量)，m(边的数量)

可选参数:cnt(其中一组节点的数量)，l(边权下界)，r(边权上界)，unique(边权是否唯一)

cnt默认值为n/2

当l，r，unique都被填入时，会构造带边权的图，否则会构造不带边权的图

输入格式与注意同: **有向无环图**

## 仙人掌

必需参数:n (节点数量)

可选参数:l(边权下界)，r(边权上界)，unique(边权是否唯一)

当l，r，unique都被填入时，会构造带边权的图，否则会构造不带边权的图

你不需要填写m(边的数量)

输入格式与注意同: **有向无环图**

## 欧拉图

必需参数:n (节点数量)，m(边的数量)

可选参数:l(边权下界)，r(边权上界)，unique(边权是否唯一),half(是否构造半欧拉图)

当half=1,将会构造半欧拉图

当l，r，unique都被填入时，会构造带边权的图，否则会构造不带边权的图

输入格式与注意同: **有向无环图**

## 菊花图(star_tree)

必需参数:n (节点数量)，m(菊花/重心的数量)

可选参数:l(边权下界)，r(边权上界)，unique(边权是否唯一)

当l，r，unique都被填入时，会构造带边权的图，否则会构造不带边权的图

输入格式与注意同: **有向无环图**

此外注意

```
m<=n
```

## hack std::unoreded_map/set

必需参数:n (数列长度)

输入格式:

第一行:n

第二行n个整数:$a_1,a_2,a_3...,a_n$,

只需诱导解题者将这些整数插入unoreded_map/set即可

## hack spfa

必需参数:n (数列长度)，m(边数)

可选参数:l(边权下界)，r(边权上界)

不当的权值范围可能会导致构造失败，推荐[1,1e9]

输入格式与注意上同



# 如何部署Construct-Helper

## 部署服务器

在下载/Construct/clion/cmake-build-relese/clion

将该文件移动到Linux任意目录,以root用户启动该程序(否者无法运行用户提交的代码)，此时程序会自动在当前目录下创建工作文件，同时监听8080端口



# 如何阅读 Construct-Helper代码

本项目目前正在开发，如果你想要学习一些图的构造方法，请阅读clion/constructOperation.h中的代码。

这里将会介绍项目的整体构思。

整个项目一共有以下代码文件:

```
main.cpp:接收请求，返回数据
base64.cpp base64.h 用于将二进制文件转化为base64编码,主要用于文件传输
constructOperation.h 用于构造图/树数据
fileOperation.h 用于处理项目中涉及到的文件操作
httplib.h 第三方库https://github.com/yhirose/cpp-httplib,是一个多线程http库
json.hpp 第三方库https://github.com/nlohmann/json 用于处理json数据格式
judgeOperation.h 用于运行用户提交的代码
logOperation.h 用于处理日志文件
poolOperation.h 用于实现各类池
tokenOperation.h 用于计算,存储与验证token
userOpeartion.h 项目开发早期遗留,试图以面向对象的方式来处理用户请求，后来改成模块化设计模式，目前主要负责登录注册功能
```

下面将依次介绍各文件

## constructOperation.h

这个头文件包含了所有构造算法的代码以及接口函数work

我们假设传入数据都是合理合法的。事实上在work函数中，将传入数据进行了检测与缺省补充。如果有未考虑周全之处，还望指出。

### #define int long long

在整个constructOperation.h文件中的int都将会被替换为long long.

### struct node_val_int

这是用来记录图或树中边的结构体，权值为整数。u和v代表一条有向边的出发点与结束点，w代表这条边的权值。

### struct n_l_r_unique_val

这是用于便于检查输入数据和补充缺省的结构题，结构体名字即代表了其中包含的权值。

一般来说n代表节点数量，l，r表示数值上下界，unique_val表示数值的上下界

结构体的构造函数将会直接从用户的报文中读取数据，如果缺少必需参数(如n,m)等，会直接返回1,表示传入参数错误。

```
int init(const httplib::Request& req){
	if(!req.has_param("n"))
            return 1;
}
```

而对于可以缺省的参数，会补上相关数据。

对于一般图或树，(构造负环时候会在work的函数中额外进行特判)，缺省值补充为:

权值下界:1

权值上界:$10^9$

是否包含重复权值:false

```
if(!req.has_param("l"))this->l=1;
else this->l=stoll(req.get_param_value("l"));

if(!req.has_param("r"))this->r=1e9;
else this->r=stoll(req.get_param_value("r"));

if(!req.has_param("unique_val"))this->unique_val=0;
else this->unique_val=stoll(req.get_param_value("unique_val"));
```

### get_array_int

功能:获取一个长度为n，权值范围为[l,r]，权值(可以/不可以)重复，的(递增/无序整数)整数数列

对于不可重复序列，需分为两类情况讨论:

数值密度较大的构造情况，若完全使用随机数生成数字，再进行判重。构造的时间回因密度的增加出现指数级的增长。故先储存整个值域，随后用$std::random\_shuffle$对数列进行随机打乱，最后取得前$n$个数值作为构造结果进行输出。

对于数值密度较小的构造情况(很多题目常见的数据约束为$n<=1e5,1<=a_i<=1e9$)，若采用上述储存值域随机打乱在取前$n$项的方法，导致需要储存$1e9$个数字，所占用空间超过一个$G$。但由于数值密度较小，在构造最后一个数字时出现数值重复的几率也只有$1e-4$则可以使用随机数生成数字，边生成边用$map$进行$O(logn)$时间复杂度的判重。

而对于可重复序列,则可以用随机数直接生成$n$个值域中的数字而不需判重.

### get_array_double

功能:获取一个长度为n，权值范围为[l,r]，权值(可以/不可以)重复，的(递增/无序整数)浮点数数列

这里首先需明确，浮点数无法判断是否相等，所以在构造时需要传入一个参数$eps$，当两个浮点数之差的绝对值小于$eps$则认为这两个数相同。

在允许出现相同值的浮点数序列，我们可以用内置的$rand$函数实现构造。

而如果需要构造出不能出现相同值的浮点数序列，则需要特殊的构造方法。

具体构造方法:对于数值密度较大的情况，我们可以用类似于整数序列的处理方法，将值域中合法数字全部列举出来，随后打乱顺序，选取前$n$个数字。

而对于密度较小的情况，我们则不能通过使用$map$来进行去重判断，我们可以一次性生成数十倍于要求的数字，随后进行排序，去重。若去重后元素数量少于$n$（出现这种情况的几率非常小），则重新进行一次构造。

### get_tree_lineval_int

功能:构造一个点数量为$n$,边权值域为$[L,R]$的树

构造方式:枚举点$i=[2,n]$，对于第$i$个点，随机向$[1,i-1]$引出一条边。由此构造的树必然具有拓扑序。



###  get_k_tree

功能:构造K叉树

$K$叉树为每个节点最多只能有$K$棵子树，其构造方式相对简单，只需将节点从小到大枚举，设一变量$cnt$表示接下来会被用作子节点的编号。直至$cnt$枚举至$n$即结束构造。

### get_map_lineval_int_aim_link

功能构造n个节点,m条边，(有/无)环的有向图

构造方法:针对有向无环连通图($DAG$图)，首要是需要保证图连通，故我们需先获取一个树的构造数据。

由于需要保证图无环，我们可以在拓扑序列中随机获取两点，只需保证出发点拓扑编号均小于结束点，即可保证图无环。而想要保证图有环，只需要将出发点与结束点调转即可。

此外，在构造边时仍需根据边密度进行构造。若边密度较低，可以用随机数在拓扑序中选点，再使用$map$进行判重。

若密度较高，可用类似于序列构造的方法，枚举出所有的边，打乱后选取前$m-n+1$个数据。

###  get_map_lineval_int_unaim_link

构造无向有/无环连通图

仅有树是无向无环图，若要构造一个点数为$n$,边数为$m$的无向无环图，若$n>m-1$，那么图无法连通。若$n<m-1$，在保证图连通的情况下，添加任意一条边就会出现环，所以无法保证图无环。当且仅当$n=m-1$时，此时可以构造一棵树满足条件限制，换句话说，**只有树是无向无环图**。

对于无向有环图由上文我们可以知道，只需在树中添加任意多条边即可成无向有环图。故我们可在图中进行随机选点连边就能保证生成无向有环图。此外对于重边的处理方式也与上文相同，若边密度小，可以用随机数+$map$判重，边密度大则可以将边全部添加后进行打乱选择。

###  get_negative_ring

构造负环图

对于构造负环图，为了保证图数据的随机性，我们的构造方法为:构造一个有向带环图，随后用$spfa$进行负环检测，如果检测出负环，则输出，否者重新进行构造。在节点数大于$5e2$的情况下，不出现负环的概率接近于0。

如果不需要保证随机性，可以采用构造一个图后直接向图中挂负环的方式。

$spfa$检测负环原理:

$spfa$算法的一大特点就是每个点在被更新后会重新入队，也就是如果出现了一个负环，负环中的点之间不断更新答案，就会导致负环上的点不断入队再出队。这里可以引入一个定理:入队次数超过节点总数的点必定在环上，因为在$spfa$中一个无负环图针对一个节点最多只能更新节点数次，也就是入队次数不会超过$n$，当入队次数超过$n$就不然存在一个环导致其无限入队出队。

此外有一个判环的小$trick$，常规$spfa$储存入队节点会使用队列，这里改成栈。将新入队的节点放入栈顶，遇到环就会在栈顶连续出栈入栈，直到判到入队次数超过节点总数为止。

### get_dichotomous_chart

构造二分图:

二分图:节点由两个集合组成，且两个集合内部没有边的图。

即存在一种方案，将节点划分成满足以上性质的两个集合。

非连通构造法:构造非连通的二分图，只需在两类节点间随机选边。由此构造出的二分图并不保证连通。

连通构造法:首先构造一棵树保证点的基本连通。随后从根开始进行$dfs$黑白染色，即将与黑色直接相连的点染为白色，与白色直接连通的点染为黑色。由于树的拓扑序我们可以知道，树总是能够黑白染色的。随后我们将节点根据其染色分为两类，再在两类节点间随机连边，即可构造出一个随机率高的连通二分图。

### get_cactus

构造仙人掌

如果某个无向连通图的任意一条边至多只出现在一条简单回路里，我们就称这张图为仙人掌图。

所谓简单回路就是指在图上不重复经过任何一个顶点的回路。

构造仙人掌图:如果采用随机连边的话效率太低，而且生成的图也可能不合法。由于任意一条边至多只会出现在一条简单回路，所以我们可以对于原树进行随机链剖分，选择少量的点向链顶连边即可，最后再用$dfs$判断数据的合法性。牺牲了一部分随机性，但换来了更高的构造效率。

### get_eulerian

构造欧拉图

通过图中所有边恰好一次的通路称为欧拉通路。

通过图中所有边恰好一次的回路称为欧拉回路。

具有欧拉回路的无向图或有向图称为欧拉图。

具有欧拉通路但不具有欧拉回路的无向图或有向图称为半欧拉图。

非形式化地讲，欧拉图就是从任意一个点开始都可以一笔画完整个图，半欧拉图必须从某个点开始才能一笔画完整个图。

构造方法:由"一笔画"的原理我们可以知道，只需构造时使得下一条边的起点始终是上一条边的终点。使得起点与终点均为一个点，其返回结果必然是一个欧拉图，构造半欧拉图亦是同理。

### star_graph(int n, int m, int l, int r, int unique)

有时为了卡掉时间复杂度不正确的树形$DP$解法(如:进行双重循环遍历所有子节点的权值来计算贡献)，并且防止代码中的特判，我们需要让树的随机一个或少数节点密度(度数)很高，以形成类似于菊花图的效果。

构造方法:m为图中星形的数量，首先将这m个点链接成树，将剩下的点向前m个点随机连边即可。

###  hack_unordered_map_GCC6

$std::unordered\_map/std::unordered\_set$是基于哈希的一种数据结构，在数据随机的情况下，其插入，删除，访问均摊时间复杂度为$O(1)$，该数据结构通过对输入值进行哈希，随后用质数进行调制，最终被放置于哈希表中合适的位置。

我们可以通过找到这个质数的列表，随后在$unordered\_map$中大量插入该质数的倍数，以使之开销达到$O(n)$。对于$gcc\ 6$或更早的版本，可以用数字$126271$，而对于$gcc\ 7$或更高的版本，则可以使用数字$107897$。

### hack_spfa

1:生成一个以起点为根的树，生成树尽可能的高，每个点的父亲可以在$max(i-5,1)到i-1$中随机，边权随机，同时计算出每个点的深度$d[i]$。

2:对于剩下对于剩下的边，随机选择两点$a$和$b$，并在$a,b$间构造一条边，边权在$ |d[b]-d[a]| $到 $|d[b]-d[a]|+5$ 随机生成.

这样生成的图中，次短路的条数非常的多，而 $SPFA$ 一旦错误地进入了次短路的分支，就会使得一整棵子树被赋错误的距离，从而在后期不得不重新更新。而由于边权接近，剪枝的效果会受到很大影响。
# 构造算法代码

```c++
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<cmath>
#include<unordered_map>
#include<queue>
#include<stack>
#include<random>
#include<chrono>
using namespace std;
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
int randed_int(int a, int b) {
	return rnd()%(b-a+1)+a;
}

struct node_val_int{
	int u,v,w;//出发点 结束点 边权
};

bool Suitable_for_random(int m,int n){//判断是否适合用随机构造法
	return log(n+1)<1+log((n-m)+1);
}

//构造数列
vector<int> 
get_array(int m, int l, int r, bool unique) {
	vector<int>array;
	int n=r-l+1;
	if (unique) {
		if (r - l + 1 < m)
			return {};//不可能构造
		if (Suitable_for_random(m,n)) {//密度较低,可以使用随机性算法
			unordered_map<int, int>mp;
			for (int i = 1; i <= m; i++) {
				int u;
                do{
                    u = randed_int(l, r);
                }while(mp[u]);
				mp[u] = 1;
				array.push_back(u);
			}
			return array;
		} 
		else { //不适合使用随机性算法进行构造
			for (int i = l; i <= r; i++) {
				array.push_back(i);
			}
			random_shuffle(array.begin(), array.end());
			array.erase(array.begin() + m, array.end());//把m之后的全删
			return array;
		}
	}else{
		for (int i = 1; i <= m; i++) {
			array.push_back(randed_int(l, r));
		}
		return array;
	}	
}

//构造树
vector<node_val_int> 
get_tree(int n, int l, int r, bool unique) {
    if (unique && l + n > r)
        return {};
    vector<node_val_int>g_line;
    vector<int>tree_val = get_array(n - 1, l, r, unique);
    for (int i = 2; i <= n; i++) {
        int fa = randed_int(1, i - 1);
        g_line.push_back({fa, i, tree_val[i - 2]});
    }
    return g_line;
}			

//有向图
vector<node_val_int>
 get_graph(int n, int m, bool ring, int l, int r, bool unique_val) {
    map<pair<int, int>, bool>st;//判断重复
    
    int dag_maxn_line=n*(n-1)/2; //有向无环图的最大边数
    int maxn_line=n*(n-1); //有向环图的最大边数
    if ((!ring&&m>dag_maxn_line)||(ring&&m>maxn_line))//不可能构造
        return {};

    vector<int>map_val = get_array(m,l,r,unique_val);//获取边权
    vector<node_val_int> map_line = get_tree(n,l,r,unique_val);//构建初始的树保证连通
    
    for (auto i:map_line) { //防重边
        st[{i.u, i.v}] = true;
    }
    if(Suitable_for_random(m,ring?maxn_line:dag_maxn_line)){//密度较小,可以rand
        if(ring){//需要对带环图特别构造
        	map_line.push_back({n,1,0});//保证最基本有一个环
        	st[{n,1}]=true;
        	for (int i=n+1;i<=m;i++) {
	        	int u,v;
	        	do{
	        		u=randed_int(1,n),v=randed_int(1,n);
	        	}while(u==v || st[{u,v}]);
	            st[{u, v}] = true;
	            map_line.push_back({u,v,0});   
            }
        }
        if(!ring){
        	for (int i=n;i<=m;i++) {
	        	int u,v;
	        	do{
	        		u=randed_int(1,n),v=randed_int(1,n);
	        		if (u>v)swap(u,v);
	        	}while(u==v || st[{u,v}]);
	            st[{u, v}] = true;
	            map_line.push_back({u,v,0});   
            }
        }
        	
    } else {//过大,枚举后打乱
    	if(!ring){//无环
    		vector<pair<int, int>>tmp;
	        for (int i = 1;i<=n;i++) {
	            for (int j=i+1;j<=n;j++) {
	                tmp.emplace_back(i, j);
	            }
	        }
	        random_shuffle(tmp.begin(), tmp.end());
	        int idx = 0;
	        for (int i = n; i <= m; i++) {
	            while (st[ {tmp[idx].first, tmp[idx].second}]) {
	                idx++;
	            }
	            st[{tmp[idx].first,tmp[idx].second}]=true;
	            map_line.push_back({tmp[idx].first, tmp[idx].second,0});
	        }
    	}
    	if(ring){
    		vector<pair<int, int>>tmp;
	        for (int i = 1;i<=n;i++) {
	            for (int j=1;j<=n;j++) {
	            	if(i==j)continue;
	                tmp.emplace_back(i, j);
	            }
	        }
	        random_shuffle(tmp.begin(), tmp.end());
	        map_line.push_back({n,1,0});//保证有一个环
	        st[{n,1}]=true;
	        int idx = 1;
	        for (int i = n+1; i <= m; i++) {
	            while (st[ {tmp[idx].first, tmp[idx].second}]) {
	                idx++;
	            }
	            st[{tmp[idx].first,tmp[idx].second}]=true;
	            map_line.push_back({tmp[idx].first, tmp[idx].second});
	        }
    	}
    }
    for (int i=0;i<m;i++) {
        map_line[i].w = map_val[i];
    }
    return map_line;
}
//检查是否存在负环
bool 
check_negative_ring(vector<node_val_int> map_line, int n, int m) {
    vector<vector<pair<int,int>>>g(n+1);
    for (auto i : map_line) {
        g[i.u].push_back({i.v, i.w});
    }
    vector<int>st(n + 10), dist(n + 10), cnt(n + 10);
    stack<int>stk;
    for (int i = 1; i <= n; i++)
        dist[i] = 0;
    for (int i = 1; i <= n; i++) {
        stk.push(i);
        st[i] = true;
    }
    while (stk.size()) {
        int t = stk.top();
        stk.pop();
        st[t] = false;
        for (auto i : g[t]) {
            if (dist[i.first] > dist[t] + i.second) {
                dist[i.first] = dist[t] + i.second;
                cnt[i.first] = cnt[t] + 1;
                if (cnt[i.first] >= n)
                    return true;
                if (!st[i.first]) {
                    st[i.first] = true;
                    stk.push(i.first);
                }
            }
        }
    }
    return false;
}		

//二分图
vector<node_val_int>
get_binary(int n,int m,int l,int r,int unique_val){
	vector<node_val_int> map_line = get_tree(n,l,r,unique_val);
	vector<vector<int>>g(n+1);
	vector<int>lset,rset;//设定二分图的两个集合
	for(auto i:map_line){
		g[i.u].push_back(i.v);
	}
	auto dfs=[&](auto &dfs,int u,int fa,int color)->void {
		if(color)lset.push_back(u);
		else rset.push_back(u);
		for(auto i:g[u]){
			if(i==fa)continue;
			dfs(dfs,i,u,color^1);
		}
	};
	dfs(dfs,randed_int(1,n),0,0);

	for(int i=n;i<=m;i++){
		map_line.push_back({lset[randed_int(0,lset.size()-1)],
		rset[randed_int(0,rset.size()-1)],0});
	}
	vector<int>map_val = get_array(m, l, r, unique_val);
	for(int i=0;i<m;i++)map_line[i].w=map_val[i];
	return map_line;
}


//仙人掌
vector<node_val_int>
get_cactus(int n,int l, int r, bool unique_val) {
    int m=n-1;
    
    vector<int>head(n+5),a(n+5),b(n+5),top(n+5),fa(n+5),ver(n*2+5),Next(n*2),vis(n+5);
    int tot=0;
    //链式向前星
    auto add=[&](auto add,int x,int y){
        ver[++tot] = y;
        Next[tot] = head[x];
        head[x] = tot;
    };
    for(int i=2;i<=n;i++){
        a[i-1]=i,b[i-1]=randed_int(1,i-1);
        add(add,a[i - 1], b[i - 1]), add(add,b[i - 1], a[i - 1]);
    }
    int rt =randed_int(1,n);//随机根节点
    auto dfs=[&](auto &dfs,int x,int f,int p)->void {
        top[x] = p, fa[x] = f;
        if (head[x] && ver[head[x]] != f)//随机选择一个节点进行剖分
            dfs(dfs,ver[head[x]], x, p);
        for (int i = Next[head[x]], y; i; i = Next[i]) {
            if ((y = ver[i]) == f)continue;
            dfs(dfs,y, x, y);
        }
    };
    dfs(dfs,rt,0,rt);
    for (int i = 1; i <= n; i++)
        if (!vis[top[i]] && top[i] != i && top[i] != fa[i])
            a[++m] = i, b[m] = top[i], vis[top[i]] = true;
    vector<int>map_val = get_array(m, l, r, unique_val);
    vector<node_val_int>map_line;
    for (int i = 1; i <= m; i++) {
        map_line.push_back({a[i], b[i], map_val[i - 1]});
    }
    return map_line;
}

signed main(){


}
```

## main.cpp

这里主要介绍各接口

Response 

#### register

```
var Request={
	"query":"1", 申请注册
	"user_id":
	"user_password"
}	
```

```
var Response={
	"code": 运行结果,0为正常,其他的为异常
}	
```

#### login

1:

```
var Request={
	"login":"1", 常规账号密码登录
	"user_id":
	"user_password"
}	
```

```
var Response={
	"code": 运行结果,0为正常,其他的为异常
	"token":登录成功后,会返回一个token
}	
```

2:

```
var Request={
	"login":"2", 使用token登录
	"token"
	"user_id"
}	
```

```
var Response={
	"code": 运行结果,0为成功登录,其他的为异常
}	
```

#### query

1:

```
var Request={
	"query":"1", 获取该用户的题目数量以及各题目名
	"user_id"
}	
```

```
var Response={
	"sum":一个整数，表明用户一共的题目数量
	"Title":一个字符串，包含sum个逗号分割的字符串，其中第i项表示第i道题的命名，例:计算素数,小写转大写,花朵的数量
	"code":一个整数,表示程序的运行结果
}	
```

2:



```
var Request={
	"query":"2",获取该用户某个题目的题面信息
	"user_id"
	"Title":题目名
}	
```

```
var Response={
	"txt":为一行字符串，表示该题目的题面
	"code":一个整数,表示程序的运行结果
}	
```

3：

```
var Request={
	"query":"2",获取该用户某个题目的题面信息
	"user_id"
	"Title":题目名
}	
```

```
var Response={
	"txt":为一行字符串，表示该题目的题面
	"code":一个整数,表示程序的运行结果
}	
```

6:



```
var Request={
	"query":"6",获取该某道题的某组数据的输入
	"user_id"
	"Title":题目名
	"data_name"这个数据的名字
}	
```

```
var Response={
	"data":返回的数据
	"code":一个整数,表示程序的运行结果
}	
```

7:



```
var Request={
	"query":"7",获取该某道题的某组数据的输出
	"user_id"
	"Title":题目名
	"data_name"这个数据的名字
}	
```

```
var Response={
	"data":返回的数据
	"code":一个整数,表示程序的运行结果
}	
```

9:



```
var Request={
	"query":"9",获取该某道题的所有数据名
	"user_id"
	"Title":题目名
}	
```

```
var Response={
	"data":返回的数据,以逗号分割
	"code":一个整数,表示程序的运行结果
}	
```



#### add

1:



```
var Request={
	"add":"1",添加一道题
	"user_id"
	"Title":题目名
	"judge_type"题目的类型
}	
```

```
var Response={
	"code":一个整数,表示程序的运行结果
}	
```

2：



```
var Request={
	"add":"2",添加一道组数据
	"user_id"
	"Title":题目名
	"data_name"数据的名字
}	
```

```
var Response={
	"code":一个整数,表示程序的运行结果
}	
```

#### delete

1:



```
var Request={
	"delete":"1",删除一道题
	"user_id"
	"Title":题目名
}	
```

```
var Response={
	"code":一个整数,表示程序的运行结果
}	
```

​	2：



```
var Request={
	"delete":"2",删除一组数据
	"user_id"
	"Title":
	"data_name"
}	
```

```
var Response={
	"code":一个整数,表示程序的运行结果
}	
```

#### 	modify

1:

```
var Request={
	"modify":"1",修改题面
	"user_id"
	"Title":
	"txt":用于修改的数据
}	
```

```
var Response={
	"code":一个整数,表示程序的运行结果
}	
```

#### 	download

2:



```
var Request={
	"download":"2",下载一道题的所有数据
	"user_id"
	"Title":
	
}	
```

```
var Response={
	"code":一个整数,表示程序的运行结果
	"data":base64压缩后的二进制文件
}	
```

#### build

1:



```
var Request={
	"build":"1",自动构造一个输入数据
	"user_id"
	"Title":
	"data_name"
	"type":构造的数据类型
	还有其他参数,根据构造数据类型而定,阅如何使用Construct-Helper的一部分
}	
```

```
var Response={
	"code":一个整数,表示程序的运行结果
	"type":构造数据的类型
	还有其他参数,根据构造数据类型而定,阅如何使用Construct-Helper的一部分
}	
```

2:



```
var Request={
	"build":"2",手动构造一个输入数据
	"user_id"
	"Title":
	"data_name"
}	
```

```
var Response={
	"code":一个整数,表示程序的运行结果
	"info":具体的运行信息
}	
```

3:



```
var Request={
	"build":"3",手动构造一个输出数据
	"user_id"
	"Title":
	"data_name"
	"txt"构造用的代码
}	
```

```
var Response={
	"code":一个整数,表示程序的运行结果
	"info":具体的运行信息
}	
```



#### test

1:

```
var Request={
	"test":"1",测试一个代码是否能AC
	"user_id"
	"Title":
	"data_name"
	"txt"构造用的代码
}	
```

```
var Response={
	"code":一个整数,表示程序的运行结果
	"return":具体的运行信息
}	
```



## judgeOperation

用于运行用户程序，用户的程序将会被放置到../judge_pool文件下运行

同时为了满足多线程的需求，在judge_pool下创建了20个文件夹作为评测单元，在poolOperation.h中实现了一个基于带锁队列的文件池。

使用了seccomp以防止用户代码可能会使用一些危险的系统调用，默认程序的CPU实际限制为5s,实际运行实际限制为6s,同时输出限制1e7个字符，编译器错误日志限制1000个字符

实现参考:https://github.com/QingdaoU/OnlineJudge

## tokenOperation

用哈希来生成token,使用unsigned long long 的自然溢出来减低冲突风险,用 map<ull,string>来存储token和user_id的映射

后续还需要去实现一个队列来删除过期的token



## poolOperation

这个头文件中主要实现了一个用于给judger分配判题空间的文件池，和一个防止多线程冲突的带锁队列模板

带锁队列的pop()是阻塞的，会一直阻塞到分配到判题空间为止。而try_pop是非阻塞的。他们的返回值是一个智能指针。







