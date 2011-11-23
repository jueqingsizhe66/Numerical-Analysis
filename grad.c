#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
double **A;
double *b;
int n;
double *copy(double *x,int n)
{
	double *ret=(double *)malloc(sizeof(double)*n+1);
	int i;
	for(i=1;i<=n;i++)
		ret[i]=x[i];
	return ret;
}
int check_zeros(double *x,int n)
{
	int i;
	for(i=1;i<=n;i++)
		if(!(abs(x[i])<10e-8))
			return 0;
	return 1;
}
double inner_product(double *x,double *y,int n)
{
	int i;
	double ret=0;
	for(i=1;i<=n;i++)
		ret+=x[i]*y[i];
	return ret;
}
double quad(double *x,double **a,double *y,int n)
{
	double *tmp=(double *)malloc(sizeof(double *)*n);
	int i,j;
	for(i=1;i<=n;i++)
	{
		tmp[i]=0;
		for(j=1;j<=n;j++)
			tmp[i]+=x[j]*a[j][i];
	}
	double ret=0;
	for(i=1;i<=n;i++)
		ret+=tmp[i]*y[i];
	return ret;
}
double *grad(double **a,double *b,int n)
{
	double *x1,*x0,*x2;
	x1=(double *)malloc(sizeof(double *)*n+1);
	x0=(double *)malloc(sizeof(double *)*n+1);
	int i;
	for(i=1;i<=n;i++)
		x0[i]=0;
	double *r2,*r1,*r0;
	double *p1,*p0;
	double beta2,beta1,beta0;
	double alpha1,alpha0;
	int step=0;
	//k=1时
	r0=copy(b,n);
	p0=copy(r0,n);
	alpha0=inner_product(r0,r0,n)/quad(p0,a,p0,n);
	for(i=1;i<=n;i++)
		x1[i]=x0[i]+alpha0*p0[i];
	r1=copy(r0,n);
	for(i=1;i<=n;i++)
	{
		int j;
		double tmp=0;
		for(j=1;j<=n;j++)
			tmp+=a[i][j]*p0[j];
		tmp*=alpha0;
		r1[i]-=tmp;
	}
	if(check_zeros(r1,n)) return x1;
	beta0=inner_product(r1,r1,n)/inner_product(r0,r0,n);
	p1=(double *)malloc(sizeof(double)*n+1);
	for(i=1;i<=n;i++)
		p1[i]=r1[i]+beta0*p0[i];
	alpha1=inner_product(r1,r1,n)/quad(p1,a,p1,n);
	for(i=1;i<=n;i++)
		x2[i]=x1[i]+alpha1*p1[i];
	for(i=1;i<=n;i++)
	{
		r2[i]=r1[i];
		int j;
		double tmp=0;
		for(j=1;j<=n;j++)
			tmp+=a[i][j]*p1[j];
		r2[i]-=alpha1*tmp;
	}
	while(!check_zeros(r2,n))
	{
		r0=copy(r1,n),r1=copy(r2,n);
		x0=copy(x1,n),x1=copy(x2,n);
		p0=copy(p1,n);
		beta0=inner_product(r1,r1,n)/inner_product(r0,r0,n);
		for(i=1;i<=n;i++)
			p1[i]=r1[i]+beta0*p0[i];
		alpha1=inner_product(r1,r1,n)/quad(p1,a,p1,n);
		for(i=1;i<=n;i++)
			x2[i]=x1[i]+alpha1*p1[i];
		for(i=1;i<=n;i++)
		{
			r2[i]=r1[i];
			double tmp=0;
			int j;
			for(j=1;j<=n;j++)
				tmp+=a[i][j]*p1[j];
			r2[i]-=alpha1*tmp;
		}
	}
	return x2;
}
int main()
{
	scanf("%d",&n);
	A=(double **)malloc(sizeof(double *)*n+1);
	int i,j;
	for(i=1;i<=n;i++)
	{
		*(A+i)=(double *)malloc(sizeof(double) *n+1);
		for(j=1;j<=n;j++)
			scanf("%lf",&A[i][j]);
	}
	b=(double *)malloc(sizeof(double *)*n+1);
	for(i=1;i<=n;i++)
		scanf("%lf",&b[i]);
	double *ans=grad(A,b,n);
	for(i=1;i<=n;i++)
		printf("%lf ",ans[i]);
	free(A);
	free(b);
}
