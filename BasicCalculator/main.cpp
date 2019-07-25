#include <iostream>
#include <string>
#include "Mapper.h"
#include "Calculator.h"
#include <time.h>
using namespace std;

void my();

int main(int argc, char* argv[])
{
	double start = clock();
	for (int i = 0; i < 1; i++)
		my();
	double taketime = clock() - start;
	printf("걸린시간 %f\n", taketime);

	start = clock();
	for (int i = 0; i < 1000; i++)
		float temp = 55.330000 * 2.98926 + 1.720000 * 0.000000 + 54.000000 * 0.000000 + 1.662190 * 0.000000;
	taketime = clock() - start;
	printf("걸린시간 %f\n", taketime);

	
	return 0;
}

void my()
{
	string formula = "x1*a1+x2*a2+x3*a3+x4*a4"; // 계산할 수식
	//cout << "계산할 수식 : " << formula << endl;

	// 채워 넣을 파라미터
	map<string, string> params;
	params.insert(pair<string, string>("x1", "55.330000"));
	params.insert(pair<string, string>("a1", "2.98926"));
	params.insert(pair<string, string>("x2", "1.720000"));
	params.insert(pair<string, string>("a2", "0.000000"));
	params.insert(pair<string, string>("x3", "54.000000"));
	params.insert(pair<string, string>("a3", "0.000000"));
	params.insert(pair<string, string>("x4", "1.662190"));
	params.insert(pair<string, string>("a4", "0.000000 "));

	string infixExpression;
	double start = clock();
	for (int i = 0; i < 1000; i++)
	{
		Mapper mapper = Mapper();
		infixExpression = mapper.Mapping(formula, params);
	}
	double taketime = clock() - start;
	printf("mapper 걸린시간 %f\n", taketime);

	
	//cout << "파라미터를 채워 넣은 수식 : " << infixExpression << endl;

	//infixExpression = 

	string postfixExpression;
	Calculator* cal = new Calculator();

	start = clock();
	for (int i = 0; i < 1; i++)
	{
		postfixExpression = cal->GetPostFix(infixExpression);
	}
	taketime = clock() - start;
	printf("후위 표기법 변환 걸린시간 %f\n", taketime);
	
	//cout << "후위 표기법 변환: " << postfixExpression << endl;
	
	//postfixExpression = "55.330000  -2.98926 *  1.720000  0.000000 * +  54.000000  0.000000 * +  1.662190  0.000000   * +";
	start = clock();
	for (int i = 0; i < 1000; i++)
		double result = cal->Calculate(postfixExpression);
	taketime = clock() - start;
	printf("계산 걸린시간 %f\n", taketime);
 	//cout << "계산 결과 : " << result << endl;
}