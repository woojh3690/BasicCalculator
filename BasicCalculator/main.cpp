#include <iostream>
#include <string>
#include "Calculator.h"
using namespace std;

double my();
double adata[8] = { 55.330000, -2.98926, 1.720000, 0.000000, 54.000000, 0.000000, 1.662190, 0.000000 };

string formula = "x1*a1+x2*a2+x3*a3+x4*a4";
Calculator* cal = new Calculator(formula, 8);
string params[][2] = {
		{"x1", "55.330000"},
		{"a1", "-2.98926"},
		{"x2", "1.720000"},
		{"a2", "0.000000"},
		{"x3", "54.000000"},
		{"a3", "0.000000"},
		{"x4", "1.662190"},
		{"a4", "0.000000 "} };

int main(int argc, char* argv[])
{
	double nativeResult;
	double start = clock();
	for (int i = 0; i < 10000; i++)
		nativeResult = adata[0] * adata[1] + adata[2] * adata[3] + adata[4] * adata[5] + adata[6] * adata[7];
	double taketime = clock() - start;
	printf("하드코딩 수식 계산 걸린시간 %lf\n", taketime);

	start = clock();
	for (int i = 0; i < 10000; i++)
		cal->start(params);
	taketime = clock() - start;
	printf("수식 파서 걸린시간 %lf\n", taketime);

	printf("my 결과 : %lf\n", cal->start(params));
	printf("my 결과 : %lf\n", nativeResult);
	return 0;
}