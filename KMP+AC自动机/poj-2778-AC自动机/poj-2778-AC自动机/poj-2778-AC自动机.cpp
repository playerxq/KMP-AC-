// poj-2778-AC自动机.cpp : 定义控制台应用程序的入口点。
//
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
#define M 128 
#define Mod 100000
char dna[16];  
struct Node{
    int next[4];
    int fail;
    int count;
    void init()
    {
        memset(next,0,sizeof(next));
        fail=0;
        count=0;
    }
}node[505];
int tot,n;
char S[45];
int Matrix[M][M],R[M][M];  
int MAX(int a,int b)
{
    return a>b?a:b;
}

void chushihua()
{
    tot=0;
    node[0].init();
}
int hashx1(char x)
{
    if(x=='A')
        return 0;
    else if(x=='C')
        return 1;
    else if(x=='G')
        return 2;
    else
        return 3;
}
int insert(char *str)
{
     int p = 0;
     int i=0,index;
     while (str[i])
     {
           index=hashx1(str[i]);
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
        for(i=0;i<4;i++)
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
void MatrixMulti(int a[M][M], int b[M][M])
{
	int i,j,k;  
    __int64 tmp;  
    int c[M][M]={0};  
    for(i=0;i<=tot;i++){  
        for(j=0;j<=tot;j++){  
            for(k=0;k<=tot;k++){  
                tmp=((__int64)a[i][k])*((__int64)b[k][j]);  
                if(tmp>=Mod)  
                    tmp%=Mod;  
                c[i][j]+=tmp;  
            }  
        }  
    }  
    for(i=0;i<=tot;i++){  
        for(j=0;j<=tot;j++)  
            a[i][j]=c[i][j];  
    } 
}
void GetResMatrix()  
{  
    int i;  
    for(i=0;i<=tot;i++)  
        R[i][i]=1;  
    while(n){  
        if(n&1) MatrixMulti(R,Matrix);  
        MatrixMulti(Matrix,Matrix);  
        n>>=1;  
    }  
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int res;  
    int i,m;  
    scanf("%d%d",&m,&n);  
	chushihua();
    while(m--){  
        scanf("%s",dna);  
        insert(dna);  
    }  
    build_ac();  
    //get_matrix();  
    GetResMatrix();  
    for(i=0,res=0;i<=tot;i++){  
        res+=R[0][i];  
        if(res>=Mod) res%=Mod;  
    }  
    printf("%d\n",res);  
    return 0;
}



