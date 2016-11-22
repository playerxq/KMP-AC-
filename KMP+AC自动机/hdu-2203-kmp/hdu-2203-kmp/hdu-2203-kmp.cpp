// hdu-2203-kmp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
/*该题要求一个串循环后是否包含另外一个串，其实只要将母串重复一次再进行KMP匹配就行了，
因为在重复母串的过程中，其实据已经将循环后的所有可能都列举出来了，
比如串 "ABCD" 重复后为  "ABCDABCD" 在这个串中 "BCDA" , "CDAB" 以及 "DABC" 都相继出现了。
用该种方法求解的过程中还应注意当子串长度超过母串时不进行匹配
*/

#include<stdio.h>
#include<string.h>
char a[200005],b[100005];
int P[100005];
int d1,d2;
int get_P()
{
	int j = 0;
	P[1] = 0;
	int i = 2;
	for(;i<=d2;i++)
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
int KMP()
{
	int i,j;	
	i=1;j=1;	
	while(i<=d1&&j<=d2)	
	{		
		if(j==0||a[i]==b[j]) {i++;j++;}		
		else j=P[j];		
	}	
	if(j>=d2) return 1;	
	else return -1;	
}
int main()
{	
	
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int i,j,ans,d;	
	while(scanf("%s",a+1)!=EOF)
	{		
		scanf("%s",b+1);	
        d1=strlen(a+1); 			
		d2=strlen(b+1); 		
		if(d2>d1) {printf("no\n");continue;}		
		j=d1+1;	
        for(i=1;i<=d1;i++)			
			a[j++]=a[i];//把本串接到本串		
		a[j]='\0';		
		//puts(a+1);		
		d1=strlen(a+1);	
		memset(P,0,sizeof(P));
		get_P();		
		ans=KMP();		
		if(ans>0) printf("yes\n");		
		else printf("no\n");		
	}		
}



