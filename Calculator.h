#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <vector>
#include <hash_map>
using namespace std;

class Calculator {
private:
	hash_map<string, char> func_map;
	//const string simbols = "(+-*/)^ ";
	const string simbols = "(+-*/)^ ";

public:
	Calculator();
	~Calculator();

public:
	string GetPostFix(const string infixExpression);
	double Calculate(const string postfixExpression);
};
#endif