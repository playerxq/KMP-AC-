// hdu-3247-AC�Զ���.cpp : �������̨Ӧ�ó������ڵ㡣
//�ϲ��ļ�ʹ�ó�������Ҳ��������ؼ���
//��trie�������ϣ����ݹؼ��ֵ�id�Ź����ɴ�״̬���ܿ������ڵ�
//�ɴ�״̬��¼���ļ��ؼ��ֽڵ�ת�Ƴ���  ����dp״̬ѹ������
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
			else//ʹ��failָ��ĺ�׺��next��ƴ��
                node[p].next[i]=node[node[p].fail].next[i];
		}
	}
}
int g[11][11];
int dp[1025][11];//dp[i][j]Ϊ�ļ�״̬i ���ǵ�j�ؼ���ʱ������ܳ�
int cnt;
int pos[11];
int dis[60010];
void bfs(int k)//kΪ�ļ��ڵ�
{
    queue<int>q;
    memset(dis,-1,sizeof(dis));
    dis[pos[k]] = 0;
    q.push(pos[k]);//�ڵ������
    while(!q.empty())
    {
        int now = q.front();
        q.pop();
        for(int i = 0; i< 2;i++)//���ļ��ڵ�ĺ���
        {
			int tmp = node[now].next[i];
			if(dis[tmp]<0 && node[tmp].index >= 0)//���ǲ����ڵ�
            {
                dis[tmp] = dis[now] + 1;//�ɴ��
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
		if(node[i].index> 0)//�Ǹ��ļ�
           pos[cnt++] = i;//ÿ���ļ��ֵ��յ�ڵ�
    for(int i = 0; i < cnt;i++)
        bfs(i);//���ļ��ڵ����� �����ļ��ڵ�֮��Ŀɴ����

    for(int i = 0;i < (1<<n);i++)//�ļ�����״̬  ȫ1ʱΪȫ������
        for(int j = 0;j < cnt;j++)//ÿ���ļ��ڵ�
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







