// hdu-3341-AC�Զ���.cpp : �������̨Ӧ�ó������ڵ㡣
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
int hashx[41][41][41][41];
int ta,tc,tg,tt;
int dp[15000][505];
char keyword[15];
char S[45];

int MAX(int a,int b)
{
    return a>b?a:b;
}

void chushihua()
{
    memset(dp,-1,sizeof(dp));
    ta=tc=tg=tt=0;
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
     node[p].count++;//��β����
     return 0;
}
queue<int> Q;
void build_ac()//����trieͼ
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
                if(p==0)//��
                    node[son].fail=0;
                else
                {
                    while(cur&&node[cur].next[i]==0)
                        cur=node[cur].fail;
                    node[son].fail=node[cur].next[i];
                }
                if(node[node[son].fail].count)//��׺��ĳ���ؼ��ֽ�β
                    node[son].count+=node[node[son].fail].count;//��ǰ�ڵ�Ҳ������Ӧ��β��Ŀ
                Q.push(son);
            }
            else//ʹ��failָ��ĺ�׺��next��ƴ��
                node[p].next[i]=node[node[p].fail].next[i];
        }
    }
}
void yasuo()//����ѹ��
{
    int i,j,k,l,num=0;
    for(i=0;S[i]!='\0';i++)
        if(S[i]=='A')
            ta++;
        else if(S[i]=='C')
            tc++;
        else if(S[i]=='G')
            tg++;
        else
            tt++;
    for(i=0;i<=ta;i++)
        for(j=0;j<=tc;j++)
            for(k=0;k<=tg;k++)
                for(l=0;l<=tt;l++)
                    hashx[i][j][k][l]=num++;
}
void solve(int zuhao)
{
   int i,j,k,l,p,q,son,x1,x2,maxn=0;
   dp[0][0]=0;
   for(i=0;i<=ta;i++)
       for(j=0;j<=tc;j++)
           for(k=0;k<=tg;k++)
               for(l=0;l<=tt;l++)
               {
                   if(i+j+k+l==0)
                       continue;
                   x1=hashx[i][j][k][l];//��ѹ
                   for(p=0;p<=tot;p++)//����trie��ÿ���ڵ�p
                   {
                       for(q=0;q<4;q++)//����p �ĺ��
                       {
                           if(q==0&&i-1>=0)//��һ������ A�ַ�
                               x2=hashx[i-1][j][k][l];//֮ǰ��״̬
                           else if(q==1&&j-1>=0)
                               x2=hashx[i][j-1][k][l];
                           else if(q==2&&k-1>=0)
                               x2=hashx[i][j][k-1][l];
                           else if(q==3&&l-1>=0)
                               x2=hashx[i][j][k][l-1];
                           else
                               continue;
                           if(dp[x2][p]==-1)//�ߵ��ڵ�pʱ״̬��x2
                               continue;
                           son=node[p].next[q];
                           dp[x1][son]=MAX(dp[x1][son],dp[x2][p]+node[son].count);
                           if(dp[x1][son]>maxn)
                               maxn=dp[x1][son];
                       }
                   }
               }
   printf("Case %d: ",zuhao);
   printf("%d\n",maxn);
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int zuhao=0;
    while(scanf("%d",&n)!=EOF&&n)
    {
        zuhao++;
        chushihua();
        getchar();
        while(n--)
        {
            scanf("%s",keyword);
            insert(keyword);
        }
        build_ac();
        scanf("%s",S);
        yasuo();
        solve(zuhao);
    }
    return 0;
}

