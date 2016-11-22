// hdu-2222.cpp : 定义控制台应用程序的入口点。
//AC自动机
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
//构建trie树
struct node
{
    node *next[26],*fail;//匹配失败了 回溯到哪里继续
    int count;
    node()
    {
          fail=NULL;
          count=0;
          memset(next,0,sizeof(next));
    }
};
int insert(char *str,node *root)
{
     node *p=root;
     int i=0,index;
     while (str[i])
     {
           index=str[i]-'a';
           if (!p->next[index]) p->next[index]=new node();
           p=p->next[index];
           i++;
     }
     p->count++;//结尾次数
     return 0;
}
char word[60],str[1000002];
queue<node*> q;
//构建fail指针  即当前trie树的路径上匹配结束后 跳转到哪条分支上继续匹配
//root:fail应为当前节点的后缀
//BFS
//当前节点沿路径回溯，直到找到一个祖先节点，其子节点与当前节点一样，则将当前节点的fail指向该子节点，若回溯到根也没有，则fail=root
//可利用父节点回溯，即从当前节点的父节点的fail指针处寻找祖先节点
int build(node *root)
{
    root->fail=NULL;
    q.push(root);
    while (!q.empty())
    {
        node *p=NULL;
        node *temp=q.front();
        q.pop();
        for (int i=0;i<26;i++)//考虑temp的每个孩子
		{
            if(temp->next[i])//第i个孩子 孩子作为当前考虑的节点  祖先节点的子节点也必须是第i个孩子
            {
                if(temp==root) //根  没法回溯
					temp->next[i]->fail=root;
                else
                {
                     p=temp->fail;//父节点的fail
                     while(p)
                     {
                         if (p->next[i]) //有第i个孩子
						 {
							 temp->next[i]->fail=p->next[i];//指向这个子节点
							 break;
						 }
                         p=p->fail;//继续回溯
                     }
                     if(!p) //未找到  指向根
						 temp->next[i]->fail=root;
                 }
                 q.push(temp->next[i]);
             }
		}
    }
    return 0;
}
//考虑主串在trie上的匹配情况
int solve(node *root)
{
     int i=0,cut=0,index,len=strlen(str);
     node *p=root;
     while(str[i])//对主串每个字符
     {
		 //此时p节点到root恰好对应一个关键字  str[i]为关键字的下一个字符
          index=str[i]-'a';
          while (!p->next[index] && p!=root) p=p->fail;//从上一个关键字结尾的fail指针匹配  直到找到str[i] 此时root:p为之前关键字的后缀
          p=p->next[index];//找到一个匹配  后缀扩展一个str[i]字符
          p=(p==NULL)?root:p;//p = root时说明trie上没有这个字符的匹配  i++看下一个字符 从根重新匹配
          node *temp=p;//从这个匹配开始
          while (temp!=root && temp->count!=-1)
          {
                cut+=temp->count;//count记录有几个单词关键字以当前字符结尾 即后缀扩展str[i]形成的单词是否是完整的关键字
                temp->count=-1;
                temp=temp->fail;//考虑后缀扩展str[i]构成的单词的后缀  看是否也是关键字
          }
          i++;
    }
    return cut;
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int tt;
    scanf("%d",&tt);
    while (tt--)
    {
          node *root=new node();
          int n;
          scanf("%d\n",&n);
          for (int i=1;i<=n;i++)
          {
              gets(word);
              insert(word,root);
          }
          build(root);
          scanf("%s",str);
          printf("%d\n",solve(root));
    }
    return 0;
}

