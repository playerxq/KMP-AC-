// hdu-3336.cpp : 定义控制台应用程序的入口点。
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
            if(P[i]>0)//出现一次前缀重复
                s++;  
            if(s>10007)  
                s=s%10007;  
        }  
        s=s+n;  //长度n本身有n个前缀  加上自身出现的那次
        s=s%10007;  
        printf("%d\n",s);  
    } 
}

