#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <vector>
#include <map>
using namespace std;

class Calculator {
private:
	map<string, char> func_map; // 커스텀 함수 설정 변수
	map<char, int> priority_map; // 우선순위 설정 변수
	string simbols = "(+-*/)^ "; // 다항연산자 기호 검사 변수
	string simbols_single; // 단항연산자 기호 검사 변수
	//const string simbols;

public:
	Calculator();
	~Calculator();

public:
	string GetPostFix(const string infixExpression);
	double Calculate(const string postfixExpression);

private:
	void order_stack(string::iterator i, string &postfixExpression, vector<char> &stack);
};

#endif