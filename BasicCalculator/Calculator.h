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
	map<string, char> func_map; // 커스텀 함수 설정 변수
	map<char, int> priority_map; // 우선순위 설정 변수
	string simbols = "(+-*/)^ "; // 다항연산자 기호 검사 변수
	string simbols_single; // 단항연산자 기호 검사 변수
	//const string simbols;

public:

	Calculator() {
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
	};
	~Calculator();

public:
	string GetPostFix(string& infixExpression); // 중위 표기법을 후위 표기법으로 변환
	double Calculate(string& postfixExpression); // 후위 표기법 계산
	void ReplaceAll(std::string& str, const std::string& from, const std::string& to);

private:
	void compare(string::iterator i, string &postfixExpression, vector<char> &stack);
	void preprocessing(string &infixExpression);
	double getRadian(int _num);
};

#endif