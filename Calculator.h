#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <vector>
#include <map>
using namespace std;

class Calculator {
private:
	map<string, char> func_map; // Ŀ���� �Լ� ���� ����
	map<char, int> priority_map; // �켱���� ���� ����
	string simbols = "(+-*/)^ "; // ���׿����� ��ȣ �˻� ����
	string simbols_single; // ���׿����� ��ȣ �˻� ����
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