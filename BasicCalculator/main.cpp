#include <iostream>
#include <string>
#include "Mapper.h"
#include "Calculator.h"
using namespace std;

int main(int argc, char* argv[])
{
	string formula = "a*x^b+a"; // ����� ����
	cout << "����� ���� : " << formula << endl;

	// ä�� ���� �Ķ����
	map<string, string> params;
	params.insert(pair<string, string>("x", "3"));
	params.insert(pair<string, string>("a", "4"));
	params.insert(pair<string, string>("b", "2"));

	Mapper mapper = Mapper();
	string infixExpression = mapper.Mapping(formula, params);
	cout << "�Ķ���͸� ä�� ���� ���� : " << infixExpression << endl;

	Calculator* cal = new Calculator();
	string postfixExpression = cal->GetPostFix(infixExpression);
	cout << "���� ǥ��� ��ȯ: " << postfixExpression << endl;
	
	double result = cal->Calculate(postfixExpression);
 	cout << "��� ��� : " << result << endl;

	
	return 0;
}