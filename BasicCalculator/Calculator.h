#ifndef CALCULATOR_H
#define CALCULATOR_H

#define _USE_MATH_DEFINES
#define FUNC_SIZE 4
#include <math.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <time.h>

using namespace std;

class Calculator {

private:
	string func_map[FUNC_SIZE][2] = {
		{"log", "l"},
		{"sin", "s"},
		{"cos", "c"},
		{"tan", "t"}
	}; // Ŀ���� �Լ� ���� ����// Ŀ���� �Լ� ���� ����

	map<char, int> priority_map; // �켱���� ���� ����
	string simbols = "(+-*/)^ "; // ���׿����� ��ȣ �˻� ����
	string simbols_single; // ���׿����� ��ȣ �˻� ����
	string formula;
	int size;
	vector<char> stack;

public:
	Calculator(string formula, int size)
	{
		//�⺻ ������ �켱���� �ʱ�ȭ
		priority_map.insert(pair<char, int>('+', 1));
		priority_map.insert(pair<char, int>('-', 1));
		priority_map.insert(pair<char, int>('*', 2));
		priority_map.insert(pair<char, int>('/', 2));
		priority_map.insert(pair<char, int>('^', 3));

		// Ŀ���� �Լ� �켱���� �ʱ�ȭ (����(^)�̶� ���� 3���� ��� �ʱ�ȭ ��)
		for (int i = 0; i < FUNC_SIZE; i++) {
			char value = func_map[i][1][0];
			priority_map.insert(pair<char, int>(value, 3)); // �켱���� ����
			simbols_single += value; // ���׿����� �߰�
		}

		this->formula = preprocessing(formula); //��ó��
		this->size = size;
	};
	~Calculator();

public:
	double start(string params[][2]);

private:
	string GetPostFix(string& infixExpression); // ���� ǥ����� ���� ǥ������� ��ȯ
	double Calculate(string postfixExpression); // ���� ǥ��� ���
	void ReplaceAll(std::string& str, const std::string& from, const std::string& to);
	void compare(string::iterator i, string &postfixExpression, vector<char> &stack);
	string preprocessing(string infixExpression);
	double getRadian(double _num);
};

#endif