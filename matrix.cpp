#include <iostream>
#include <math.h>
using namespace std;

class Matrix
{
	int n;
	int m;
	float* data;
public:
	Matrix();
	Matrix(int n, int m);
	Matrix (const Matrix& A);
	Matrix& operator =(const Matrix &A)
	{
		delete this->data;
		this->n = A.n;
		this->m = A.m;
		this->data = new float[A.n*A.m];
		for (int i(0); i < A.n*A.m; i++)
		{
			this->data[i] = A.data[i];
		}
		return (*this);
	}
	int getN()
	{
		return this->n;
	}
	int getM()
	{
		return this->m;
	}
	Matrix operator* (float c)
	{
		if (failed() == 1)
		{
			return *this;
		}
		Matrix res;
		res.n = this->n;
		res.m = this->m;
		res.data = new float [res.n*res.m];
		for (int i(0); i < res.n*res.m; i++)
		{
			res.data[i] = this->data[i] * c;
		}
		return Matrix(res);
	}
	Matrix operator* (Matrix& A)
	{
		if (n != A.m || failed() == 1 || A.failed() == 1)
		{
			return *this;
		}
		Matrix res(A.m, n);
		double sum = 0;
		for (int i(0); i < A.m; i++)
			for (int j(0); j < n; j++)
			{
				sum = 0;
				for (int k(0); k < m; k++)
				{
					sum += get(k, j)*A.get(i,k);
				}
				res.set(i,j, sum);
			}
			return Matrix(res);

	}
	float get(int i, int j);
	void set (int i, int j, float data);
	ostream& print (ostream& o)
	{
		for (int i(0); i < n; i++)
		{	
			for (int j(0); j < m; j++)
			{
				o<<this->get(i,j)<<'\t';
			}
			o<<'\n';
		}
		return o;
	}
	istream& read (istream& o)
	{
		int _n, _m;
		o>>_n>>_m;
		this->n = _n;
		this->m = _m;
		data = new float[n*m];
		for (int i(0); i < n; i++)
			for (int j(0); j < m; j++)
			{
				o>>this->data[i*n + j];
			}
		return o;
	}
	Matrix GetMinor(int _i, int _j)
	{
		if ( n != m)
		{
			return *(this);
		}
		Matrix temp(n-1,m-1);
		int k=0;
		int p = 0;
		for (int i(0); i < n; i++)
		{
			if (i == _i)
				continue;
			p = 0;
			for (int j(0); j < m; j++)
			{
				if ( j == _j)
					continue;
				temp.set(k,p,get(i,j));
				p++;
			}
			k++;
		}
		return Matrix(temp);
	}
	double determinant()
	{
		if(n != m || failed()== 1)
			return 0;
		if(n==1)
			return data[0];
		double det =0;
		for( int i(0); i < n; i++)
			det = det + powf(-1,i)*data[i]*GetMinor(0,i).determinant();
		return det;
	}
	Matrix reverse()
	{
		if (failed() == 1)
			return *this;
		double det = determinant();
		if (det == 0)
			return *this;
		Matrix _inverse(n, m);
		for (int i(0); i < n; i++)
			for (int j(0); j < m; j++)
			{
				_inverse.set(i, j, powf(-1, i + j) * GetMinor(j, i).determinant());
			}

			_inverse = _inverse*pow(det,-1);
			return Matrix(_inverse);
	}
	Matrix transpose()
	{
		Matrix res;
		if (this->failed() == 0)
		{
			res.n = this->m;
			res.m = this->n;
			res.data = new float [res.n*res.m];
			for (int i(0); i < this->n; i++)
			{
				for ( int j(0); j < this->m; j++)
				{
					res.set(j,i,get(i,j));
				}
			}
		}
		return Matrix(res);
	}
	Matrix operator + (Matrix& A)
	{
		Matrix res;
		if (this->failed()!=1 && A.failed()!=1 && this->n == A.n && this->m == A.m)
		{
			
			res.n = n;
			res.m = m;
			res.data = new float [res.n*res.m];
			for (int i(0); i < res.n; i++)
			{
				for(int j(0); j < res.m; j++)
					res.set(i,j,this->get(i,j) + A.get(i,j));
			}
			
		}
		return Matrix (res);
	}
	Matrix operator - (Matrix& A)
	{
		Matrix res;
		if (this->failed()!=1 && A.failed()!=1 && this->n == A.n && this->m == A.m)
		{
			
			res.n = n;
			res.m = m;
			res.data = new float [res.n*res.m];
			for (int i(0); i < res.n; i++)
			{
				for(int j(0); j < res.m; j++)
					res.set(i,j,this->get(i,j) - A.get(i,j));
			}
			
		}
		return Matrix (res);
	}
	bool failed()
	{
		return (n<=0 || m<=0 || n!=m || data == NULL);
	}
};
void Matrix::set(int i, int j, float data)
{
	this->data[i*m + j] = data;
}
float Matrix::get(int i, int j)
{
	return data[i*m + j];
}
Matrix::Matrix()
{
	n = 0; 
	m = 0;
	data = NULL;
}
Matrix::Matrix(int n, int m)
{
	this->n = n;
	this->m = m;
	this->data = new float [n*m];
}
Matrix::Matrix(const Matrix &A)
{
	this->n = A.n;
	this->m = A.m;
	this->data = new float[n*m];
	for ( int i(0); i < n*m; i++)
	{
		this->data[i] = A.data[i];
	}

}
Matrix* get_init(int n, int m)
{
    Matrix* N = new Matrix(m,n);
    return N;
}
