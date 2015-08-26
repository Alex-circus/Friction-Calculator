#include "stdafx.h"
#include "Fraction.h"

Fraction::Fraction(int a, int b) {
	try {
		up = a;
		down = b;
		if (down == 0) throw(1);
	}
	catch (...) {
		cout << "�� �������� ������� �����, ��� ��� ����������� �� ������ ��������� 0!" << endl;
	}
}

//����������� ��������
Fraction Fraction::operator +(const Fraction f2) const
{
	
	int resUp = up * f2.down + f2.up * down;					//��������� ���������
	int resDown = down * f2.down;								//������� ����� �����������
	return Fraction(resUp, resDown);							//���������� ����� � ����������� ���������� � ������������
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
		cout << "������! ������� �� ����" << endl;
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
		cout << "������� �����: ��������� ";
		cin >> fraction.up;
		cout << "�����������";
		s >> fraction.down;
		if (fraction.down == 0) cout << "����������� �� ������ = 0";
	} while (fraction.down == 0);
	return s;
}
ostream& operator << (ostream& s, Fraction& fraction) {
	fraction.lowterms();												//��������� �����
	s << fraction.up << "|" << fraction.down << endl;
	return s;
}

//������� ���������� �����
void Fraction::lowterms() {
	if (up == 0) return;

	if (up == down) {
		up = 1;
		down = 1;
		return;
	}

	//�������� �������
	//R1 = a-b*q1, ��� a, b �����, ��� ������ ���� �����, q-������������� �������, r - ������� �� �������
	//R2 = b - R1*q2 = a(-q1)+ b(1+q1q2)
	//... 
	//���(a,b)Rn = a*s+bt
	//����� ������� ����������, ��� ���(�,�) = R(n-1) ��� b � ����� �����
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
		q = static_cast<int>(a / b);		//������� �������
		r = a - b*q;						//������� �������
		if (r == 0) break;					//���� r=0 �������� �������� � ��� �������� � b
		//������ ����� a � b
		a = b;
		b = r;
	}
	NOD = b;
	up /= NOD;
	down /= NOD;
}


