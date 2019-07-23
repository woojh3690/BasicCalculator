#include "Calculator.h"
#include <math.h>
#include <sstream>

void Calculator::order_stack(string::iterator i, string &postfixExpression, vector<char> &stack)
{
	while (stack.size() != 0 && priority_map[stack.back()] >= priority_map[*i])
	{
		postfixExpression += stack.back();
		postfixExpression += " ";
		stack.pop_back();
	}
	stack.push_back(*i);
}


Calculator::Calculator()
{
	//�⺻ ������ �켱���� �ʱ�ȭ
	priority_map.insert(map<char, int>::value_type('(', 0));
	priority_map.insert(map<char, int>::value_type(')', 0));
	priority_map.insert(map<char, int>::value_type('+', 1));
	priority_map.insert(map<char, int>::value_type('-', 1));
	priority_map.insert(map<char, int>::value_type('*', 2));
	priority_map.insert(map<char, int>::value_type('/', 2));                                                                               
	priority_map.insert(map<char, int>::value_type('^', 3));

	// Ŀ���� �Լ� �ʱ�ȭ
	func_map.insert(map<string, char>::value_type("log", 'l'));

	// Ŀ���� �Լ� �켱���� ����
	for (map<string, char>::iterator it = func_map.begin(); it != func_map.end(); ++it) {
		char func_value = func_map[it->first];
		priority_map.insert(map<char, int>::value_type(func_value, 3)); // �켱���� ����
		simbols_single += func_value; // ���׿����� �߰�
	}
}

string Calculator::GetPostFix(string infixExpression)
{

	string postfixExpression;

	string::iterator i = infixExpression.begin();
	string::iterator start = infixExpression.begin();
	string::iterator end;

	vector<char> stack;

	for (; i != infixExpression.end(); ++i)
	{
		// ������ �ƴҰ�쿡 �н�
		if (simbols.find(*i) == string::npos)
		{
			postfixExpression += *i;
			continue;
		}

		// ������ ó��
		postfixExpression += " ";
		switch (*i)
		{
		case '(': stack.push_back('('); break;
		case ')': 
			while (stack.back() != '(')
			{
				postfixExpression += stack.back();
				postfixExpression += " ";
				stack.pop_back();
			}
			stack.pop_back();
			break;
		case '+':
		case '-':
			order_stack(i, postfixExpression, stack);
			break;
		case '*':
		case '/':
			order_stack(i, postfixExpression, stack);
			break;
		case '^':
			order_stack(i, postfixExpression, stack);
			break;
		case ' ': break;

		default:
			//error//
			break;
		}
		postfixExpression += " ";
	}

	size_t stackSize = stack.size();
	for (size_t i = 0; i < stackSize; ++i)
	{
		postfixExpression += " ";
		postfixExpression += stack.back();
		stack.pop_back();
	}

	return postfixExpression;
}

double Calculator::Calculate(const string postfixExpression)
{
	vector<double> stack;
	string str = "dumy";

	stringstream temp(postfixExpression);
	while(!temp.eof())
	{
		temp >> str;
		if (simbols.find(str) == string::npos)
		{
			double dtemp;
			stringstream(str) >> dtemp;
			stack.push_back(dtemp);
		}
		else if (simbols_single.find(str) == string::npos)
		{

		}
		else
		{//���� ������
			double d1, d2;
			d2 = stack.back();
			stack.pop_back();
			d1 = stack.back();
			stack.pop_back();
			switch (simbols[simbols.find(str)])
			{
			case '+':
				stack.push_back(d1 + d2); break;
			case '-':
				stack.push_back(d1 - d2); break;
			case '*':
				stack.push_back(d1 * d2); break;
			case '/':
				stack.push_back(d1 / d2); break;
			case '^':
				stack.push_back(powf(d1, d2)); break;
			}
		}
	}

	return stack.back();
}