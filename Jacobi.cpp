/*
 * Author: xn_rookie
 * Created Time:  2011/11/8 22:46:05
 * File Name: Jacobi.cpp
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

const double eps=0.000001;
vector <double> b;
vector < vector <double> > a;
//input
class Norm
{
	public:
	double vector_norm_inf(vector <double> v)
	{
		double max=0;
		int N=v.size();
		for(int i=0;i<N;i++)
			max=max<abs(v[i])?abs(v[i]):max;
		return max;
	}
	double vector_norm_one(vector <double> v)
	{
		double ret=0;
		for(int i=0;i<v.size();i++)
			ret+=abs(v[i]);
		return ret;
	}
	double vector_norm_two(vector <double> v)
	{
		double ret=0;
		for(int i=0;i<v.size();i++)
			ret+=v[i]*v[i];
		return sqrt(ret);
	}
	double matrix_norm_inf(const vector <vector <double> > a)
	{
		int N=a.size();
		double max=0;
		for(int i=0;i<N;i++)
		{
			double sum=0;
			for(int j=0;j<N;j++)
				sum+=abs(a[i][j]);
			max=max<sum?sum:max;
		}
		return max;
	}
	double matrix_norm_one(const vector <vector <double> > a)
	{
		int N=a.size();
		double max=0;
		for(int j=0;j<N;j++)
		{
			double sum=0;
			for(int i=0;i<N;i++)
				sum+=abs(a[i][j]);
			max=max<sum?sum:max;
		}
		return max;
	}
}norm;
class Iteration
{
	private:
		vector <double> sub(vector <double> a,vector <double> b)
		{
			vector <double> ans;
			ans.clear();
			for(int i=0;i<a.size();i++)
				ans.push_back(a[i]-b[i]);
			return ans;
		}
	public:
		vector <double> Jacobi(vector <vector <double> > a,vector <double >b)
		{
			vector <double> ans,x;
			ans.clear(),x.clear();
			int N=a.size();
			for(int i=0;i<N;i++)
			{
				ans.push_back(0);
				x.push_back(0);
			}
			do
			{
				ans=x;
				for(int i=0;i<N;i++)
				{
					x[i]=b[i];
					for(int j=0;j<N;j++)
					{
						if(i==j) continue;
						x[i]-=a[i][j]*x[j];
					}
					x[i]/=a[i][i];
				}
			}while(norm.vector_norm_two(sub(x,ans))>=eps);
			return ans;
		}
		vector <double> GS(vector <vector <double> > a,vector <double> b)
		{
			vector <double> ans,x;
			ans.clear(),x.clear();
			int N=a.size();
			for(int i=0;i<N;i++)
			{
				ans.push_back(0);
				x.push_back(0);
			}
			do
			{
				ans=x;
				for(int i=0;i<N;i++)
				{
					x[i]=b[i];
					for(int j=0;j<N;j++)
					{
						if(i==j) continue;
						if(j<i)
							x[i]-=a[i][j]*ans[j];
						else
							x[i]-=a[i][j]*x[j];
					}
					x[i]/=a[i][i];
				}
			}while(norm.vector_norm_two(sub(x,ans))>=eps);
			return ans;
		}
}solve;
void input()
{
	int N;
	cout<<"input the order of Maxtrix A"<<endl;
	cin>>N;
	a.clear();
	cout<<"input the Matrix A"<<endl;
	for(int i=0;i<N;i++)
	{
		vector <double> tmp;
		tmp.clear();
		for(int j=0;j<N;j++)
		{
			double x;
			cin>>x;
			tmp.push_back(x);
		}
		a.push_back(tmp);
	}
	b.clear();
	cout<<"input the Vector b"<<endl;
	for(int i=0;i<N;i++)
	{
		double x;
		cin>>x;
		b.push_back(x);
	}
}

int main() {
	input();
	vector <double> ans=solve.Jacobi(a,b);
	for(int i=0;i<ans.size();i++)
		cout<<ans[i]<<' ';
	cout<<endl;
    return 0;
}

