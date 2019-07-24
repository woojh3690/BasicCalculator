#include "Calculator.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>

Calculator::Calculator()
{
	//기본 연산자 우선순위 초기화
	priority_map.insert(pair<char, int>('+', 1));
	priority_map.insert(pair<char, int>('-', 1));
	priority_map.insert(pair<char, int>('*', 2));
	priority_map.insert(pair<char, int>('/', 2));                                                                               
	priority_map.insert(pair<char, int>('^', 3));

	// 커스텀 함수 초기화
	func_map.insert(pair<string, char>("log", 'l'));
	func_map.insert(pair<string, char>("sin", 's'));
	func_map.insert(pair<string, char>("cos", 'c'));
	func_map.insert(pair<string, char>("tan", 't'));

	// 커스텀 함수 우선순위 초기화 (제곱(^)이랑 같은 3으로 모두 초기화 됨)
	for (map<string, char>::iterator it = func_map.begin(); it != func_map.end(); ++it) {
		char func_value = func_map[it->first];
		priority_map.insert(map<char, int>::value_type(func_value, 3)); // 우선순위 설정
		simbols_single += func_value; // 단항연산자 추가
	}
}

Calculator::~Calculator()
{
}

// 중위 표기법을 후위 표기법으로 변환
string Calculator::GetPostFix(string infixExpression)
{
	preprocessing(infixExpression); //전처리

	string postfixExpression;
	string::iterator i = infixExpression.begin();
	vector<char> stack;

	for (; i != infixExpression.end(); ++i)
	{
		// 연산자 아닐경우 패스
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
			compare(i, postfixExpression, stack); break;
		case '*':
		case '/':
			compare(i, postfixExpression, stack); break;
		case '^':
		case 'l':
		case 's':
		case 'c':
		case 't':
			compare(i, postfixExpression, stack); break;
		case ' ': 
			break;
		default:
			//error//
			break;
		}
		postfixExpression += " ";
	}

	// 남은 연산자 처리
	size_t stackSize = stack.size();
	for (size_t i = 0; i < stackSize; ++i)
	{
		postfixExpression += " ";
		postfixExpression += stack.back();
		stack.pop_back();
	}

	return postfixExpression;
}

// 후위 표기법 계산
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
			if (simbols_single.find(str) != string::npos)
			{// 다항 연산자 계산
				double d1;
				d1 = stack.back();
				stack.pop_back();
				switch (simbols_single[simbols_single.find(str)])
				{
				case 'l': stack.push_back(log10(d1)); break;
				case 's': stack.push_back(sin(getRadian(d1))); break;
				case 'c': stack.push_back(cos(getRadian(d1))); break;
				case 't': stack.push_back(tan(getRadian(d1))); break;
				}

			}
			else
			{ // 이항, 다항 연산자도 아닌 상수인 경우 stack에 push
				double dtemp;
				stringstream(str) >> dtemp;
				stack.push_back(dtemp);
			}
		}
		else
		{// 이항 연산자 계산
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

// 전처리
void Calculator::preprocessing(string& infixExpression)
{
	//커스텀 함수를 문자 하나로 변경
	for (map<string, char>::iterator it = func_map.begin(); it != func_map.end(); ++it) {
		string from = it->first;
		string to = string(1, it->second);
		infixExpression = ReplaceAll(infixExpression, from, to);
	}

	//커스텀 함수 위치 변경
	vector<pair<char, int>> stack;
	int count = 0;
	for (int i = 0; i != infixExpression.length(); ++i)
	{
		if (infixExpression[i] == '(')
		{
			count++;
		}
		else if (infixExpression[i] == ')')
		{
			count--;
		}

		if (simbols_single.find(infixExpression[i]) != string::npos)
		{
			char item = infixExpression.substr(i)[0];
			infixExpression.erase(i, 1);
			stack.push_back(pair<char, int>(item, count));

			count++;
		}
		else if (stack.size() != 0 && ')' == infixExpression[i] && stack.back().second == count)
		{
			infixExpression.insert(i + 1, 1, stack.back().first);
			stack.pop_back();
			i++;
		}
	}
}

void Calculator::compare(string::iterator i, string& postfixExpression, vector<char>& stack)
{
	while (stack.size() != 0 && priority_map[stack.back()] >= priority_map[*i])
	{
		postfixExpression += stack.back();
		postfixExpression += " ";
		stack.pop_back();
	}
	stack.push_back(*i);
}

string Calculator::ReplaceAll(std::string str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}

double Calculator::getRadian(int _num)
{
	return _num * (M_PI / 180);
}