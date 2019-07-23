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
	//기본 연산자 우선순위 초기화
	priority_map.insert(map<char, int>::value_type('(', 0));
	priority_map.insert(map<char, int>::value_type(')', 0));
	priority_map.insert(map<char, int>::value_type('+', 1));
	priority_map.insert(map<char, int>::value_type('-', 1));
	priority_map.insert(map<char, int>::value_type('*', 2));
	priority_map.insert(map<char, int>::value_type('/', 2));                                                                               
	priority_map.insert(map<char, int>::value_type('^', 3));

	// 커스텀 함수 초기화
	func_map.insert(map<string, char>::value_type("log", 'l'));

	// 커스텀 함수 우선순위 설정
	for (map<string, char>::iterator it = func_map.begin(); it != func_map.end(); ++it) {
		char func_value = func_map[it->first];
		priority_map.insert(map<char, int>::value_type(func_value, 3)); // 우선순위 설정
		simbols_single += func_value; // 단항연산자 추가
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
		// 연산자 아닐경우에 패스
		if (simbols.find(*i) == string::npos)
		{
			postfixExpression += *i;
			continue;
		}

		// 연산자 처리
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
		{//이항 연산자
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