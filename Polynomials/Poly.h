#pragma once

#include <stdlib.h>
#include <math.h>

class Polynomial
{
private:
	void Start(unsigned int _degree)
	{
		this->degree = _degree;
		this->p = (double*)malloc((_degree + 1) * sizeof(double));
		for (unsigned int i = 0; i <= _degree; i++) this->p[i] = 0;
	}

	void Start(unsigned int _degree, double* _p)
	{
		this->degree = _degree;
		this->p = _p;
	}

public:
	double* p;
	unsigned int degree;

	Polynomial()
	{
		this->degree = NULL;
		this->p = NULL;
	}

	Polynomial(unsigned int _degree)
	{
		Start(_degree);
	}

	Polynomial(unsigned int _degree, double* _p)
	{
		Start(_degree, _p);
	}

	void Reset()
	{
		free(this->p);
		this->degree = 0;
	}

	void Set(unsigned int _degree)
	{
		Reset();
		Start(_degree);
	}

	void Set(unsigned int _degree, double* _p)
	{
		Reset();
		Start(_degree, _p);
	}

	void Copy(Polynomial* pol)
	{
		Set(pol->degree);
		for (int i = 0; i <= pol->degree; i++) this->p[i] = pol->p[i];
	}

	void Differentiate(Polynomial* pol)
	{
		unsigned int d_degree = pol->degree - 1;
		Polynomial d_pol(d_degree);

		for (unsigned int i = 0; i <= d_degree; i++)
		{
			d_pol.p[i] = (double)(i + 1) * pol->p[i + 1];
		}

		this->Set(d_degree, d_pol.p);
	}

	void DifferentiateSelf()
	{
		Differentiate(this);
	}

	void Sum(Polynomial* pol_1, Polynomial* pol_2)
	{
		unsigned int s_degree = pol_1->degree > pol_2->degree ? pol_1->degree : pol_2->degree;
		Polynomial s_pol(s_degree);

		for (unsigned int i = 0; i <= s_degree; i++)
		{
			double a = pol_1->p[1];
			if (i <= pol_1->degree) s_pol.p[i] += pol_1->p[i];
			if (i <= pol_2->degree) s_pol.p[i] += pol_2->p[i];
			a++;
		}

		this->Set(s_degree, s_pol.p);
	}

	void SumSelf(Polynomial* pol)
	{
		Sum(pol, this);
	}

	void Multiply(Polynomial* pol_1, Polynomial* pol_2)
	{
		unsigned int m_degree = pol_1->degree + pol_2->degree;
		Polynomial m_pol(m_degree);

		for (unsigned int i = 0; i <= pol_1->degree; i++)
		{
			for (unsigned int j = 0; j <= pol_2->degree; j++)
			{
				m_pol.p[i + j] += pol_1->p[i] * pol_2->p[j];
			}
		}

		this->Set(m_degree, m_pol.p);
	}

	void MultiplySelf(Polynomial* pol)
	{
		Multiply(pol, this);
	}

	double f(double num)
	{
		double result = 0;
		for (int i = 0; i <= this->degree; i++)
		{
			result += this->p[i] * pow(num, i);
		}

		return result;
	}
};