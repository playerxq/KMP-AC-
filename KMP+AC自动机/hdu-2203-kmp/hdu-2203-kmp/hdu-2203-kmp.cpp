// hdu-2203-kmp.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
/*����Ҫ��һ����ѭ�����Ƿ��������һ��������ʵֻҪ��ĸ���ظ�һ���ٽ���KMPƥ������ˣ�
��Ϊ���ظ�ĸ���Ĺ����У���ʵ���Ѿ���ѭ��������п��ܶ��оٳ����ˣ�
���紮 "ABCD" �ظ���Ϊ  "ABCDABCD" ��������� "BCDA" , "CDAB" �Լ� "DABC" ����̳����ˡ�
�ø��ַ������Ĺ����л�Ӧע�⵱�Ӵ����ȳ���ĸ��ʱ������ƥ��
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
			a[j++]=a[i];//�ѱ����ӵ�����		
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



