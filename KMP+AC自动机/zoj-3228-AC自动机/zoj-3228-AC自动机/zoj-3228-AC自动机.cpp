// zoj-3228-AC�Զ���.cpp : �������̨Ӧ�ó������ڵ㡣
//���ص��Ͳ����ص�2������
//��һ�������¼��һ�γ��ֵ�λ�ã�Ȼ��Ϳ�����������ص���
//����ͬһ���ؼ��ֵ����ͣ��ɷ��ص������ܲ�ͬ������index��ǹؼ��ֻᵼ���ظ�
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
int cnt[600010][2];
int last[600010];


struct Node
{
	int fail;
	int next[26];
	int deep;
	void init()
    {
        memset(next,0,sizeof(next));
        fail=0;
		deep = 0;
    }
} node[600010];
int tot;
int insert(char *str)//����id
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
		   node[p].deep = i+1;
           i++;
     }
     return p;
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
		for(i = 0;i<26;i++)
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
			else//ʹ��failָ��ĺ�׺��next��ƴ��
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
	memset(cnt,0,sizeof(cnt));
    memset(last,-1,sizeof(last));

	while(str[i])
	{
		t = str[i]-'a';
		while(now&&node[now].next[t]==0) now = node[now].fail;
		now = node[now].next[t];
		if(now==0)
			now = 0;
		temp = now;
		while(temp)
		{
			cnt[temp][0]++;//���ص�����+1
			if(i-last[temp]>=node[temp].deep)
			{
				last[temp]=i;
				cnt[temp][1]++;
			}
			temp = node[temp].fail;
		}
		i++;
	}
}
char str[100010];
char buf[20];
int typ[100010],pos[100010];

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int n;
    int iCase = 0;
    while(scanf("%s",str)==1)
    {
        iCase++;
        printf("Case %d\n",iCase);
        scanf("%d",&n);
        tot = 0;
		node[0].init();
        for(int i = 0;i < n;i++)
        {
            scanf("%d%s",&typ[i],buf);
            pos[i]=insert(buf);//��¼ÿ���ؼ��ֵĽڵ�
        }
        build_ac();
        query(str);
        for(int i = 0;i < n;i++)
            printf("%d\n",cnt[pos[i]][typ[i]]);
        printf("\n");
    }
    return 0;
}





