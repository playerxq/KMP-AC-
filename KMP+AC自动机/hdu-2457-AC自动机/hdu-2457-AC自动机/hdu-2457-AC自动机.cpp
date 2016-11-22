// hdu-2457-AC自动机.cpp : 定义控制台应用程序的入口点。
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
int tot;
const int INF = 0x3f3f3f3f;

struct Node
{
	int fail;
	int next[4];
	int index;
	void init()
    {
        memset(next,0,sizeof(next));
        fail=0;
		index = 0;
    }
} node[100];
int hashx(char c)
{
	if(c=='A')
		return 0;
	else if(c=='C')
		return 1;
	else if(c=='G')
		return 2;
	else
		return 3;
}
int insert(char *str)//病毒id
{
     int p = 0;
     int i=0,index;
	 int len = strlen(str);
     for(;i<len;i++)
     {
           index=hashx(str[i]);
		   if (node[p].next[index]==0)
		   {
			   ++tot;
			   node[tot].init();
			   node[p].next[index]=tot;
		   }
           p=node[p].next[index];
     }
	 node[p].index = 1;
     return 0;
}
queue<int> Q;
int dp[1010][100];
void build_ac()
{
	int i,j,son,cur,p;
	Q.push(0);
	while(!Q.empty())
	{
		p=Q.front();
        Q.pop();
		for(i = 0;i<=3;i++)
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
						node[son].index = 1;
				}
				Q.push(son);
			}
			else//使用fail指向的后缀的next来拼接
                node[p].next[i]=node[node[p].fail].next[i];
		}
	}
}
int solve(char buf[])
{
	int len = strlen(buf);
    for(int i = 0;i <= len;i++)
        for(int j = 0;j < tot+1;j++)
            dp[i][j] = INF;
	dp[0][0]=0;
	for(int i = 0;i<len;i++)
	{
		for(int j = 0;j<=tot;j++)
		{
			if(dp[i][j]==INF)
				continue;
			for(int k = 0;k<4;k++)
			{
				int news = node[j].next[k];
				if(node[news].index==1)
					continue;
				int temp;
				if(k==hashx(buf[i]))
					temp = dp[i][j];//原来串的字符不会产生关键字  则什么也不改变
				else
					temp = dp[i][j]+1;//将原来的buf[i]改成k代表的字符
				dp[i+1][news] = min(temp,dp[i+1][news]);
			}
		}
	}
	int ans = INF;
    for(int j = 0;j <=tot;j++)
        ans = min(ans,dp[len][j]);
    if(ans == INF)ans = -1;
    return ans;

}
char buf[1010];

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout); 
	int n;
    int iCase = 0;
    while ( scanf("%d",&n) == 1 && n)
    {
        iCase++;
		tot = 0;
        node[0].init();
        while(n--)
        {
            scanf("%s",buf);
            insert(buf);
        }
        build_ac();
        scanf("%s",buf);
        printf("Case %d: %d\n",iCase,solve(buf));
    }
    return 0;
}





