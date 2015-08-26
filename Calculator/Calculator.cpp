// Calculator.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "Fraction.h"
#include "PostfixNotationExprassion.h"
#include <locale>
#include <conio.h>
#include <map>

bool ExpressionCheck(const string expression); //�������� �� ������������ ���������

int main()
{
	setlocale(LC_ALL, "rus");
	int nValues;				//���-�� ����������
	char ch = 0;
	string expression;			//���������
	Fraction res;				//��������� ����������

	while (ch != 2) {
		cout << "������� ���������� ����������: " << endl;
		cin >> nValues;

		Fraction* Values = new Fraction(nValues);		
		do {
			cout << "������� ��������� � ����� ����, ��������� ����� ����������� �������� � �������� ����������: " << endl
				<< "������: a+b*c" << endl;
			cin >> expression;
		} while (ExpressionCheck(expression) != true);			//���� ��������� � ��� ��������

		expression = PostfixNotation(expression);				//������� � ����������� �����
		//cout << expression << endl;								// ����� ���������  ���������� �����

		for (int i = 0; i < nValues; i++) {							//���� ����������
			cout << "������� ���������� " << (char)('a' + i) << endl;
			cin >> Values[i];
		}

		res = PostfixSolution(expression, Values, 5);				//������� 
		cout << res;
		delete Values;
		cout << "�������:"
			<< "\n 1. ���� ������ ���������"
			<< "\n 2. �����" << endl;
		cin >> ch;
	}
    return 0;
}

//��������� ������������ ���������� ���������
//���������� false, ���� ��������� ���������� ��� ������������� ���������,
//����� ����������� 2 ����� �������� ��� 2 ����� ������
//���� ��������� �������� ������ �� ������������ ���-�� ��������
bool ExpressionCheck(const string expression) {
	if (expression[0] == '+' || expression[0] == '-' ||			
		expression[0] == '/' || expression[0] == '*') {
		cout << "��������� �� ������ ���������� � ��������";
		return false;
	}
	
	int OpenBkt = 0, i;
	bool PrevSumbol = false; //����� false, ���� ���������� ������ - ���� ��������, � true - ���� �����, ����� ��� ����������� ������

	for (i = 0; i < expression.length(); i++) {		
		if ( isalnum (expression[i]) ) {			
			if (PrevSumbol == true) {
				cout << "������! ��� ����� ��� ����� ������ " 
					 << expression[i - 1] << expression[i] << endl;
				return false;
			}
			PrevSumbol = true;
		}

		else {
			if (PrevSumbol == false) {
				cout << "������! ��� ����� �������� ������ "
					<< expression[i - 1] << expression[i] << endl;
				return false;
			}
			PrevSumbol = false;
		}
		if (expression[i] == '(') {
			OpenBkt++;
			PrevSumbol = false;
		}
		if (expression[i] == ')') {
			OpenBkt--;
			PrevSumbol = true;
		}
	}
	if (OpenBkt != 0) {
		cout << "������! ���������� �������� ������ �������������� ���������� ��������" << endl;
		return false;
	}
	if (expression[i] == '+' || expression[i] == '-' ||
		expression[i] == '/' || expression[i] == '*') {
		cout << "��������� �� ������ ������������� ���������";
		return false;
	}
	return true;
		
}


