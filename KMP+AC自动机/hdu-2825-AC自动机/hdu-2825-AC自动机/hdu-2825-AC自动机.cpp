// hdu-2825-AC自动机.cpp : 定义控制台应用程序的入口点。
//
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
const int MOD=20090717;
int n,m,k;

int dp[30][110][1<<10];//dp[i][j][k]表示当前长度为i 树上走到j点 m个单词集的使用情况是k

struct Node
{
	int fail;
	int next[26];
	int index;
	void init()
    {
        memset(next,0,sizeof(next));
        fail=0;
        index=0;
    }
} node[110];
int tot;
int num[5000];

int insert(char buf[],int id)
{
     int p = 0;
     int i=0;
	 int len = strlen(buf);
     for(;i<len;i++)
     {
		   if (node[p].next[buf[i]-'a']==0)
		   {
			   ++tot;
			   node[tot].init();
			   node[p].next[buf[i]-'a']=tot;
		   }
           p=node[p].next[buf[i]-'a'];
     }
     node[p].index|=(1<<id);//价值
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
		for(i = 0;i<26;i++)
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
					node[son].index|=node[node[son].fail].index;
				}
				Q.push(son);
			}
			else//使用fail指向的后缀的next来拼接
                node[p].next[i]=node[node[p].fail].next[i];
		}
	}
}
int solve()
{
	for(int i = 0;i<=n;i++)
	{
		for(int j = 0;j<=tot;j++)
		{
			for(int k = 0;k<(1<<(m));k++)
			{
				dp[i][j][k]=0;
			}
		}
	}
	dp[0][0][0]=1;
	for(int i = 0;i<n;i++)
	{
		for(int j = 0;j<=tot;j++)
		{
			for(int k = 0;k<(1<<(m));k++)
			{
				if(dp[i][j][k])
				{
					for(int c = 0;c<26;c++)//新扩展一个字母
					{
						int newi = i+1;
						int newj = node[j].next[c];
						int newk = k|(node[newj].index);//如果新扩展的字母与之前的串可以构成一个单词
						dp[newi][newj][newk] += dp[i][j][k];
                        dp[newi][newj][newk]%=MOD;

					}
				}
			}
		}
	}
	int ans = 0;
    for(int p = 0;p < (1<<m);p++)
    {
        if(num[p] < k)continue;
        for(int i = 0;i <=tot;i++)
        {
            ans = (ans + dp[n][i][p])%MOD;
        }
    }
    return ans;
}
char buf[20];

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	for(int i=0;i<(1<<10);i++)
    {
        num[i] = 0;
        for(int j = 0;j < 10;j++)
            if(i & (1<<j))
                num[i]++;
    }
    while(scanf("%d%d%d",&n,&m,&k)==3)
    {
        if(n== 0 && m==0 &&k==0)break;
        tot = 0;
		node[0].init();
        for(int i = 0;i < m;i++)
        {
            scanf("%s",buf);
            insert(buf,i);
        }
        build_ac();
        printf("%d\n",solve());
    }
    return 0;

}

