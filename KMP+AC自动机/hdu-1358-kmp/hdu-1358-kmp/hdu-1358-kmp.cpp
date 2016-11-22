// hdu-1358-kmp.cpp : 定义控制台应用程序的入口点。
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
int P[1000005];
int n;
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
void kmp()  
{  
    int i,t;  
    for(i = 2;i<=n;i++)  
    {  
        t = i-P[i]; //
        if(i%t == 0 && i!=t) //t与i不同且  t|i  t|i-p[i]  因此t|p[i]
			printf("%d %d\n",i,i/t);  
    }  
}  
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int cnt = 1;
	while(scanf("%d",&n)!=EOF&&n)
	{
		scanf("%s",str+1);
		printf("Test case #%d\n",cnt++);  
		memset(P,0,sizeof(P));
		get_P();
		kmp();
		printf("\n");
	}
}

