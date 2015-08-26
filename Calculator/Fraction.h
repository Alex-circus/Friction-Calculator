#pragma once
#include "stdafx.h"
#include <iostream>

using namespace std;

//Класс дробь
class Fraction
{
private:
	int up;										//Числитель
	int down;									//Знаменатель
public:
	//Конструкторы
	Fraction() : up(0), down(1) {}
	Fraction(int a, int b = 1);
	//Перегрузки операций
	Fraction operator + (const Fraction f2) const;
	Fraction operator + (const int) const;
	Fraction operator - (const Fraction f2) const;
	Fraction operator - (const int) const;
	Fraction operator * (const Fraction f2) const;
	Fraction operator * (const int) const;
	Fraction operator / (const Fraction f2) const;
	Fraction operator / (const int) const;
	const Fraction&  operator = (const Fraction& fr2);
	friend istream& operator >> (istream&, Fraction&);
	friend ostream& operator << (ostream&, Fraction&);
	//Логическиие операции
	bool operator == (Fraction f2) {
		return (up == f2.up && down == f2.down);
	}
	bool operator != (Fraction f2) {
		return (up == f2.up && down == f2.down);
	}
	//Прочие функции
	void lowterms();							//Сокращение дроби
};