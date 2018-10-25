#include"stdafx.h"
#include <iostream>
#include<cstdio>
#include<algorithm>
#include<string.h>
#define MAXN 1000
using namespace std;
char fir_str[MAXN], sec_str[MAXN];
int len_fir, len_sec;
int count_fir[128], count_sec[128];

//method1
bool str_search(char* Target,char* Source)
{
	int len = strlen(Source);
	char *S = new char[len*2];
	strncpy_s(S,sizeof(S),Source,len);
	strncpy_s(S + len,sizeof(S), Source, len);
	return strstr(S,Target) != NULL;
}

//method2
bool str_circulation(char* Target, char* Source)
{
	int len = strlen(Target);
	char *S = new char[len];
	strncpy_s(S,sizeof(S),Target,len);
	for (int i = 0,signs; i < len; ++i)
	{
		char temp = S[0];
		signs = 1;
		for (int j = 0; j < len-1; ++j)
			S[i] = S[i + 1];
		S[len - 1] = temp;
		for (int j = 0; j < len; ++j)
		{
			if (S[j] != Source[j])
			{
				signs = 0;
				break;
			}
		}
		if (signs)
			return 1;
	}
	return 0;
}

int main()
{
	cin.getline(fir_str, MAXN);
	cin.getline(sec_str, MAXN);
	len_fir = strlen(fir_str);
	len_sec = strlen(sec_str);
	memset(count_fir, 0, sizeof(count_fir));
	memset(count_sec, 0, sizeof(count_sec));
	
	//check their length equivalence
	if (len_fir != len_sec)
	{
		printf("No.\n");
		return 0;
	}

	//check their characters' equivalence
	for (int i = 0; i < len_fir; ++i)
	{
		count_fir[fir_str[i]]++;
		count_sec[sec_str[i]]++;
	}
	for (int i = 0; i < 128; ++i)
	{
		if (count_fir[i] != count_sec[i])
		{
			printf("No.\n");
			return 0;
		}
	}

	//method1:to join fir_str with fir_str, then search sec_str in the new joint str
	if (str_search(fir_str, sec_str))
		printf("Yes.\n");
	else
		printf("No.\n");

	//method2:string circulation
	if (str_circulation(fir_str, sec_str))
		printf("Yes.\n");
	else
		printf("No.\n");
	return 0;
}
