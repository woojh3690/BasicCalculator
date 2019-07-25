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
	printf("�ɸ��ð� %f\n", taketime);

	printf("---�߰� �Ϸ�---\n");

	start = clock();
	for (int i = 0; i < 10000; i++)
		float temp = adata[0] * adata[1] + adata[2] * adata[3] + adata[4] * adata[5] + adata[6] * adata[7];
	taketime = clock() - start;
	printf("�ɸ��ð� %f\n", taketime);

	
	return 0;
}

void my()
{
	string formula = "x1*a1+x2*a2+x3*a3+x4*a4"; // ����� ����
	//cout << "����� ���� : " << formula << endl;

	// ä�� ���� �Ķ����
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
	printf("mapper �ɸ��ð� %f\n", taketime);*/

	
	//cout << "�Ķ���͸� ä�� ���� ���� : " << infixExpression << endl;

	//infixExpression = 

	string postfixExpression;
	Calculator* cal = new Calculator();

	/*start = clock();
	for (int i = 0; i < 1; i++)
	{*/
		postfixExpression = cal->GetPostFix(infixExpression);
	/*}
	taketime = clock() - start;
	printf("���� ǥ��� ��ȯ �ɸ��ð� %f\n", taketime);*/
	
	//cout << "���� ǥ��� ��ȯ: " << postfixExpression << endl;
	
	//postfixExpression = "55.330000  -2.98926 *  1.720000  0.000000 * +  54.000000  0.000000 * +  1.662190  0.000000   * +";
	/*start = clock();
	for (int i = 0; i < 1; i++)*/
		double result = cal->Calculate(postfixExpression);
	/*taketime = clock() - start;
	printf("��� �ɸ��ð� %f\n", taketime);*/
 	//cout << "��� ��� : " << result << endl;
}