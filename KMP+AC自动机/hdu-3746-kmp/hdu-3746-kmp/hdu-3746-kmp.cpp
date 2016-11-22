// hdu-3746-kmp.cpp : 定义控制台应用程序的入口点。
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
const int M=100002;
char s[M];
int P[M];
int n,m;
int len;
int get_P()
{
	int j = 0;
	P[1] = 0;
	int i = 2;
	for(;i<=len;i++)
	{
		while(j>0&&s[i]!=s[j+1])
			j = P[j];
		if(s[i]==s[j+1])
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
		scanf("%s",s+1);
        len=strlen(s+1);
		memset(P,0,sizeof(P));
		get_P();
		int min_repeat_len=len-P[len];
		if(len!=min_repeat_len&&len%min_repeat_len==0 )
			printf("0\n");
		else
            printf( "%d\n", min_repeat_len-len%min_repeat_len );
	}
}

