// Calculator.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Fraction.h"
#include "PostfixNotationExprassion.h"
#include <locale>
#include <conio.h>
#include <map>

bool ExpressionCheck(const string expression); //проверка на корректность выржаения

int main()
{
	setlocale(LC_ALL, "rus");
	int nValues;				//кол-во переменных
	char ch = 0;
	string expression;			//выражение
	Fraction res;				//результат вычислений

	while (ch != 2) {
		cout << "Введите количество переменных: " << endl;
		cin >> nValues;

		Fraction* Values = new Fraction(nValues);		
		do {
			cout << "Введите выражение в общем виде, используя буквы английского алфавита в качестве переменных: " << endl
				<< "Пример: a+b*c" << endl;
			cin >> expression;
		} while (ExpressionCheck(expression) != true);			//ввод выражения и его проверка

		expression = PostfixNotation(expression);				//перевод в постфиксную форму
		//cout << expression << endl;								// вывод выражения  постфикной форме

		for (int i = 0; i < nValues; i++) {							//ввод переменных
			cout << "Введите переменную " << (char)('a' + i) << endl;
			cin >> Values[i];
		}

		res = PostfixSolution(expression, Values, 5);				//решение 
		cout << res;
		delete Values;
		cout << "Нажмите:"
			<< "\n 1. Ввод нового выражения"
			<< "\n 2. Выход" << endl;
		cin >> ch;
	}
    return 0;
}

//Проверяет корректность введенного выражения
//возвращает false, если выражение начинается или заканчивается операцией,
//когда встречается 2 знака операции или 2 буквы подряд
//если количеств открытых скобок не соответсвует кол-ву закрытых
bool ExpressionCheck(const string expression) {
	if (expression[0] == '+' || expression[0] == '-' ||			
		expression[0] == '/' || expression[0] == '*') {
		cout << "Выражение не должно начинаться с операции";
		return false;
	}
	
	int OpenBkt = 0, i;
	bool PrevSumbol = false; //равно false, если предыдущий символ - знак операции, и true - если буква, цифра или закрывающая скобка

	for (i = 0; i < expression.length(); i++) {		
		if ( isalnum (expression[i]) ) {			
			if (PrevSumbol == true) {
				cout << "Ошибка! Две буквы или цифры подряд " 
					 << expression[i - 1] << expression[i] << endl;
				return false;
			}
			PrevSumbol = true;
		}

		else {
			if (PrevSumbol == false) {
				cout << "Ошибка! Два знака операции подряд "
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
		cout << "Ошибка! Количество открытых скобок несоответсвует количеству закрытых" << endl;
		return false;
	}
	if (expression[i] == '+' || expression[i] == '-' ||
		expression[i] == '/' || expression[i] == '*') {
		cout << "Выражение не должно заканчиваться операцией";
		return false;
	}
	return true;
		
}


