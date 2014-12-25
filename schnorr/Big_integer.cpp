#include "Big_integer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <vector>
using std::ifstream;
using std::ofstream;

#define DIV_BY_ZERO 1
#define FNV_32_PRIME ((short)0x012)

Bnumb::Bnumb()
{//Конструктор по умолчанию
	this->sz = 1;
	this->sgn= 0;
	this->digits = new unsigned char[1];
	this->digits[0] = 0;
}


Bnumb::Bnumb(const char* instring)
{
	//Конструктор от входной строки
	
	int instringLen = strlen(instring);
	int instringSign = 0;
	if (instring[0] == '-')
	{
		instringSign = 1;
		instringLen--;
	}

	Bnumb res;

	Bnumb tenspower = 1;  // Для того,чтобы преобразовать char в число по основанию 256 необходимо каждый 
								//Каждый символ превести к int значению и далее умножить на 10 в степени i, где i номер разряда.

	for (int i = instringLen + instringSign - 1; i >= instringSign; i--)
	{
		int rzrd = instring[i] - '0';
		res = res + tenspower * rzrd;
		tenspower = tenspower * 10;
	}
	res.sgn = instringSign;

	this->sz = 0;
	*this = res;
}

Bnumb::Bnumb(const Bnumb &RValue)
{	//конструктор от Big_integer
	this->sz = RValue.sz;
	this->digits = new unsigned char[this->sz];
	this->sgn = RValue.sgn;
	memcpy(digits, RValue.digits, this->sz * sizeof(unsigned char));
	return;
}

Bnumb::Bnumb(int value)
{   
	//Конструктор от int-ового значения

	this->digits = new unsigned char[11]();
	this->sz = 0;
	this->sgn = 0;
	if (value < 0)
	{
		this->sgn = 1;
		value = -value;
	}
	do
	{
		this->sz++;
		this->digits[this->sz - 1] = value % 256;
		value = value / 256;
	} while (value > 0);

	this->deletezero();
}

Bnumb::~Bnumb()
{// Деструктор
	delete[] digits;
}

char* Bnumb::GetString()
{
	//Фукция получения строки в 10-й записи
	
	Bnumb tmp = *this; 
	tmp.sgn = 0;
	
	std::vector<char> tmpString; // Вектор для хранения строки


	while (tmp != (int)0)
	{
		Bnumb rem;
		tmp = Divide(tmp, 10, rem); 
		char ost = rem[0] + '0'; 
		tmpString.push_back(ost);
	}

	
	if (this->sgn)
		tmpString.push_back('-');


	int stringSize = tmpString.size();
	char* string = new char[stringSize + 1]();

	for (int i = 0; i < tmpString.size(); i++)
	{
		string[stringSize - i - 1] = tmpString[i];
	}

	return string;
}


bool Bnumb::readtxt(const char* path)
{
	ifstream fp(path);
	if (fp.fail())
		return false;

	fp.seekg(0, std::ios::end);
	int File_size = fp.tellg();
	fp.seekg(0, std::ios::beg);

	char* string = new char[File_size + 1]();
	fp >> string;
	fp.close();

	*this = Bnumb(string);
	delete[] string;
	return true;
}

bool Bnumb::writetxt(const char* path)
{
	ofstream fp_r(path);
	if (fp_r.fail())
		return false;

	char* string = this->GetString();
	fp_r << string;
	delete[] string;
	fp_r.close();

	return true;
}

bool Bnumb::writebin(const char* path)
{

	ofstream fp_ob(path, std::ios::binary);
	if (fp_ob.fail())
		return false;

	fp_ob.write((char*) this->digits, this->sz); 

	fp_ob.close();
	return true;
}

bool Bnumb::readbin(const char* path)
{
	ifstream fp_ib(path, std::ios::binary);
	if (fp_ib.fail())
		return false;

	fp_ib.seekg(0, std::ios::end);
	int File_size = fp_ib.tellg();
	fp_ib.seekg(0, std::ios::beg);

	delete[] this->digits;
	this->digits = new unsigned char[File_size];
	this->sz = File_size;
	this->sgn = 0;

	fp_ib.read((char*)this->digits, File_size);
	fp_ib.close();

	return true;
}


void Bnumb::setup_sz(int newSize)
{	
	if (this->sz)
		delete[] this->digits;
	this->sz = newSize;
	this->sgn = 0;
	this->digits = new unsigned char[this->sz]();
}

void Bnumb::deletezero()
{
	while ((sz - 1)&& digits[sz - 1] == 0)
		this->sz--;

	if (this->sz == 1 && digits[0] == 0)
		this->sgn = 0;
}

int Bnumb::compare(const Bnumb& Y)
{

	int SgnFlag = 1;
	if (this->sgn == 1)
		SgnFlag = -1;

	if (this->sgn != Y.sgn)
		return SgnFlag;

	if (this->sz > Y.sz)
		return SgnFlag;

	if (this->sz < Y.sz)
		return -SgnFlag;

	int i = this->sz - 1;

	while (this->digits[i] == Y[i] && i > 0)
	{
		i--;
	}
	return ( (int) this->digits[i] - (int) Y[i]) * SgnFlag;
}

void Bnumb::Sft(int s)
{

	unsigned char* newdigits = new unsigned char[this->sz + s]();
	for (int i = 0; i < this->sz; i++)
	{
		newdigits[i + s] = this->digits[i];
	}

	delete[] this->digits;
	this->digits = newdigits;
	this->sz += s;
	this->deletezero();
}


Bnumb Bnumb::summaryandsubstract(const Bnumb& LValue, const Bnumb& RValue) const
{
	Bnumb A = LValue, B = RValue; 
	A.sgn = 0;
	B.sgn = 0;
	if (A > B)
	{
		A.sgn = LValue.sgn;
		B.sgn = RValue.sgn;
	}
	else
	{
		A = RValue;
		B = LValue;
	}

	if (A.sgn == B.sgn)
	{

		Bnumb res;
		res.setup_sz(A.sz + 1);

		int cf = 0;

		for (int i = 0; i < A.sz; i++)
		{
			int tmp = A[i] + cf;
			if (i < B.sz)
				tmp += B[i];

			res[i] = tmp % 256;
			cf = tmp / 256;
		}

		res[A.sz] = cf;
		res.sgn = A.sgn;
		res.deletezero();
		return res;
	}
	else
	{
		Bnumb res;
		res.setup_sz(A.sz);

		int cf = 0;
		for (int i = 0; i < A.sz; i++)
		{
			int tmp = A[i] - cf;
			if (i < B.sz)
				tmp -= B[i];

			cf = 0;
			if (tmp < 0)
			{
				cf = 1;
				tmp += 256;
			}
			res[i] = tmp;
		}

		res.sgn = A.sgn;
		res.deletezero();
		return res;
	}
}

Bnumb Bnumb::Multiplicate(const Bnumb X, const Bnumb Y) const
{
	Bnumb res;
	res.setup_sz(X.sz + Y.sz);
	int cf = 0;
	for (int i = 0; i < Y.sz; i++)
	{
		cf = 0;
		for (int j = 0; j < X.sz; j++)
		{
			int tmp = (int) Y[i] * (int) X[j] + (int) cf + (int) res[i + j];
			cf = tmp / 256;
			res[i + j] = tmp % 256;
		}
		res[i + X.sz] = cf;
	}

	res.sgn = (X.sgn != Y.sgn);
	res.deletezero();
	return res;
}

Bnumb Bnumb::Divide(const Bnumb& X, const Bnumb& Y, Bnumb &rem) const
{
	rem = X;
	rem.sgn = 0;

	Bnumb divider = Y;
	divider.sgn = 0;

	if (divider == Bnumb((int)0))
	{
		printf("DIV_BY_ZERO!!!!\n");
		exit(1);
	}

	if (rem < divider)
	{
		rem = X;
		return Bnumb((int)0);
	}

	Bnumb res;
	res.setup_sz(X.sz - Y.sz + 1);

	for (int i = X.sz - Y.sz + 1; i; i--)
	{
		int search_limit_max = 256;
		int search_limit_min = 0;
		int Value = search_limit_max;


		while (search_limit_max - search_limit_min > 1)
		{
			Value = (search_limit_max + search_limit_min) / 2;

			//tmp = Value * divider * 256^i;
			Bnumb tmp = divider * Value;
			tmp.Sft(i - 1);	// умножение на 256^(i - 1)
			
			if (tmp > rem)
				search_limit_max = Value;
			else
				search_limit_min = Value;
		}
		Bnumb tmp = divider * search_limit_min;
		tmp.Sft(i - 1); // умножение на 256 ^ (i - 1)
		rem = rem - tmp;
		res[i - 1] = search_limit_min;
	}

	res.sgn = (X.sgn != Y.sgn);
	rem.sgn = (X.sgn != Y.sgn);
	rem.deletezero();
	res.deletezero();

	return res;
}

short Hash(char* str)
{
	short hval = 0x345;


	while(*str)
	{
		hval *= FNV_32_PRIME;
		hval ^= (short)*str++;
	}

	return abs(hval);
}


Bnumb Pow(Bnumb& X,Bnumb& Y, Bnumb& mod)
{
	Bnumb res(1), xx = X , yy = Y;
	Bnumb temp1(2);
	Bnumb one(1);
	Bnumb zero(0);

	while(yy != zero)
	{
		if((yy % temp1) == one)
		{
			res = (res*xx)%mod;
		}

		xx = (xx*xx) % mod;

		yy = yy /temp1;
	}

	return res;
}

unsigned char & Bnumb::operator[](int i)
{
	if (i < 0)
		return this->digits[this->sz + i];
	return this->digits[i];
}

unsigned char Bnumb::operator[](int i) const
{
	if (i < 0)
		return this->digits[this->sz + i];
	return this->digits[i];
}


Bnumb& Bnumb::operator=(const Bnumb& RValue)
{
	if (this->sz)
		delete[] this->digits;

	this->sz = RValue.sz;
	this->digits = new unsigned char[sz];
	this->sgn = RValue.sgn;
	memcpy(digits, RValue.digits, sz);
	return *this;
}

Bnumb Bnumb::operator-() const
{
	Bnumb res = *this;
	res.sgn = !res.sgn;
	return res;
}

Bnumb Bnumb::operator^(const Bnumb& RValue) const
{
	Bnumb res = 1;
	Bnumb base = *this;
	for (Bnumb i = RValue; i > (int)0; i = i - 1)
		res = res * base;
	return res;
}

Bnumb Bnumb::operator+(const Bnumb& RValue) const
{
	return summaryandsubstract(*this, RValue);
}

Bnumb Bnumb::operator-(const Bnumb& RValue) const
{
	return *this + (-RValue);
}

Bnumb Bnumb::operator*(const Bnumb& RValue) const
{
	return Multiplicate(*this, RValue);
}

Bnumb Bnumb::operator/(const Bnumb& RValue) const
{
	Bnumb rem;
	return Divide(*this, RValue, rem);
}

Bnumb Bnumb::operator%(const Bnumb& RValue) const
{
	Bnumb rem;
	Divide(*this, RValue, rem);
	return rem;
}

bool Bnumb::operator>(const Bnumb& Y)
{
	return this->compare(Y) > 0;
}


bool Bnumb::operator>=(const Bnumb& Y)
{
	return this->compare(Y) >= 0;
}

bool Bnumb::operator<(const Bnumb& Y)
{
	return this->compare(Y) < 0;
}

bool Bnumb::operator<=(const Bnumb& Y)
{
	return this->compare(Y) <= 0;
}

bool Bnumb::operator==(const Bnumb& Y)
{
	return this->compare(Y) == 0;
}

bool Bnumb::operator!=(const Bnumb& Y)
{
	return this->compare(Y) != 0;
}

char* Bnumb::__str__()
{
	return GetString();
}

char* Bnumb::__repr__()
{
	return GetString();
}

Bnumb Bnumb::operator++()
{
Bnumb value = *this;
*this = *this + 1;
return value;
}

Bnumb Bnumb::operator++(int)
{
*this = *this + 1;
return *this;
}
Bnumb Bnumb::operator--()
{
Bnumb value = *this;
*this = *this - 1;
return value;
}

Bnumb Bnumb::operator--(int)
{
*this = *this - 1;
return *this;
}
