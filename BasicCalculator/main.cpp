#include <iostream>
#include <string>
#include "Calculator.h"
using namespace std;

double my();
double adata[8] = { 55.330000, 2.98926, 1.720000, 0.000000, 54.000000, 0.000000, 1.662190, 0.000000 };

int main(int argc, char* argv[])
{
	double start = clock();
	for (int i = 0; i < 10000; i++)
		my();
	double taketime = clock() - start;
	printf("걸린시간 %lf\n", taketime);

	printf("---중간 완료---\n");

	double nativeResult;
	start = clock();
	for (int i = 0; i < 10000; i++)
		nativeResult = adata[0] * adata[1] + adata[2] * adata[3] + adata[4] * adata[5] + adata[6] * adata[7];
	taketime = clock() - start;
	printf("걸린시간 %lf\n", taketime);

	printf("my 결과 : %lf\n", my());
	printf("my 결과 : %lf\n", nativeResult);
	return 0;
}

string formula = "x1*a1+x2*a2+x3*a3+x4*a4";
Calculator* cal = new Calculator(formula, 8);
string params[][2] = {
		{"x1", "55.330000"},
		{"a1", "2.98926"},
		{"x2", "1.720000"},
		{"a2", "0.000000"},
		{"x3", "54.000000"},
		{"a3", "0.000000"},
		{"x4", "1.662190"},
		{"a4", "0.000000 "} };

double my()
{
	return cal->start(params);
}