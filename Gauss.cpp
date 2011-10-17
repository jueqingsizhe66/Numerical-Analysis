/*
 * Author: xn_rookie
 * Created Time:  2011/10/11 19:14:50
 * File Name: Gauss.c
 * Description : 列主元高斯消元法
 */
#include <stdio.h>

#define Limit 200

int N;
double A[Limit][Limit];
int main() {
	printf("Please Input N\n");
	scanf("%d",&N);
	printf("Please Input Matrix A\n");
	int i,j;
	for(i = 1 ; i<=N; i++)
		for(j=1; j<=N;j++)
			scanf("%lf",&A[i][j]);
	int k;
	for(k=1;k<N;k++)
	{
		double max=-1;
		int maxp=-1;
		for(i=k;i<=N;i++)
			if(max<abs(A[i][k]))
			{
				max=abs(A[i][k]);
				maxp=i;
			}
		for(i=1;i<=N;i++)
		{
			double t;
			t=A[k][i];
			A[k][i]=A[maxp][i];
			A[maxp][i]=t;
		}
		for(i=k+1;i<=N;i++)
			A[i][k]/=A[k][k];
		for(i=k+1;i<=N;i++)
			for(j=k+1;j<=N;j++)
				A[i][j]-=A[i][k]*A[k][j];
	}
	printf(" Matrix A= \n");
	for(i= 1 ; i <= N;i++)
	{ 
		printf("%lf",A[i][1]);
		for(j=2;j<=N;j++)
			printf(" %lf",A[i][j]);
		putchar('\n');
	}
    return 0;
}

