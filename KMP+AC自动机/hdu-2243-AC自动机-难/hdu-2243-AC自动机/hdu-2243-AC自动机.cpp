// hdu-2243-AC自动机.cpp : 定义控制台应用程序的入口点。
//在poj2778上改进为包含关键字的串数 则先求不包含的  再用总的减去之
//26^1+26^2+26^3+...+26^n-(A^1+A^2+A^3+...+A^n)
//注意与poj2778不同处还有对不包含的串  应计算长度为1:L的A^i次幂求和  而不只是A^L
//即求(A^1+A^2+A^3+...+A^L)
//对A增加一列1 求L次方  第0行求和-1即为和
#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <string.h>
#include <math.h>
#include <queue>
#include<iomanip>
#include <ctype.h>
#include <algorithm>
using namespace std;
#define M 50 
char sss[10];  
unsigned long long a[2][2],b[2][2];
struct Node{
    int next[26];
    int fail;
    int count;
    void init()
    {
        memset(next,0,sizeof(next));
        fail=0;
        count=0;
    }
}node[505];
int tot,n,l;
unsigned long long Matrix[M][M],R[M][M];

void chushihua()
{
    tot=0;
    node[0].init();
	memset(Matrix,0,sizeof(Matrix));
	memset(R,0,sizeof(R));
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
}
int insert(char *str)
{
     int p = 0;
     int i=0,index;
     while (str[i])
     {
           index=str[i]-'a';
		   if (node[p].next[index]==0)
		   {
			   node[++tot].init();
			   node[p].next[index]=tot;
		   }
           p=node[p].next[index];
           i++;
     }
     node[p].count++;//结尾次数
     return 0;
}
queue<int> Q;
void build_ac()//建立trie图
{
    int i,p,cur,son;
    Q.push(0);
    while(!Q.empty())
    {
        p=Q.front();
        Q.pop();
        for(i=0;i<26;i++)
        {
            if(node[p].next[i]!=0)
            {
                son=node[p].next[i];
                cur=node[p].fail;
                if(p==0)//根
                    node[son].fail=0;
                else
                {
                    while(cur&&node[cur].next[i]==0)
                        cur=node[cur].fail;
                    node[son].fail=node[cur].next[i];
                }
                if(node[node[son].fail].count)//后缀是某个关键字结尾
                    node[son].count+=node[node[son].fail].count;//当前节点也加上相应结尾数目
                Q.push(son);
            }
            else//使用fail指向的后缀的next来拼接
                node[p].next[i]=node[node[p].fail].next[i];
			if(!node[node[p].next[i]].count) Matrix[p][node[p].next[i]]++;
        }
    }
}
void expend()
{
	for(int i = 0;i<=tot+1;i++)
		Matrix[i][tot+1]=1;
}
void MatrixMulti(unsigned long long a[M][M], unsigned long long b[M][M])
{
	int i,j,k;  
    unsigned long long tmp;  
    unsigned long long c[M][M]={0};  
    for(i=0;i<=tot+1;i++){  
        for(j=0;j<=tot+1;j++){  
            for(k=0;k<=tot+1;k++){  
                tmp=(unsigned long long)(((unsigned long long)a[i][k])*((unsigned long long)b[k][j]));
                c[i][j]+=tmp;  
            }  
        }  
    }  
    for(i=0;i<=tot+1;i++){  
        for(j=0;j<=tot+1;j++)  
            a[i][j]=c[i][j];  
    } 
}
void GetResMatrix(unsigned long long k)  
{  
    int i;  
    for(i=0;i<=tot+1;i++)  //构造单位阵
        R[i][i]=1;  
    while(k){  
        if(k&1) MatrixMulti(R,Matrix);  
        MatrixMulti(Matrix,Matrix);  
        k>>=1;  
    }  
}
void MatrixMulti_x(unsigned long long a[2][2], unsigned long long b[2][2])
{
	int i,j,k;  
    unsigned long long tmp;  
    unsigned long long c[2][2]={0};  
    for(i=0;i<=1;i++){  
        for(j=0;j<=1;j++){  
            for(k=0;k<=1;k++){  
                tmp=(unsigned long long)((a[i][k])*(b[k][j]));
                c[i][j]+=tmp;  
            }  
        }  
    }  
    for(i=0;i<=1;i++){  
        for(j=0;j<=1;j++)  
            a[i][j]=c[i][j];  
    }
}
void get_a_pow(unsigned long long k)
{
	for(int i = 0;i<2;i++)
	{
		b[i][i]=1;
	}
	while(k)
	{
		if(k&1) MatrixMulti_x(b,a);
		MatrixMulti_x(a,a);
		k>>=1;
	}
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	unsigned long long res;  
    int i,L;  
    while(scanf("%d%d",&n,&l)!=EOF)
	{
		chushihua();
		L = l;
		while(n--){  
			scanf("%s",sss);  
			insert(sss);  
		}  
		build_ac();  
		expend();  
		GetResMatrix(L);  
		//计算不包括关建字的串
		for(i=0,res=0;i<=tot+1;i++){  
			res+=R[0][i];
		}
		res--;
		a[0][0]=26;
		a[1][0]=a[1][1]=1;
		get_a_pow(L);
		unsigned long long ans = b[1][0]+b[0][0];//1+26+26^2+...+26^L
		ans--;
		ans-=res;
		cout<<ans<<endl;
	}
    return 0;
}





