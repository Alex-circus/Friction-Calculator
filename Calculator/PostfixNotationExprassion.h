#pragma once
#include "stdafx.h"
#include <string>
#include "Fraction.h"

using namespace std;
string PostfixNotation(string str);			//������ ��������� � ����������� �����
Fraction  PostfixSolution(string PostfixNot, Fraction* mass, unsigned int n);		//������� ��������� � ����������� �����