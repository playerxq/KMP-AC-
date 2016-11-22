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
const int N=505;  
const int M=10011;  
struct Node
{
	int fail;
	int next[100];
	int index;
	void init()
    {
        memset(next,0,sizeof(next));
        fail=0;
        index=0;
    }
} node[200*N];
int tot;
int insert(char *str,int id)
{
     int p = 0;
     int i=0,index;
     while (str[i])
     {
           index=str[i]-' ';
		   if (node[p].next[index]==0)
		   {
			   ++tot;
			   node[tot].init();
			   node[p].next[index]=tot;
		   }
           p=node[p].next[index];
           i++;
     }
     node[p].index=id;//价值
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
		for(i = 0;i<100;i++)
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
int ss[2*N][3],k[2*N];  
void query(char* str, int zz)//zz为网站id
{
	int now,temp;
	int i,t;
	int flag[N];
	i = k[zz]=0;//zz号网站含有病毒数目
	now = 0;
	memset(flag,0,sizeof(flag));  
	while(str[i])
	{
		t = str[i]-' ';
		while(now&&node[now].next[t]==0) now = node[now].fail;
		now = node[now].next[t];
		if(now==0)
			now = 0;
		temp = now;
		while(temp&&!flag[node[temp].index])
		{
			if(node[temp].index)
			{
				ss[zz][k[zz]++] = node[temp].index;
				flag[node[temp].index] = 1;
			}
			temp = node[temp].fail;
		}
		if(k[zz]>=3)
			break;
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
    char str1[205],str2[M];  
    while(scanf("%d",&n)!=-1)  
    {  
        tot=0; 
		node[0].init(); 
        for(i=1;i<=n;i++)    {scanf("%s",str1);insert(str1,i);}  
  
        build_ac();  
  
        cnt=0;  
        scanf("%d",&m);  
        for(i=1;i<=m;i++)  
        {  
            scanf("%s",str2);  
            query(str2,i);  
            if(k[i])    {sort(ss[i],ss[i]+k[i]);cnt++;}  
        }  
        for(i=1;i<=m;i++)  
        {  
            if(!k[i])   continue;  
            printf("web %d:",i);  
            for(l=0;l<k[i];l++)  printf(" %d",ss[i][l]);  
            printf("\n");  
        }  
        printf("total: %d\n",cnt);  
    }  
    return 0;
}

