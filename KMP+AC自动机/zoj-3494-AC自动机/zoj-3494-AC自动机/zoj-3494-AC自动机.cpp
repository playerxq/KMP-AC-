// zoj-3494-AC自动机.cpp : 定义控制台应用程序的入口点。
//A B内有多少串的BCD码不含预定义的模式串
#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include <queue>
#include<iomanip>
#include <ctype.h>
#include <algorithm>
using namespace std;
struct Node
{
	int fail;
	int next[2];
	int index;
	void init()
    {
        memset(next,0,sizeof(next));
        fail=0;
        index=-1;
    }
} node[2010];
int tot;
int insert(char buf[])
{
     int p = 0;
     int i=0;
	 int len = strlen(buf);
     for(;i<len;i++)
     {
		   if (node[p].next[buf[i]-'0']==0)
		   {
			   ++tot;
			   node[tot].init();
			   node[p].next[buf[i]-'0']=tot;
		   }
           p=node[p].next[buf[i]-'0'];
     }
     node[p].index=1;//价值
     return 0;
}
queue<int> Q;
void build_ac()
{
	int i,son,cur,p;
	Q.push(0);
	while(!Q.empty())
	{
		p=Q.front();
        Q.pop();
		for(i = 0;i<2;i++)
		{
			if(node[p].next[i]!=0)
			{
				cur = node[p].fail;
				son = node[p].next[i];
				if(p==0)
					node[son].fail = 0;
				else
				{
					while(cur&&node[cur].next[i]==0)
						cur = node[cur].fail;
					node[son].fail = node[cur].next[i];
					if(node[node[son].fail].index==1)
						node[son].index=1;
				}
				Q.push(son);
			}
			else//使用fail指向的后缀的next来拼接
                node[p].next[i]=node[node[p].fail].next[i];
		}
	}
}
int bcd[2010][10];//bcd[i][j]表示从i节点开始加上j的BCD码字后到达的节点
int change(int pre,int num)//之前状态pre也即节点  加数字num
{
    if(node[pre].index==1)//是关键字结尾 不能再加数字了
		return -1;
    int cur = pre;
    for(int i = 3;i >= 0;i--)//考虑num每一位
    {
		if(node[node[cur].next[(num>>i)&1]].index==1)//枚举对应的cur的每个孩子 看是否构造出关键字
			return -1;
        cur = node[cur].next[(num>>i)&1];//这一位可以加于cur之后
    }
    return cur;//pre加上num后处于的节点位置
}
const int MOD = 1000000009;
long long dp[210][2010];//dp[i][j]表示长度为i，位于结点j的个数 
int bit[210];//上限串

//从根节点开始沿着ac树走 若有预定义串 相当于存在一条根到叶子的路径
//bcd数组标识了从节点如何走可以避免走到叶子  s定义了当前所在的节点  s的变化就是要确定的数的变化
//bcd数组第二维为10 相当于在ac树中沿0-9的BCD码来走 跳转到相应节点
//dp数组就是长度为i,在节点j处存在的不超过目标串的且不包含预定义串的数字个数

//目标串长度pos是已知的  按位从高到低位赋值 最大的肯定是最高位为9 最高位加0相当于加前导0 将所有pos长度内小于目标串的数字串个数求出
//数位DP，长度为pos,当前状态为s,flag最高位是否有限制，z是否有前导0  

//当前考虑到pos位 从高位到低位考虑 目标位为bit[pos]
long long dfs(int pos,int s,bool flag,bool z)
{
    if(pos == -1)
		return 1;
    if(!flag && dp[pos][s]!=-1)return dp[pos][s];//没有限制  若前面有前导0 则要求会放宽  dp依然正确 前面无前导0 由于flag=0 依然正确
    //有限制时  最高位不一定与之前计算的dp[pos][s]中的所得串相一致 需要重新计算
	long long ans = 0;
	//首先考虑当前最高位放0
	//有前导0 当前放0相当于继续制造前导0
    if(z)
    {//增加前导0 数字实际上没变  因此节点s不变
        ans += dfs(pos-1,s,flag && bit[pos]==0,true);//若目标对应位=0 则限制flag传递给递归 否则当前位设置的0小于目标对应位 不会有限制
        ans %= MOD;
    }
    else//不再有前导0
    {//首先考虑最高位加0 节点s走0方向 此时0作为十进制数 BCD码0000的走法已经在change中算出
        if(bcd[s][0]!=-1)//可以走
			ans += dfs(pos-1,bcd[s][0],flag && bit[pos]==0,false);//bit[pos]=0说明添加的数与目标一样 如果之前也有限制 那么限制将传递到递归中 否则之前无限制 递归也不应该有限制 若bit[pos]不为0 显然添加的数小于目标 则递归低位也不会有限制
        ans %= MOD;//累计当前位加0的可取的数字串个数
    }
    int end = flag?bit[pos]:9;
    for(int i = 1;i<=end;i++)
    {
        if(bcd[s][i]!=-1)//保证不会走到叶子
        {
            ans += dfs(pos-1,bcd[s][i],flag&&i==end,false);//当i=end即到达上限 之前的限制会传递给递归中的低位 否则i没有到达上限 递归自然不会有限制
            ans %=MOD;
        }
    }
    if(!flag && !z)//长度为pos 起始节点为s向低位扩展出ans个不超过目标的串 这些串若被用作之后的计算  需要保证不依赖于pos以上的高位 即flag与z为0
		dp[pos][s] = ans;//若flag=0但前导有0 说明此时从s的扩展0-9依赖于前面的0 也就是说当前面不为前导0时不一定可以从0-9 故不能作为dp的值
	//只有当前面没有前导0的限制 且flag=0时 才是pos位s节点处的所有扩展
    return ans;
}


long long calc(char s[])
{
    int len = strlen(s);
    for(int i = 0;i < len;i++)
        bit[i] = s[len-1-i]-'0';//高低位反转  上限串为A-1或者B
    return dfs(len-1,0,1,1);
}
char str[210];

void pre_init()
{
    for(int i = 0;i <=tot;i++)
        for(int j = 0;j <10;j++)
            bcd[i][j] = change(i,j);
}


int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int T;
    scanf("%d",&T);
    int n;
    while(T--)
    {
		node[0].init();
		tot = 0;
        scanf("%d",&n);
        for(int i = 0;i < n;i++)//预定义的模式串
        {
            scanf("%s",str);
            insert(str);
        }
        build_ac();
        pre_init();
        memset(dp,-1,sizeof(dp));
        int ans = 0;
        scanf("%s",str);//A
        int len = strlen(str);
        for(int i = len -1;i >=0;i--)//高精度减法  从len-1位开始减1 则0为9 直到第一个不为0的减一 可能会在最高位产生一个前导0
        {
            if(str[i]>'0')
            {
                str[i]--;
                break;
            }
            else str[i] = '9';
        }
        ans -= calc(str);//去除A以内即A-1不包含关键字的串
        ans %=MOD;
        scanf("%s",str);
        ans += calc(str);//再加上B以内不包含关键字的串  得到A,B之间不包含关键字的串
        ans %=MOD;
        if(ans < 0)ans += MOD;
        printf("%d\n",ans);
    }
    return 0;

}



