#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <vector>
#include <map>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <sstream>

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
	string GetPostFix(string& infixExpression); // ���� ǥ����� ���� ǥ������� ��ȯ
	double Calculate(string& postfixExpression); // ���� ǥ��� ���
	void ReplaceAll(std::string& str, const std::string& from, const std::string& to);

private:
	void compare(string::iterator i, string &postfixExpression, vector<char> &stack);
	void preprocessing(string &infixExpression);
	double getRadian(int _num);
};

#endif