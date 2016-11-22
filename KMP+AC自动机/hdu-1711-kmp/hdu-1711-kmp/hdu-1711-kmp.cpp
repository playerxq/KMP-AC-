// hdu-1711-kmp.cpp : 定义控制台应用程序的入口点。
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
int a[1000005];  
int b[10005];
int P[10005];
int n,m;
int get_P()
{
	int j = 0;
	P[1] = 0;
	int i = 2;
	for(;i<=m;i++)
	{
		while(j>0&&b[i]!=b[j+1])
			j = P[j];
		if(b[i]==b[j+1])
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
		while(j>0&&a[i]!=b[j+1])
			j = P[j];
		if(a[i]==b[j+1])
			j++;
		if(j==m)
		{
			printf("%d\n",i-j+1);
			return 0;
		}
	}
	printf("-1\n");
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
		scanf("%d %d",&n,&m);
		for(int i = 1;i<=n;i++)
		{
			scanf("%d",&a[i]);
		}
		for(int i = 1;i<=m;i++)
		{
			scanf("%d",&b[i]);
		}
		memset(P,0,sizeof(P));
		get_P();
		kmp();
	}
}

