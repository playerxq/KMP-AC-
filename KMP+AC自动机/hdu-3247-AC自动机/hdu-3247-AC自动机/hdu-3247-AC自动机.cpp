// hdu-3247-AC自动机.cpp : 定义控制台应用程序的入口点。
//合并文件使得长度最短且不含病毒关键字
//在trie树基础上，根据关键字的id号构建可达状态，避开病毒节点
//可达状态记录了文件关键字节点转移长度  利用dp状态压缩即可
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
int tot;
const int INF = 0x3f3f3f3f;

struct Node
{
	int fail;
	int next[2];
	int index;
	void init()
    {
        memset(next,0,sizeof(next));
        fail=0;
		index = 0;
    }
} node[60010];
int insert(char *str, int id)
{
     int p = 0;
     int i=0,index;
	 int len = strlen(str);
     for(;i<len;i++)
     {
           index=str[i]-'0';
		   if (node[p].next[index]==0)
		   {
			   ++tot;
			   node[tot].init();
			   node[p].next[index]=tot;
		   }
           p=node[p].next[index];
     }
	 node[p].index = id;
     return 0;
}
queue<int> Q;
void build_ac()
{
	int i,j,son,cur,p;
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
					if(node[node[son].fail].index!=0)
						node[son].index = node[node[son].fail].index;
				}
				Q.push(son);
			}
			else//使用fail指向的后缀的next来拼接
                node[p].next[i]=node[node[p].fail].next[i];
		}
	}
}
int g[11][11];
int dp[1025][11];//dp[i][j]为文件状态i 考虑到j关键字时的最短总长
int cnt;
int pos[11];
int dis[60010];
void bfs(int k)//k为文件节点
{
    queue<int>q;
    memset(dis,-1,sizeof(dis));
    dis[pos[k]] = 0;
    q.push(pos[k]);//节点入队列
    while(!q.empty())
    {
        int now = q.front();
        q.pop();
        for(int i = 0; i< 2;i++)//对文件节点的孩子
        {
			int tmp = node[now].next[i];
			if(dis[tmp]<0 && node[tmp].index >= 0)//不是病毒节点
            {
                dis[tmp] = dis[now] + 1;//可达的
                q.push(tmp);
            }
        }
    }
    for(int i = 0;i < cnt;i++)
        g[k][i] = dis[pos[i]];
}

int solve(int n)
{
    pos[0] = 0;
    cnt = 1;
    for(int i = 0;i <=tot;i++)
		if(node[i].index> 0)//是个文件
           pos[cnt++] = i;//每个文件字的终点节点
    for(int i = 0; i < cnt;i++)
        bfs(i);//从文件节点搜索 计算文件节点之间的可达情况

    for(int i = 0;i < (1<<n);i++)//文件包含状态  全1时为全部包含
        for(int j = 0;j < cnt;j++)//每个文件节点
            dp[i][j] = INF;
    dp[0][0] = 0;
    for(int i = 0;i <(1<<n);i++)
        for(int j = 0;j < cnt;j++)
            if(dp[i][j]<INF)
            {
                for(int k = 0;k < cnt;k++)
                {
                    if(g[j][k] < 0)continue;
                    if( j == k)continue;
					dp[i|node[pos[k]].index][k] = min(dp[i|node[pos[k]].index][k],dp[i][j]+g[j][k]);
                }
            }
    int ans = INF;
    for(int j = 0;j < cnt;j++)
        ans = min(ans,dp[(1<<n)-1][j]);
    return ans;
}

char buf[1010];

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout); 
	int n,m;
    while(scanf("%d%d",&n,&m) == 2)
    {
        if(n == 0 && m == 0)break;
        tot = 0;
		node[0].init();
        for(int i = 0;i < n;i++)
        {
            scanf("%s",buf);
            insert(buf,1<<i);
        }
        for(int i = 0;i < m;i++)
        {
            scanf("%s",buf);
            insert(buf,-1);
        }
        build_ac();
        printf("%d\n",solve(n));
    }
    return 0;
}







