#include "stdafx.h"
#include "PostfixNotationExprassion.h"
#include <map>
#include <stack>
#include <vector>
#include <iostream>
#include <locale>


using namespace std;

string PostfixNotation(string str) {
	stack<char> stack;												//���� ��� ������ ��������
	string Notation;												//����������� ������
	for (unsigned int i = 0; i < str.length(); i++) {				//���� �� ������ ���������
		if (isalnum(str[i]) || str[i] == '|') Notation += str[i];		//���� ������� ����� ��� ���� ����� ��������� � ����������� ������
		else {
			switch (str[i]) {

			case '-': //���� � ����� ��� �������� ��� ������� ��������� ����� �������� ����������� ������, �������� ������� � ����;
			case '+':
				if (stack.empty()) stack.push(str[i]);
				else {
					if (stack.top() == '(') stack.push(str[i]);
					//���� ����� �������� ����� ������� ��� ������ ���������, ��� ������� �������� � �����
					else {
						if (stack.top() == '+' || stack.top() == '-' || stack.top() == '*' || stack.top() == '/') {
							//�� ��������, ����������� � �����, �� ��������� ����������� ������ 
							//��� �� �������� � ����������� �������, ��� � ����� ��������, 
							//��������������� � ����������� ������,
							while (stack.top() != '(') {
								Notation += stack.top();
								stack.pop();
								if (stack.empty()) break;
							}
							stack.push(str[i]); //� ����� �������� ������� � ����.
						}
					}
				}
				break;
			case '/': //���� ����� �������� ����� ������� ���������, ��� ������� �������� � �����, �� ����� �������� ������� � ����
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
							stack.push(str[i]); //� ����� �������� ������� � ����.
						}
					}
				}
				break;

			case '(': stack.push(str[i]); break; //����������� ������ �������� � ����
			case ')':  //����������� ������ ����������� �� ����� � ����������� ������ ��� �������� �� ��������� ����������� ������
				while (stack.top() != '(') {
					Notation += stack.top();
					stack.pop();
				}
				stack.pop(); //����������� ������ ��������� �� �����
				break;
			default: cout << "�������� ������" << str[i] << endl;
			}
		}
	}
	while (!stack.empty()) {
		Notation += stack.top();
		stack.pop();
	}
	return Notation;
}

//���������� ��������� � ����������� �����
//������������� ���������, ���� ����������� ���������� ��� ����� ������� � ����, 
//���� �������� - ��������� �� ����� 2 ������� �������� � ��������� ��� ��� ��� ��������
Fraction PostfixSolution(string PostfNot, Fraction* values,unsigned int nVal){
	if (nVal > 26) {
		cout << "������� ����� ����������" << endl;
		return 0;
	}
	Fraction sum1, sum2, res;
	stack<Fraction> stack;
	map<char, Fraction> container;				//������ ��� ���������� � ����������� �� ��������
	char ch = 'a';

	for (unsigned int count = 0; count < nVal; count++) {			//����������� �������� �����
		container[ch + count] = values[count];
	}
						
	for (unsigned int i = 0; i < PostfNot.length(); i++) {
		if (isalnum(PostfNot[i])) {
			//���� ����������� ����� - ����� ������� � ����
			if (PostfNot[i] >= '0' && PostfNot[i] <= '9') stack.push (PostfNot[i] -  '0');
			//���� ����������� ���������� ������� � ���� �� ��������
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
					cout << "������! ������� �� ����";
				}
				stack.push(res);
				break;

			case '*':
				sum1 = stack.top(); stack.pop();
				sum2 = stack.top(); stack.pop();
				res = sum1 * sum2;
				stack.push(res);
				break;

			default: cout << "����������� ������ " << PostfNot[i]; break;
			}
		}
		//cout << "stack " << stack.top() << endl;
	}
	res = stack.top();
	stack.pop();
	return res;
}