#include "stdafx.h"
#include "PostfixNotationExprassion.h"
#include <map>
#include <stack>
#include <vector>
#include <iostream>
#include <locale>


using namespace std;

string PostfixNotation(string str) {
	stack<char> stack;												//Стек для записи операции
	string Notation;												//Формируемая запись
	for (unsigned int i = 0; i < str.length(); i++) {				//Цикл по строке выражения
		if (isalnum(str[i]) || str[i] == '|') Notation += str[i];		//Если введена цифра или знак дроби добавляем в формируемую запись
		else {
			switch (str[i]) {

			case '-': //если в стеке нет операций или верхним элементом стека является открывающая скобка, операции кладётся в стек;
			case '+':
				if (stack.empty()) stack.push(str[i]);
				else {
					if (stack.top() == '(') stack.push(str[i]);
					//если новая операция имеет меньший или равный приоритет, чем верхняя операции в стеке
					else {
						if (stack.top() == '+' || stack.top() == '-' || stack.top() == '*' || stack.top() == '/') {
							//то операции, находящиеся в стеке, до ближайшей открывающей скобки 
							//или до операции с приоритетом меньшим, чем у новой операции, 
							//перекладываются в формируемую запись,
							while (stack.top() != '(') {
								Notation += stack.top();
								stack.pop();
								if (stack.empty()) break;
							}
							stack.push(str[i]); //а новая операции кладётся в стек.
						}
					}
				}
				break;
			case '/': //если новая операции имеет больший приоритет, чем верхняя операции в стеке, то новая операции кладётся в стек
			case '*':
				if (stack.empty()) stack.push(str[i]);
				else {
					if (stack.top() == '+' || stack.top() == '-' || stack.top() == '(') stack.push(str[i]);
					else {
						if (stack.top() == '*' || stack.top() == '/') {
							while (stack.top() != '(') {
								Notation += stack.top();
								stack.pop();
								if (stack.empty()) break;
							}
							stack.push(str[i]); //а новая операции кладётся в стек.
						}
					}
				}
				break;

			case '(': stack.push(str[i]); break; //открывающая скобка кладется в стек
			case ')':  //Закрывающая скобка выталкивает из стека в формируемую запись все операции до ближайшей открывающей скобки
				while (stack.top() != '(') {
					Notation += stack.top();
					stack.pop();
				}
				stack.pop(); //открывающая скобка удаляется из стека
				break;
			default: cout << "Неверный символ" << str[i] << endl;
			}
		}
	}
	while (!stack.empty()) {
		Notation += stack.top();
		stack.pop();
	}
	return Notation;
}

//вычисление выражения в постфиксной форме
//просматриваем выражение, если встречается переменная или цифра заносим в стек, 
//если операция - извлекаем из стека 2 верхних значения и выполняем для них эту операцию
Fraction PostfixSolution(string PostfNot, Fraction* values,unsigned int nVal){
	if (nVal > 26) {
		cout << "Слишком много переменных" << endl;
		return 0;
	}
	Fraction sum1, sum2, res;
	stack<Fraction> stack;
	map<char, Fraction> container;				//Хранит имя переменной и присовенное ей значение
	char ch = 'a';

	for (unsigned int count = 0; count < nVal; count++) {			//присваивает значения ключу
		container[ch + count] = values[count];
	}
						
	for (unsigned int i = 0; i < PostfNot.length(); i++) {
		if (isalnum(PostfNot[i])) {
			//Если встречается цифра - сразу заносим в стек
			if (PostfNot[i] >= '0' && PostfNot[i] <= '9') stack.push (PostfNot[i] -  '0');
			//Если встречается переменная заносим в стек ее значение
			else stack.push(container[PostfNot[i]]);
		}

		else {
			switch (PostfNot[i]) {
			case '+':	
				sum1 = stack.top(); stack.pop();
				sum2 = stack.top(); stack.pop();
				res = sum1 + sum2;
				stack.push(res);
				break;

			case '-':		
				sum1 = stack.top(); stack.pop();
				sum2 = stack.top(); stack.pop();
				res = sum2 - sum1;
				stack.push(res);
				break;

			case '/':
				sum1 = stack.top(); stack.pop();
				sum2 = stack.top(); stack.pop();
				try {
					res = sum2 / sum1;
				}
				catch (...) {
					cout << "Ошибка! Деление на ноль";
				}
				stack.push(res);
				break;

			case '*':
				sum1 = stack.top(); stack.pop();
				sum2 = stack.top(); stack.pop();
				res = sum1 * sum2;
				stack.push(res);
				break;

			default: cout << "Неизвестный символ " << PostfNot[i]; break;
			}
		}
		//cout << "stack " << stack.top() << endl;
	}
	res = stack.top();
	stack.pop();
	return res;
}