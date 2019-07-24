#include <iostream>
#include <string>
#include "Mapper.h"
#include "Calculator.h"
using namespace std;

int main(int argc, char* argv[])
{
	string formula = "a*x^b+a"; // 계산할 수식
	cout << "계산할 수식 : " << formula << endl;

	// 채워 넣을 파라미터
	map<string, string> params;
	params.insert(pair<string, string>("x", "3"));
	params.insert(pair<string, string>("a", "4"));
	params.insert(pair<string, string>("b", "2"));

	Mapper mapper = Mapper();
	string infixExpression = mapper.Mapping(formula, params);
	cout << "파라미터를 채워 넣은 수식 : " << infixExpression << endl;

	Calculator* cal = new Calculator();
	string postfixExpression = cal->GetPostFix(infixExpression);
	cout << "후위 표기법 변환: " << postfixExpression << endl;
	
	double result = cal->Calculate(postfixExpression);
 	cout << "계산 결과 : " << result << endl;

	
	return 0;
}