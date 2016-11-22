// hdu-2296-AC自动机.cpp : 定义控制台应用程序的入口点。
//dp[i][j]表示长度为i的时候，在Trie上的第j个结点时的最大分值
//path[i][j]表示状态(i,j)时的字典序最小的串。
//当最大值为0的时候，输出的是空串
#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <string.h>
#include <math.h>
#include <vector>
#include <queue>
#include<iomanip>
#include <ctype.h>
#include <algorithm>
using namespace std;
#define inf 1<<30  
#define M 60005  
#define N 10005  
#define maxn 300005 
int tot;
struct Node{
    int next[26];
    int fail;
    int count;
	int kind;//节点所占有的索引号
    void init()
    {
        memset(next,0,sizeof(next));
        fail=0;
        count=0;
		kind = tot;
    }
}node[M];
int dp[55][N];
char str[105][105];  
string path[55][N]; 
int n,m,h[105],idx;
int insert(char *str,int k)
{
     int p = 0;
     int i=0,index;
     while (str[i])
     {
           index=str[i]-'a';
		   if (node[p].next[index]==0)
		   {
			   ++tot;
			   node[tot].init();
			   node[p].next[index]=tot;
		   }
           p=node[p].next[index];
           i++;
     }
     node[p].count=h[k];//价值
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
                if(node[node[son].fail].count)//
                    node[son].count+=node[node[son].fail].count;//为当前节点构成单词的后缀  累加count
                Q.push(son);
            }
            else//使用fail指向的后缀的next来拼接
                node[p].next[i]=node[node[p].fail].next[i];
        }
    }
}
  

void slove()  
{  
    int ans=0;  
    memset(dp,-1,sizeof(dp));  
    dp[0][0]=0;  
    for(int i=0;i<=n;i++) for(int j=0;j<=tot;j++) path[i][j].clear();  
    for(int i=0;i<n;i++)  
    {  
        for(int j=0;j<=tot;j++)  
        {  
            if(dp[i][j]==-1) continue;  
            for(int k=0;k<26;k++)  
            {  
				int son = node[j].next[k];//枚举j的后续
				if(!son)
					continue;
                int cur=node[son].kind;  
                if(dp[i][j]+node[cur].count>dp[i+1][cur])  
                {  
                    dp[i+1][cur]=dp[i][j]+node[cur].count;  
                    path[i+1][cur]=path[i][j]+(char)(k+'a');  
                }  
                else if(dp[i][j]+node[cur].count==dp[i+1][cur]&&path[i][j]+(char)(k+'a')<path[i+1][cur])  
                {  
                    path[i+1][cur]=path[i][j]+(char)(k+'a');  
                }  
            }  
        }  
    }  
    for(int i=1;i<=n;i++) for(int j=0;j<=tot;j++) ans=max(ans,dp[i][j]);  
    if(ans==0) 
	{
		puts("");
		return;
	}  
    string str=" ";  
    for(int i=1;i<=n;i++) 
		for(int j=0;j<=tot;j++) 
			if(dp[i][j]==ans&&(str==" "||(path[i][j].size()<str.size()||(path[i][j].size()==str.size()&&path[i][j]<str)))) 
				str=path[i][j];  
    cout<<str<<endl;  
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int t;  
    scanf("%d",&t);  
    while(t--)  
    {  
        tot=0; 
		node[0].init();
        scanf("%d%d",&n,&m);  
        for(int i=1; i<=m; i++)  
            scanf("%s",str[i]);  
        for(int i=1;i<=m;i++)  
        {  
            scanf("%d",&h[i]);  
            insert(str[i],i);  
        }  
        build_ac();
        slove();  
    }  
    return 0; 
}

