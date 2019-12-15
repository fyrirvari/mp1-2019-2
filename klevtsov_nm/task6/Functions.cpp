#include "math.h"
#define PI 3.14159265359
#define ld long double

void cast(ld& x)
{
	while (x > 2 * PI) { x -= 2 * PI; }
	while (x < -2 * PI) { x += 2 * PI; }
}

//------------------------------------------------------------------------
ld mySin(ld x, ld e, int& n, ld& reference)
{
	//cast(x);
	int i;
	ld res = x, buffer = x;
	reference = sin(x);
	for (i = 3; fabs(res - reference) > e && i < n; i += 2)
	{
		buffer *= (-1) * (x * x) / ((i - 1) * i);
		res += buffer;
	}
	n = (n < i ? n : i);
	return res;
}

//------------------------------------------------------------------------
ld myCos(ld x, ld e, int& n, ld& reference)
{
	//cast(x);
	int i;
	ld res = 1, buffer = 1;
	reference = cos(x);
	for (i = 2; fabs(res - reference) > e && i < n; i += 2)
	{
		buffer *= (-1) * (x * x) / ((i - 1) * i);
		res += buffer;
	}
	n = (n < i ? n : i);
	return res;
}

//------------------------------------------------------------------------
ld myExp(ld x, ld e, int& n, ld& reference)
{
	int i;
	ld res = 1, buffer = 1;
	reference = exp(x);
	for (i = 1; fabs(res - reference) > e && i < n; i++)
	{
		buffer *= x / i;
		res += buffer;
	}
	n = (n < i ? n : i);
	return res;
}
//------------------------------------------------------------------------
ld myAsin(ld x, ld e, int& n, ld& reference)
{
	int i;
	ld res = x, rank = x, up, down;
	reference = asin(x);
	for (i = 3; fabs(res - reference) > e && i < n; i += 2)
	{
		rank *= x * x;
		up = 1;
		for (int j = i - 2; j > 0; j -= 2)
		{
			up *= j;
		}
		down = i;
		for (int j = i - 1; j > 0; j -= 2)
		{
			down *= j;
		}
		res += up * rank / down;
	}
	n = (n < i ? n : i);
	return res;
}

//------------------------------------------------------------------------
ld myAtan(ld x, ld e, int& n, ld& reference)
{
	int i;
	ld res = x, up = x;
	reference = atan(x);
	for (i = 3; fabs(res - reference) > e && i < n; i += 2)
	{
		up *= (-1) * x * x;
		res += up / i;
	}
	n = (n < i ? n : i);
	return res;
}

//------------------------------------------------------------------------