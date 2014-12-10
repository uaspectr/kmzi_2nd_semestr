#pragma once

class Bnumb
{
private:
	int sz; // размер числа
	unsigned char* digits; // знаки числа
	int sgn; //знак - 0 положительный , 1 - отрицательный

public:
	//Конструкторы
	Bnumb();
	Bnumb(const char* instring);
	Bnumb(const Bnumb& RValue);
	Bnumb(int RValue);

	~Bnumb(); // деструктор

	char* GetString(); // функция получения строки в 10-й записи


	// Операции с файлами
	bool readtxt(const char* path);
	bool writetxt(const char* path);
	bool readbin(const char* path);
	bool writebin(const char* path);





	//Операторы сравнения
	bool operator>(const Bnumb& Y);
	bool operator>=(const Bnumb& Y);
	bool operator<(const Bnumb& Y);
	bool operator<=(const Bnumb& Y);
	bool operator==(const Bnumb& Y);
	bool operator!=(const Bnumb& Y);
	char* __str__();
	char* __repr__();







	//Операторы инкриментирования и декриментирования
	Bnumb operator++();
	Bnumb operator++(int);
	Bnumb operator--();
	Bnumb operator--(int);





	//Арифметические операторы
	Bnumb& operator=(const Bnumb& RValue);
	Bnumb operator+(const Bnumb& RValue) const;
	Bnumb operator-() const;
	Bnumb operator-(const Bnumb& RValue) const;
	Bnumb operator*(const Bnumb& RValue) const;
	Bnumb operator/(const Bnumb& RValue) const;
	Bnumb operator%(const Bnumb& RValue) const;
	Bnumb operator^(const Bnumb& RValue) const;

private:
	void setup_sz(int size); // устанавливает размер
	unsigned char & operator[](int i);
	unsigned char operator[](int i) const;
	void deletezero(); // Название функции говорит само за себя
	int compare(const Bnumb& Y);
	void Sft(int s);

	Bnumb summaryandsubstract(const Bnumb& LValue, const Bnumb& RValue) const;
	Bnumb Multiplicate(const Bnumb X, const Bnumb Y) const;
	Bnumb Divide(const Bnumb& X, const Bnumb& Y,Bnumb &rem) const;


};

Bnumb Pow(Bnumb& X,Bnumb& Y, Bnumb& Modul);

