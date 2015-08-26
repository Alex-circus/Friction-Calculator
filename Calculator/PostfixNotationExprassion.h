#pragma once
#include "stdafx.h"
#include <string>
#include "Fraction.h"

using namespace std;
string PostfixNotation(string str);			//запись выражения в постфиксной форме
Fraction  PostfixSolution(string PostfixNot, Fraction* mass, unsigned int n);		//решение выражения в постфиксной форме