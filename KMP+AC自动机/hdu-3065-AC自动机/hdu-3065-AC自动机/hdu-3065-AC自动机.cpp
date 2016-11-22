// hdu-3065-AC自动机.cpp : 定义控制台应用程序的入口点。
//
// hdu-2896-AC自动机.cpp : 定义控制台应用程序的入口点。
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
const int M=10011;  
#define MAXN 2000010
#define MAXM 50000
#define MAXL 128
char str[MAXN], dic[MAXM][60];
int size, k[MAXM];

struct Node
{
	int fail;
	int next[128];
	int index;
	void init()
    {
        memset(next,0,sizeof(next));
        fail=0;
		index = 0;
    }
} node[50005];
int tot;
int insert(char *str,int id)//病毒id
{
     int p = 0;
     int i=0,index;
     while (str[i])
     {
           index=str[i];
		   if (node[p].next[index]==0)
		   {
			   ++tot;
			   node[tot].init();
			   node[p].next[index]=tot;
		   }
           p=node[p].next[index];
           i++;
     }
	 node[p].index=id;
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
		for(i = 'A';i<='Z';i++)
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
				}
				Q.push(son);
			}
			else//使用fail指向的后缀的next来拼接
                node[p].next[i]=node[node[p].fail].next[i];
		}
	}
}
void query(char* str)
{
	int now,temp;
	int i,t;
	i = 0;
	now = 0;  
	while(str[i])
	{
		t = str[i];
		while(now&&node[now].next[t]==0) now = node[now].fail;
		now = node[now].next[t];
		if(now==0)
			now = 0;
		temp = now;
		while(temp)
		{
			k[node[temp].index]++;
			temp = node[temp].fail;
		}
		i++;
	}
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int n,m;  
    int i,l;  
    int cnt;  
     
    while(scanf("%d",&n)!=-1)  
    {  
        tot=0; 
		node[0].init(); 
		memset(k, 0, sizeof(k));

        for(i=1;i<=n;i++)    
		{
			scanf(" %s", dic[i]);
			insert(dic[i],i);
		}  
  
        build_ac();  
        scanf("%s",str);
		query(str);
        for(i=1;i<=n;i++)  
        {  
            if(!k[i])   continue;
			printf("%s: %d\n", dic[i], k[i]);  
        }
    }  
    return 0;
}



