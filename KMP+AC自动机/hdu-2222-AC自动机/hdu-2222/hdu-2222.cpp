// hdu-2222.cpp : �������̨Ӧ�ó������ڵ㡣
//AC�Զ���
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
//����trie��
struct node
{
    node *next[26],*fail;//ƥ��ʧ���� ���ݵ��������
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
     p->count++;//��β����
     return 0;
}
char word[60],str[1000002];
queue<node*> q;
//����failָ��  ����ǰtrie����·����ƥ������� ��ת��������֧�ϼ���ƥ��
//root:failӦΪ��ǰ�ڵ�ĺ�׺
//BFS
//��ǰ�ڵ���·�����ݣ�ֱ���ҵ�һ�����Ƚڵ㣬���ӽڵ��뵱ǰ�ڵ�һ�����򽫵�ǰ�ڵ��failָ����ӽڵ㣬�����ݵ���Ҳû�У���fail=root
//�����ø��ڵ���ݣ����ӵ�ǰ�ڵ�ĸ��ڵ��failָ�봦Ѱ�����Ƚڵ�
int build(node *root)
{
    root->fail=NULL;
    q.push(root);
    while (!q.empty())
    {
        node *p=NULL;
        node *temp=q.front();
        q.pop();
        for (int i=0;i<26;i++)//����temp��ÿ������
		{
            if(temp->next[i])//��i������ ������Ϊ��ǰ���ǵĽڵ�  ���Ƚڵ���ӽڵ�Ҳ�����ǵ�i������
            {
                if(temp==root) //��  û������
					temp->next[i]->fail=root;
                else
                {
                     p=temp->fail;//���ڵ��fail
                     while(p)
                     {
                         if (p->next[i]) //�е�i������
						 {
							 temp->next[i]->fail=p->next[i];//ָ������ӽڵ�
							 break;
						 }
                         p=p->fail;//��������
                     }
                     if(!p) //δ�ҵ�  ָ���
						 temp->next[i]->fail=root;
                 }
                 q.push(temp->next[i]);
             }
		}
    }
    return 0;
}
//����������trie�ϵ�ƥ�����
int solve(node *root)
{
     int i=0,cut=0,index,len=strlen(str);
     node *p=root;
     while(str[i])//������ÿ���ַ�
     {
		 //��ʱp�ڵ㵽rootǡ�ö�Ӧһ���ؼ���  str[i]Ϊ�ؼ��ֵ���һ���ַ�
          index=str[i]-'a';
          while (!p->next[index] && p!=root) p=p->fail;//����һ���ؼ��ֽ�β��failָ��ƥ��  ֱ���ҵ�str[i] ��ʱroot:pΪ֮ǰ�ؼ��ֵĺ�׺
          p=p->next[index];//�ҵ�һ��ƥ��  ��׺��չһ��str[i]�ַ�
          p=(p==NULL)?root:p;//p = rootʱ˵��trie��û������ַ���ƥ��  i++����һ���ַ� �Ӹ�����ƥ��
          node *temp=p;//�����ƥ�俪ʼ
          while (temp!=root && temp->count!=-1)
          {
                cut+=temp->count;//count��¼�м������ʹؼ����Ե�ǰ�ַ���β ����׺��չstr[i]�γɵĵ����Ƿ��������Ĺؼ���
                temp->count=-1;
                temp=temp->fail;//���Ǻ�׺��չstr[i]���ɵĵ��ʵĺ�׺  ���Ƿ�Ҳ�ǹؼ���
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

