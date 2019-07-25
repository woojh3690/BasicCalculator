#include <iostream>
#include <string>
#include "Mapper.h"
#include "Calculator.h"
#include <time.h>
using namespace std;

void my();
float adata[8] = { 55.330000, 2.98926, 1.720000, 0.000000, 54.000000, 0.000000, 1.662190, 0.000000 };

int main(int argc, char* argv[])
{
	double start = clock();
	for (int i = 0; i < 10000; i++)
		my();
	double taketime = clock() - start;
	printf("걸린시간 %f\n", taketime);

	printf("---중간 완료---\n");

	start = clock();
	for (int i = 0; i < 10000; i++)
		float temp = adata[0] * adata[1] + adata[2] * adata[3] + adata[4] * adata[5] + adata[6] * adata[7];
	taketime = clock() - start;
	printf("걸린시간 %f\n", taketime);

	
	return 0;
}

void my()
{
	string formula = "x1*a1+x2*a2+x3*a3+x4*a4"; // 계산할 수식
	//cout << "계산할 수식 : " << formula << endl;

	// 채워 넣을 파라미터
	string params[][2] = {
		{"x1", "55.330000"},
		{"a1", "2.98926"},
		{"x2", "1.720000"},
		{"a2", "0.000000"},
		{"x3", "54.000000"},
		{"a3", "0.000000"},
		{"x4", "1.662190"},
		{"a4", "0.000000 "} };

	string infixExpression;
	/*double start = clock();
	for (int i = 0; i < 1; i++)
	{*/
		Mapper mapper = Mapper();
		infixExpression = mapper.Mapping(formula, params);
	/*}
	double taketime = clock() - start;
	printf("mapper 걸린시간 %f\n", taketime);*/

	
	//cout << "파라미터를 채워 넣은 수식 : " << infixExpression << endl;

	//infixExpression = 

	string postfixExpression;
	Calculator* cal = new Calculator();

	/*start = clock();
	for (int i = 0; i < 1; i++)
	{*/
		postfixExpression = cal->GetPostFix(infixExpression);
	/*}
	taketime = clock() - start;
	printf("후위 표기법 변환 걸린시간 %f\n", taketime);*/
	
	//cout << "후위 표기법 변환: " << postfixExpression << endl;
	
	//postfixExpression = "55.330000  -2.98926 *  1.720000  0.000000 * +  54.000000  0.000000 * +  1.662190  0.000000   * +";
	/*start = clock();
	for (int i = 0; i < 1; i++)*/
		double result = cal->Calculate(postfixExpression);
	/*taketime = clock() - start;
	printf("계산 걸린시간 %f\n", taketime);*/
 	//cout << "계산 결과 : " << result << endl;
}