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
struct Node
{
	int fail;
	int next[256];
	int index;
	void init()
    {
        memset(next,0,sizeof(next));
        fail=0;
        index=-1;
    }
} node[40000];
int tot;
unsigned char buf[2050];
int toto;
char str[4000];
unsigned char s[4000];
int insert(unsigned char buf[],int len,int id)
{
     int p = 0;
     int i=0;
     for(;i<len;i++)
     {
		   if (node[p].next[buf[i]]==0)
		   {
			   ++tot;
			   node[tot].init();
			   node[p].next[buf[i]]=tot;
		   }
           p=node[p].next[buf[i]];
     }
     node[p].index=id;//价值
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
				}
				Q.push(son);
			}
			else//使用fail指向的后缀的next来拼接
                node[p].next[i]=node[node[p].fail].next[i];
		}
	}
}
bool used[520];
int query(unsigned char buf[], int len,int n)
{
	int now;
	int i,t;
	memset(used,false,sizeof(used));
	i = 0;//zz号网站含有病毒数目
	now = 0; 
	for(;i<len;i++)
	{
		now = node[now].next[buf[i]];
		int temp = now;
		while(temp)
		{
			if(node[temp].index!=-1)
				used[node[temp].index]=true;
			temp = node[temp].fail;
		}
	}
	int res = 0;
	for(i = 0;i<n;i++)
		if(used[i])
			res++;
	return res;
}

unsigned char Get(char ch)
{
    if( ch>='A'&&ch<='Z' )return ch-'A';
    if( ch>='a'&&ch<='z' )return ch-'a'+26;
    if( ch>='0'&&ch<='9' )return ch-'0'+52;
    if( ch=='+' )return 62;
    else return 63;
}
void change(unsigned char str[],int len)
{
    int t=0;
    for(int i=0;i<len;i+=4)
    {
        buf[t++]=((str[i]<<2)|(str[i+1]>>4));
        if(i+2 < len)
            buf[t++]=( (str[i+1]<<4)|(str[i+2]>>2) );
        if(i+3 < len)
            buf[t++]= ( (str[i+2]<<6)|str[i+3] );
    }
    toto=t;
}

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int n,m;
    while(scanf("%d",&n) == 1)
    {
        node[0].init();
		tot = 0;
        for(int i = 0;i < n;i++)
        {
            scanf("%s",str);
            int len = strlen(str);
            while(str[len-1]=='=')len--;
            for(int j = 0;j < len;j++)
            {
                s[j] = Get(str[j]);
            }
            change(s,len);
            insert(buf,toto,i);
        }
        build_ac();
        scanf("%d",&m);
        while(m--)
        {
            scanf("%s",str);
            int len=strlen(str);
            while(str[len-1]=='=')len--;
            for(int j = 0;j < len;j++)
                s[j] = Get(str[j]);
            change(s,len);
            printf("%d\n",query(buf,toto,n));
        }
        printf("\n");
    }
    return 0;
}

