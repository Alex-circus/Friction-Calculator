#pragma once
#include "stdafx.h"
#include <iostream>

using namespace std;

//����� �����
class Fraction
{
private:
	int up;										//���������
	int down;									//�����������
public:
	//������������
	Fraction() : up(0), down(1) {}
	Fraction(int a, int b = 1);
	//���������� ��������
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
	//����������� ��������
	bool operator == (Fraction f2) {
		return (up == f2.up && down == f2.down);
	}
	bool operator != (Fraction f2) {
		return (up == f2.up && down == f2.down);
	}
	//������ �������
	void lowterms();							//���������� �����
};