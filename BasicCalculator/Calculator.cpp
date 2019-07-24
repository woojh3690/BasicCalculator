#include "Calculator.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>

Calculator::Calculator()
{
	//�⺻ ������ �켱���� �ʱ�ȭ
	priority_map.insert(pair<char, int>('+', 1));
	priority_map.insert(pair<char, int>('-', 1));
	priority_map.insert(pair<char, int>('*', 2));
	priority_map.insert(pair<char, int>('/', 2));                                                                               
	priority_map.insert(pair<char, int>('^', 3));

	// Ŀ���� �Լ� �ʱ�ȭ
	func_map.insert(pair<string, char>("log", 'l'));
	func_map.insert(pair<string, char>("sin", 's'));
	func_map.insert(pair<string, char>("cos", 'c'));
	func_map.insert(pair<string, char>("tan", 't'));

	// Ŀ���� �Լ� �켱���� �ʱ�ȭ (����(^)�̶� ���� 3���� ��� �ʱ�ȭ ��)
	for (map<string, char>::iterator it = func_map.begin(); it != func_map.end(); ++it) {
		char func_value = func_map[it->first];
		priority_map.insert(map<char, int>::value_type(func_value, 3)); // �켱���� ����
		simbols_single += func_value; // ���׿����� �߰�
	}
}

Calculator::~Calculator()
{
}

// ���� ǥ����� ���� ǥ������� ��ȯ
string Calculator::GetPostFix(string infixExpression)
{
	preprocessing(infixExpression); //��ó��

	string postfixExpression;
	string::iterator i = infixExpression.begin();
	vector<char> stack;

	for (; i != infixExpression.end(); ++i)
	{
		// ������ �ƴҰ�� �н�
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

	// ���� ������ ó��
	size_t stackSize = stack.size();
	for (size_t i = 0; i < stackSize; ++i)
	{
		postfixExpression += " ";
		postfixExpression += stack.back();
		stack.pop_back();
	}

	return postfixExpression;
}

// ���� ǥ��� ���
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
			{// ���� ������ ���
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
			{ // ����, ���� �����ڵ� �ƴ� ����� ��� stack�� push
				double dtemp;
				stringstream(str) >> dtemp;
				stack.push_back(dtemp);
			}
		}
		else
		{// ���� ������ ���
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

// ��ó��
void Calculator::preprocessing(string& infixExpression)
{
	//Ŀ���� �Լ��� ���� �ϳ��� ����
	for (map<string, char>::iterator it = func_map.begin(); it != func_map.end(); ++it) {
		string from = it->first;
		string to = string(1, it->second);
		infixExpression = ReplaceAll(infixExpression, from, to);
	}

	//Ŀ���� �Լ� ��ġ ����
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