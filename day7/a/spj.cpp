#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
int n,m,sm1,sm2;
char s[509];
int v[509][509];
int mat[509][509];
int main()
{
	freopen("result.out","w",stdout);
	for(int t=1;t<=75;t++)
	{
		char cmd[100];
		sprintf(cmd,"cp bitbit%d.in a.in; time ./a; cp bitbit%d.out ans.out",t,t);
		system(cmd);
		FILE *in=fopen("a.in","r"),*out=fopen("a.out","r"),*ans=fopen("ans.out","r");
		fscanf(in,"%d%d",&n,&m);
		// printf("n:%d m:%d\n",n,m);
		for(int i=1;i<=n;i++)
		{
			fscanf(in,"%s",s+1);
			for(int j=1;j<=m;j++)
				v[i][j]=s[j]-'0';
		}
		fscanf(out,"%d",&sm1);
		fscanf(ans,"%d",&sm2);
		// printf("sm1:%d sm2:%d\n",sm1,sm2),fflush(stdout);
		if(sm1!=sm2)
		{
			printf("WA %d sum out: %d != sum ans: %d\n",t,sm1,sm2);
			fclose(in),fclose(out),fclose(ans);
			continue;
		}
		char ps[10];
		memset(mat,0,sizeof(mat));
		for(int i=1;i<=sm1;i++)
		{
			fscanf(out,"%s",ps);
			int sgn=ps[0]=='+'?1:-1;
			for(int j=1;j<=n;j++)
			{
				fscanf(out,"%s",s+1);
				for(int k=1;k<=m;k++)
					mat[j][k]+=sgn*(s[k]-'0');
			}
		}
		fclose(in),fclose(out),fclose(ans);
		int fg=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
				if(v[i][j]!=mat[i][j])
				{
					printf("WA %d line %d column %d\n",t,i,j);
					fg=1;
					break;
				}
			if(fg)
				break;
		}
		if(fg)
			continue;
		printf("AC %d\n",t);
	}
	return 0;
}