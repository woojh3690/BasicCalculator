#include "Calculator.h"
#include <math.h>
#include <sstream>

//void temp()
//{
//	while (stack.size() != 0 && (stack.back() == '*' || stack.back() == '/'))
//	{
//		postfixExpression += stack.back();
//		postfixExpression += " ";
//		stack.pop_back();
//	}
//	stack.push_back(*i);
//}

Calculator::Calculator()
{
	func_map.insert(hash_map<string, char>::value_type("log", 'l'));
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
			while(stack.size() != 0 && stack.back() != '(')
			{
				postfixExpression += stack.back();
				postfixExpression += " ";
				stack.pop_back();
			}
			stack.push_back(*i);
			break;
		case '*':
		case '/':
			
			break;
		case '^':

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
		else
		{
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