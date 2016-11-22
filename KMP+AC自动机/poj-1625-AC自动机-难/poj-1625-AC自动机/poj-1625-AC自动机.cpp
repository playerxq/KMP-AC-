// poj-1625-AC自动机.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include <queue>
#include <map>
#include<iomanip>
#include <ctype.h>
#include <algorithm>
using namespace std;
map<char,int> mp;
int mat[110][110];
int N,M,P;
struct Node
{
	int next[256];
	int fail;
	int index;
	void init()
	{
		memset(next,0,sizeof(next));
		fail = 0;
		index = -1;
	}
} node[110];
int tot;
int insert(char* buf)
{
	int i,len,t;
	len = strlen(buf);
	int p = 0;
	for(i = 0;i<len;i++)
	{
		if(node[p].next[mp[buf[i]]]==0)
		{
			++tot;
			node[tot].init();
			node[p].next[mp[buf[i]]]=tot;
		}
		p = node[p].next[mp[buf[i]]];
	}
	node[p].index = 1;
	return 0;
}
queue<int> Q;
void build_ac()
{
	int i,j,cur,son,p;
	Q.push(0);
	while(!Q.empty())
	{
		p = Q.front();
		Q.pop();
		for(i = 0;i<256;i++)
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
void getMatrix()
{
    for(int i = 0;i <=tot;i++)
       for(int j = 0;j < N;j++)
          if(node[node[i].next[j]].index==-1)
              mat[i][node[i].next[j]]++;
}


//大数类
struct BigInt
{
    const static int mod = 10000;
    const static int DLEN = 4;
    int a[600],len;
    BigInt()
    {
        memset(a,0,sizeof(a));
        len = 1;
    }
    BigInt(int v)
    {
        memset(a,0,sizeof(a));
        len = 0;
        do
        {
            a[len++] = v%mod;
            v /= mod;
        }while(v);
    }
    BigInt(const char s[])
    {
        memset(a,0,sizeof(a));
        int L = strlen(s);
        len = L/DLEN;//每4位一组
        if(L%DLEN)len++;
        int index = 0;
        for(int i = L-1;i >= 0;i -= DLEN)
        {
            int t = 0;
            int k = i - DLEN + 1;
            if(k < 0)k = 0;
            for(int j = k;j <= i;j++)//分割一个单词
                t = t*10 + s[j] - '0';
            a[index++] = t;
        }
    }
    BigInt operator +(const BigInt &b)const
    {
        BigInt res;
        res.len = max(len,b.len);
        for(int i = 0;i <= res.len;i++)
            res.a[i] = 0;
        for(int i = 0;i < res.len;i++)
        {
            res.a[i] += ((i < len)?a[i]:0)+((i < b.len)?b.a[i]:0);
            res.a[i+1] += res.a[i]/mod;
            res.a[i] %= mod;
        }
        if(res.a[res.len] > 0)res.len++;
        return res;
    }
    BigInt operator *(const BigInt &b)const
    {
        BigInt res;
        for(int i = 0; i < len;i++)
        {
            int up = 0;
            for(int j = 0;j < b.len;j++)
            {
                int temp = a[i]*b.a[j] + res.a[i+j] + up;
                res.a[i+j] = temp%mod;
                up = temp/mod;
            }
            if(up != 0)
                res.a[i + b.len] = up;
        }
        res.len = len + b.len;
        while(res.a[res.len - 1] == 0 &&res.len > 1)res.len--;
        return res;
    }
    void output()
    {
        printf("%d",a[len-1]);
        for(int i = len-2;i >=0 ;i--)
            printf("%04d",a[i]);
        printf("\n");
    }
};
char buf[1010];
BigInt dp[2][110];

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	while(scanf("%d%d%d",&N,&M,&P)==3)
	{
		gets(buf);
        gets(buf);
        mp.clear();
		memset(mat,0,sizeof(mat));
		int len = strlen(buf);
        for(int i = 0;i < len;i++)//每个字母
            mp[buf[i]]=i;//字母对应的序号
		tot = 0;
		node[0].init();
		for(int i = 0;i < P;i++)
        {
            gets(buf);
            insert(buf);
        }
		build_ac();
		getMatrix();
		int now = 0;
        dp[now][0] = 1;
        for(int i = 1;i < tot+1;i++)
            dp[now][i] = 0;
        for(int i = 0;i < M;i++)
        {
            now^=1;//now之前的状态保存在now^1取反中
            for(int j = 0;j < tot+1;j++)
                dp[now][j] = 0;
            for(int j = 0;j < tot+1;j++)
                for(int k = 0;k < tot+1;k++)
                    if(mat[j][k] > 0)//可达
                        dp[now][k] = dp[now][k]+dp[now^1][j]*mat[j][k];
        }
        BigInt ans = 0;
        for(int i = 0;i < tot+1;i++)
            ans = ans + dp[now][i];
        ans.output();

	}
}

