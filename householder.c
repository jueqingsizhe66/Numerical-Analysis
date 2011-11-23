#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int n,m;
double A[1000][1000];
double b[1000];
void house()
{
	int i,j,k;
	for(i=1;i<=m;i++)
	{
		/*calculate Alpha */
		double alpha=0;
		for(j=i;j<=n;j++)
			alpha+=A[j][i]*A[j][i];
		alpha=sqrt(alpha);
		/*calculate Alpha */
		
		/*calculate vector v*/
		double v[1000]; memset(v,0,sizeof(v));
		for(j=i;j<=n;j++)
			v[j]=A[j][i];
		v[i]-=alpha;
		/*calculate vector v*/
		
		/*calculate const beta*/
		double beta=0;
		for(j=i;j<=n;j++)
			beta+=v[j]*v[j];
		beta=beta;
		beta=2.0/beta;
		/*calculate const beta*/
		
		/*calculate H*A  */
		double w[1000]; memset(w,0,sizeof(w));
		for(j=1;j<=m;j++)
		{
			for(k=1;k<=n;k++)
				w[j]+=v[k]*A[k][j];
			w[j]*=beta;
		}
		
		for(j=i;j<=n;j++)
			for(k=i;k<=m;k++)
				A[j][k]-=v[j]*w[k];
		for(j=1;j<=n;j++)
			b[j]=b[j]-beta*v[j]b[j];
	}
}
int main()
{
	freopen("A.txt","r",stdin);
	n=301,m=31;
	int i,j;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			scanf("%lf",&A[i][j]);
	freopen("b.txt","r",stdin);
	for(i=1;i<=n;i++)
		scanf("%lf",&b[i]);
	house();
	//
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
			printf("%lf ",A[i][j]);
		putchar('\n');
	}
	
}
