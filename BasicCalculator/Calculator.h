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
	}; // 커스텀 함수 설정 변수// 커스텀 함수 설정 변수

	map<char, int> priority_map; // 우선순위 설정 변수
	string simbols = "(+-*/)^ "; // 다항연산자 기호 검사 변수
	string simbols_single; // 단항연산자 기호 검사 변수
	string formula;
	int size;
	vector<char> stack;

public:
	Calculator(string formula, int size)
	{
		//기본 연산자 우선순위 초기화
		priority_map.insert(pair<char, int>('+', 1));
		priority_map.insert(pair<char, int>('-', 1));
		priority_map.insert(pair<char, int>('*', 2));
		priority_map.insert(pair<char, int>('/', 2));
		priority_map.insert(pair<char, int>('^', 3));

		// 커스텀 함수 우선순위 초기화 (제곱(^)이랑 같은 3으로 모두 초기화 됨)
		for (int i = 0; i < FUNC_SIZE; i++) {
			char value = func_map[i][1][0];
			priority_map.insert(pair<char, int>(value, 3)); // 우선순위 설정
			simbols_single += value; // 단항연산자 추가
		}

		this->formula = preprocessing(formula); //전처리
		this->size = size;
	};
	~Calculator();

public:
	double start(string params[][2]);

private:
	string GetPostFix(string& infixExpression); // 중위 표기법을 후위 표기법으로 변환
	double Calculate(string postfixExpression); // 후위 표기법 계산
	void ReplaceAll(std::string& str, const std::string& from, const std::string& to);
	void compare(string::iterator i, string &postfixExpression, vector<char> &stack);
	string preprocessing(string infixExpression);
	double getRadian(double _num);
};

#endif