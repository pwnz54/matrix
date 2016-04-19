#include <iostream>
#include < math.h>
using namespace std;

class matrix
{
	int n;
	int m;
	float* data;
public:
	matrix();
	matrix(int n, int m);
	matrix (const matrix& A);
	matrix operator =(matrix &A)
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
	matrix operator* (float c)
	{
		matrix res;
		res.n = this->n;
		res.m = this->m;
		res.data = new float [res.n*res.m];
		for (int i(0); i < res.n*res.m; i++)
		{
			res.data[i] = this->data[i] * c;
		}
		return matrix(res);
	}
	matrix operator* (matrix& A)
	{
		matrix res(A.m, n);
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
			return matrix(res);

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
	matrix GetMinor(int _i, int _j)
	{
		if ( n != m)
		{
			return *(this);
		}
		matrix temp(n-1,m-1);
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
		return matrix(temp);
	}
	double determinant()
	{
		if(n != m || n==0)
			return 0;
		if(n==1)
			return data[0];
		double det =0;
		for( int i(0); i < n; i++)
			det = det + powf(-1,i)*data[i]*GetMinor(0,i).determinant();
		return det;
	}
	matrix inverse()
	{
		if (n != m || n == 0)
			return *this;
		double det = determinant();
		if (det == 0)
			return (*this);
		matrix _inverse(n, m);
		for (int i(0); i < n; i++)
			for (int j(0); j < m; j++)
			{
				_inverse.set(i, j, powf(-1, i + j) * GetMinor(j, i).determinant());
			}

			_inverse = _inverse*pow(det,-1);
			return matrix(_inverse);
	}
	
};
void matrix::set(int i, int j, float data)
{
	this->data[i*n+j] = data;
}
float matrix::get(int i, int j)
{
	return data[i*n+j];
}
matrix::matrix()
{
	n = 0; 
	m = 0;
	data = NULL;
}
matrix::matrix(int n, int m)
{
	this->n = n;
	this->m = m;
	this->data = new float [n*m];
}
matrix::matrix(const matrix &A)
{
	this->n = A.n;
	this->m = A.m;
	this->data = new float[n*m];
	for ( int i(0); i < n*m; i++)
	{
		this->data[i] = A.data[i];
	}

}

