#include "stdafx.h"
#include "Fraction.h"

Fraction::Fraction(int a, int b) {
	try {
		up = a;
		down = b;
		if (down == 0) throw(1);
	}
	catch (...) {
		cout << "Не возможно создать дробь, так как знаменатель не должен равняться 0!" << endl;
	}
}

//Перезгрузка операций
Fraction Fraction::operator +(const Fraction f2) const
{
	
	int resUp = up * f2.down + f2.up * down;					//Вычисляем числитель
	int resDown = down * f2.down;								//Находим общий знаменатель
	return Fraction(resUp, resDown);							//Возвращаем дробь с полученными числителем и знаменателем
}

Fraction Fraction::operator + (const int a) const {
	Fraction f2(a, 1);
	return operator +(f2);
}

Fraction Fraction::operator - (const Fraction f2) const {
	int resUp = up * f2.down - f2.up * down;					
	int resDown = down * f2.down;								
	return Fraction(resUp, resDown);
}

Fraction Fraction::operator - (const int a) const {
	Fraction f2(a, 1);
	return operator -(f2);
}

Fraction Fraction::operator * (const Fraction f2) const {
	int resUp = (up * f2.up);
	int resDown = (down * f2.down);
	return Fraction(resUp, resDown);
}

Fraction Fraction::operator * (const int a) const {
	Fraction f2(a, 1);
	return operator *(f2);
}

Fraction Fraction::operator / (const Fraction f2) const {
	int resUp = (up * f2.down);
	int resDown = (down * f2.up);
	if (resDown == 0) {
		cout << "Ошибка! Деление на ноль" << endl;
		return 0;
	}
	return Fraction(resUp, resDown);
}

Fraction Fraction::operator / (const int a) const {
	Fraction f2(a, 1);
	return operator /(f2);
}

const Fraction& Fraction::operator = (const Fraction& f2) {
	if (&f2 == this) return *this;
	up = f2.up;
	down = f2.down;
	return Fraction(up, down);
}

istream& operator >> (istream& s, Fraction& fraction) {
	do {
		cout << "Введите дробь: Числитель ";
		cin >> fraction.up;
		cout << "Знаменатель";
		s >> fraction.down;
		if (fraction.down == 0) cout << "Знаменатель не должен = 0";
	} while (fraction.down == 0);
	return s;
}
ostream& operator << (ostream& s, Fraction& fraction) {
	fraction.lowterms();												//Сокращаем дробь
	s << fraction.up << "|" << fraction.down << endl;
	return s;
}

//Функция сокращения дроби
void Fraction::lowterms() {
	if (up == 0) return;

	if (up == down) {
		up = 1;
		down = 1;
		return;
	}

	//Алгоритм Евклида
	//R1 = a-b*q1, где a, b числа, НОД кторых надо найти, q-целочисленное частное, r - остаток от деления
	//R2 = b - R1*q2 = a(-q1)+ b(1+q1q2)
	//... 
	//НОД(a,b)Rn = a*s+bt
	//таким образом получается, что НОД(а,б) = R(n-1) или b в конце цикла
	int a, b, q, r, NOD = 0; 
	if (up > down) {
		a = up;
		b = down;
	}
	else {
		a = down;
		b = up;
	}
	while (1) {
		q = static_cast<int>(a / b);		//находим частное
		r = a - b*q;						//находим остаток
		if (r == 0) break;					//Если r=0 алгоритм завершен и НОД хранится в b
		//задаем новые a и b
		a = b;
		b = r;
	}
	NOD = b;
	up /= NOD;
	down /= NOD;
}


