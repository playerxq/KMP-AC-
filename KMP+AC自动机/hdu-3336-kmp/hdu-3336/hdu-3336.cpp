// hdu-3336.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include<iomanip>
#include <ctype.h>
#include <algorithm>
using namespace std;
char str[200005];
int P[200005];
int cnt,n,m;
int get_P()
{
	int j = 0;
	P[1] = 0;
	int i = 2;
	for(;i<=n;i++)
	{
		while(j>0&&str[i]!=str[j+1])
			j = P[j];
		if(str[i]==str[j+1])
		{
			j++;
			P[i] = j;
		}
	}
	return 0;
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int t;  
    scanf("%d",&t);  
    while(t--)  
    {   
		memset(P,0,sizeof(P));
        scanf("%d",&n);  
        scanf("%s",str+1);
        get_P();  
        int i,s=0;  
        for(i=2;i<=n;i++)  
        {  
            if(P[i]>0)//����һ��ǰ׺�ظ�
                s++;  
            if(s>10007)  
                s=s%10007;  
        }  
        s=s+n;  //����n������n��ǰ׺  ����������ֵ��Ǵ�
        s=s%10007;  
        printf("%d\n",s);  
    } 
}

