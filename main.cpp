#include <iostream>
#include <string>
#include "Calculator.h"
using namespace std;

int main(int argc, char* argv[])
{
	string infixExpression;
	string postfixExpression;

	/*string temp = "atan";

	auto Aauto = temp.find("tan");

	if (Aauto == string::npos)
	{
		cout << "tan ¹ÌÈ®ÀÎ " << endl;
	}
	else {
		cout << Aauto << endl;
	}*/
	
	double result = 0.0;

	cout << "Enter Infix Expression : ";
 	cin >> infixExpression;
 
	Calculator* cal = new Calculator();
 	postfixExpression = cal->GetPostFix(infixExpression);
	cout << "Postfix Expression : " << postfixExpression << "\n";
	
	result = cal->Calculate(postfixExpression);
 	cout << "Result : " << result << "\n";

	
	return 0;
}