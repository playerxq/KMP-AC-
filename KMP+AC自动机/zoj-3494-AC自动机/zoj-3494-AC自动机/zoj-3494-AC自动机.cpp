// zoj-3494-AC�Զ���.cpp : �������̨Ӧ�ó������ڵ㡣
//A B���ж��ٴ���BCD�벻��Ԥ�����ģʽ��
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
	int next[2];
	int index;
	void init()
    {
        memset(next,0,sizeof(next));
        fail=0;
        index=-1;
    }
} node[2010];
int tot;
int insert(char buf[])
{
     int p = 0;
     int i=0;
	 int len = strlen(buf);
     for(;i<len;i++)
     {
		   if (node[p].next[buf[i]-'0']==0)
		   {
			   ++tot;
			   node[tot].init();
			   node[p].next[buf[i]-'0']=tot;
		   }
           p=node[p].next[buf[i]-'0'];
     }
     node[p].index=1;//��ֵ
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
					if(node[node[son].fail].index==1)
						node[son].index=1;
				}
				Q.push(son);
			}
			else//ʹ��failָ��ĺ�׺��next��ƴ��
                node[p].next[i]=node[node[p].fail].next[i];
		}
	}
}
int bcd[2010][10];//bcd[i][j]��ʾ��i�ڵ㿪ʼ����j��BCD���ֺ󵽴�Ľڵ�
int change(int pre,int num)//֮ǰ״̬preҲ���ڵ�  ������num
{
    if(node[pre].index==1)//�ǹؼ��ֽ�β �����ټ�������
		return -1;
    int cur = pre;
    for(int i = 3;i >= 0;i--)//����numÿһλ
    {
		if(node[node[cur].next[(num>>i)&1]].index==1)//ö�ٶ�Ӧ��cur��ÿ������ ���Ƿ�����ؼ���
			return -1;
        cur = node[cur].next[(num>>i)&1];//��һλ���Լ���cur֮��
    }
    return cur;//pre����num���ڵĽڵ�λ��
}
const int MOD = 1000000009;
long long dp[210][2010];//dp[i][j]��ʾ����Ϊi��λ�ڽ��j�ĸ��� 
int bit[210];//���޴�

//�Ӹ��ڵ㿪ʼ����ac���� ����Ԥ���崮 �൱�ڴ���һ������Ҷ�ӵ�·��
//bcd�����ʶ�˴ӽڵ�����߿��Ա����ߵ�Ҷ��  s�����˵�ǰ���ڵĽڵ�  s�ı仯����Ҫȷ�������ı仯
//bcd����ڶ�άΪ10 �൱����ac������0-9��BCD������ ��ת����Ӧ�ڵ�
//dp������ǳ���Ϊi,�ڽڵ�j�����ڵĲ�����Ŀ�괮���Ҳ�����Ԥ���崮�����ָ���

//Ŀ�괮����pos����֪��  ��λ�Ӹߵ���λ��ֵ ���Ŀ϶������λΪ9 ���λ��0�൱�ڼ�ǰ��0 ������pos������С��Ŀ�괮�����ִ��������
//��λDP������Ϊpos,��ǰ״̬Ϊs,flag���λ�Ƿ������ƣ�z�Ƿ���ǰ��0  

//��ǰ���ǵ�posλ �Ӹ�λ����λ���� Ŀ��λΪbit[pos]
long long dfs(int pos,int s,bool flag,bool z)
{
    if(pos == -1)
		return 1;
    if(!flag && dp[pos][s]!=-1)return dp[pos][s];//û������  ��ǰ����ǰ��0 ��Ҫ���ſ�  dp��Ȼ��ȷ ǰ����ǰ��0 ����flag=0 ��Ȼ��ȷ
    //������ʱ  ���λ��һ����֮ǰ�����dp[pos][s]�е����ô���һ�� ��Ҫ���¼���
	long long ans = 0;
	//���ȿ��ǵ�ǰ���λ��0
	//��ǰ��0 ��ǰ��0�൱�ڼ�������ǰ��0
    if(z)
    {//����ǰ��0 ����ʵ����û��  ��˽ڵ�s����
        ans += dfs(pos-1,s,flag && bit[pos]==0,true);//��Ŀ���Ӧλ=0 ������flag���ݸ��ݹ� ����ǰλ���õ�0С��Ŀ���Ӧλ ����������
        ans %= MOD;
    }
    else//������ǰ��0
    {//���ȿ������λ��0 �ڵ�s��0���� ��ʱ0��Ϊʮ������ BCD��0000���߷��Ѿ���change�����
        if(bcd[s][0]!=-1)//������
			ans += dfs(pos-1,bcd[s][0],flag && bit[pos]==0,false);//bit[pos]=0˵����ӵ�����Ŀ��һ�� ���֮ǰҲ������ ��ô���ƽ����ݵ��ݹ��� ����֮ǰ������ �ݹ�Ҳ��Ӧ�������� ��bit[pos]��Ϊ0 ��Ȼ��ӵ���С��Ŀ�� ��ݹ��λҲ����������
        ans %= MOD;//�ۼƵ�ǰλ��0�Ŀ�ȡ�����ִ�����
    }
    int end = flag?bit[pos]:9;
    for(int i = 1;i<=end;i++)
    {
        if(bcd[s][i]!=-1)//��֤�����ߵ�Ҷ��
        {
            ans += dfs(pos-1,bcd[s][i],flag&&i==end,false);//��i=end���������� ֮ǰ�����ƻᴫ�ݸ��ݹ��еĵ�λ ����iû�е������� �ݹ���Ȼ����������
            ans %=MOD;
        }
    }
    if(!flag && !z)//����Ϊpos ��ʼ�ڵ�Ϊs���λ��չ��ans��������Ŀ��Ĵ� ��Щ����������֮��ļ���  ��Ҫ��֤��������pos���ϵĸ�λ ��flag��zΪ0
		dp[pos][s] = ans;//��flag=0��ǰ����0 ˵����ʱ��s����չ0-9������ǰ���0 Ҳ����˵��ǰ�治Ϊǰ��0ʱ��һ�����Դ�0-9 �ʲ�����Ϊdp��ֵ
	//ֻ�е�ǰ��û��ǰ��0������ ��flag=0ʱ ����posλs�ڵ㴦��������չ
    return ans;
}


long long calc(char s[])
{
    int len = strlen(s);
    for(int i = 0;i < len;i++)
        bit[i] = s[len-1-i]-'0';//�ߵ�λ��ת  ���޴�ΪA-1����B
    return dfs(len-1,0,1,1);
}
char str[210];

void pre_init()
{
    for(int i = 0;i <=tot;i++)
        for(int j = 0;j <10;j++)
            bcd[i][j] = change(i,j);
}


int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int T;
    scanf("%d",&T);
    int n;
    while(T--)
    {
		node[0].init();
		tot = 0;
        scanf("%d",&n);
        for(int i = 0;i < n;i++)//Ԥ�����ģʽ��
        {
            scanf("%s",str);
            insert(str);
        }
        build_ac();
        pre_init();
        memset(dp,-1,sizeof(dp));
        int ans = 0;
        scanf("%s",str);//A
        int len = strlen(str);
        for(int i = len -1;i >=0;i--)//�߾��ȼ���  ��len-1λ��ʼ��1 ��0Ϊ9 ֱ����һ����Ϊ0�ļ�һ ���ܻ������λ����һ��ǰ��0
        {
            if(str[i]>'0')
            {
                str[i]--;
                break;
            }
            else str[i] = '9';
        }
        ans -= calc(str);//ȥ��A���ڼ�A-1�������ؼ��ֵĴ�
        ans %=MOD;
        scanf("%s",str);
        ans += calc(str);//�ټ���B���ڲ������ؼ��ֵĴ�  �õ�A,B֮�䲻�����ؼ��ֵĴ�
        ans %=MOD;
        if(ans < 0)ans += MOD;
        printf("%d\n",ans);
    }
    return 0;

}



