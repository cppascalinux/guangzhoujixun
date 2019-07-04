#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<random>
#include<cstdlib>
#include<ctime>
#include"game.h"
using namespace std;
int lst;
string s;
string game(int n,int k)
{
	mt19937 rnd(20020618);
	s.resize(n);
	for(int i=0;i<n;i++)
		s[i]=rnd()%2+'0';
	lst=guess(s);
	for(int i=0;i<n;i+=2)
	{
		s[i]^=1,s[i+1]^=1;
		int cur=guess(s);
		if(cur==lst+2)
			lst=cur;
		else if(cur==lst-2)
			s[i]^=1,s[i+1]^=1;
		else
		{
			s[i+1]^=1;
			int nc=guess(s);
			if(nc>lst)
				lst=nc;
			else
				s[i]^=1,s[i+1]^=1,lst=nc+2;
		}
	}
	if(n&1)
	{
		s[n-1]^=1;
		int cur=guess(s);
		if(cur<lst)
			s[n-1]^=1;
	}
	return s;
}