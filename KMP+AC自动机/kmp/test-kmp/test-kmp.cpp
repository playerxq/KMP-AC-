// test-kmp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
int a[11];
int b[5];
int p[11];
int kmp()
{
	int j = 0;
	int i = 1;
	for(;i<=10;i++)
	{
		while(j>0&&a[i]!=b[j+1])
			j = p[j];
		if(a[i]==b[j+1])
			j++;
		if(j==4)
		{
			printf("find a match, start from %d\n",i-j+1);
			j = p[j];
		}
	}
	return 0;
}
int init()
{
	int j = 0;
	p[1] = 0;
	int i = 2;
	for(;i<=4;i++)
	{
		while(j>0&&b[i]!=b[j+1])
			j = p[j];
		if(b[i]==b[j+1])
		{
			j++;
			p[i] = j;
		}
	}
	return 0;
}
int _tmain(int argc, _TCHAR* argv[])
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	for(int i = 1;i<=10;i++)
		scanf("%d",&a[i]);
	for(int i = 1;i<=4;i++)
		scanf("%d",&b[i]);
	memset(p,0,sizeof(p));
	init();
	kmp();
	return 0;
}

