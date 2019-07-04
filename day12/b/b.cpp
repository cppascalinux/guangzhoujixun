#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<cstdlib>
#include"game.h"
using namespace std;
string game(int n,int k)
{
	string t;
	for(int i=1;i<=n;i++)
		t+='0';
	int lst=guess(t);
	for(int i=0;i<n;i++)
	{
		t[i]='1';
		int cur=guess(t);
		if(cur>lst)
			lst=cur;
		else
			t[i]='0';
	}
	return t;
}