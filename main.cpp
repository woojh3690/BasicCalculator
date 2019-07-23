#include <iostream>
#include <string>
#include "Calculator.h"
using namespace std;

int main(void)
{
	string infixExpression;
	string postfixExpression;

	string temp = "atan";

	auto Aauto = temp.find("tan");

	if (Aauto == string::npos)
	{
		cout << "tan ¹ÌÈ®ÀÎ " << endl;
	}
	else {
		cout << Aauto << endl;
	}
	/*
	double result = 0.0;

	cout << "Enter Infix Expression : ";
 	cin >> infixExpression;
 
 	postfixExpression = GetPostFix(infixExpression);
	cout << "Postfix Expression : " << postfixExpression << "\n";
	
	result = Calculate(postfixExpression);
 	cout << "Result : " << result << "\n";

	*/
	return 0;
}