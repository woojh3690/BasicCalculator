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

	Calculator() {
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
	};
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