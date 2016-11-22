// hdu-1686.cpp : 定义控制台应用程序的入口点。
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
char str[1000005]; 
char a[10005];
int P[1000005];
int cnt,n,m;
int get_P()
{
	int j = 0;
	P[1] = 0;
	int i = 2;
	for(;i<=m;i++)
	{
		while(j>0&&a[i]!=a[j+1])
			j = P[j];
		if(a[i]==a[j+1])
		{
			j++;
			P[i] = j;
		}
	}
	return 0;
}
int kmp()
{
	int j = 0;
	int i = 1;
	for(;i<=n;i++)
	{
		while(j>0&&str[i]!=a[j+1])
			j = P[j];
		if(str[i]==a[j+1])
			j++;
		if(j==m)
		{
			cnt++;
			j = P[j];
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
		cnt = 0;
		scanf("%s",a+1);
		scanf("%s",str+1);
		n = strlen(str+1);
		m = strlen(a+1);
		get_P();
		kmp();
		printf("%d\n",cnt);
	}
}

