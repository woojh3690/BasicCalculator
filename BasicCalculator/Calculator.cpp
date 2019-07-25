#include "Calculator.h"

Calculator::~Calculator()
{
}

double Calculator::start(string params[][2])
{
	/*string temp;
	double start = clock();
	for (int i = 0; i < 1000; i++)
	Mapping(params);
	double taketime = clock() - start;
	printf("Mapping 걸린시간 %lf\n", taketime);

	temp  = "x1*a1+x2*a2+x3*a3+x4*a4";

	 start = clock();
	for (int i = 0; i < 1000; i++)
	GetPostFix(temp);
	 taketime = clock() - start;
	printf("GetPostFix 걸린시간 %lf\n", taketime);

	temp = "x1  a1 *  x2  a2 * +  x3  a3 * +  x4  a4 * +";
	 start = clock();
	for (int i = 0; i < 1000; i++)
		Calculate(temp);
	 taketime = clock() - start;
	printf("Calculate 걸린시간 %lf\n", taketime);

	return 0.231;*/

	string temp = Mapping(params);
	temp = GetPostFix(temp);
	return Calculate(temp);

}

// 중위 표기법을 후위 표기법으로 변환
string Calculator::GetPostFix(string& infixExpression)
{
	preprocessing(infixExpression); //전처리
	string postfixExpression;
	vector<char> stack;
	string::iterator i = infixExpression.begin();
	string::iterator end = infixExpression.end();

	for (; i != end; ++i)
	{
		// 연산자 아닐경우 패스
		if (simbols.find(*i) == string::npos || (*i == '-' && simbols.find(*i + 1) == string::npos))
		{
			postfixExpression += *i;
			continue;
		}

		// 연산자 처리
		postfixExpression += " ";
		switch (*i)
		{
		case '(': stack.push_back('('); break;
		case ')':
			while (stack.back() != '(')
			{
				postfixExpression += stack.back();
				postfixExpression += " ";
				stack.pop_back();
			}
			stack.pop_back();
			break;
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
		case 'l':
		case 's':
		case 'c':
		case 't':
			compare(i, postfixExpression, stack); break;
		case ' ':
			break;
		default:
			//error//
			break;
		}
		postfixExpression += " ";
	}

	// 남은 연산자 처리
	size_t stackSize = stack.size();
	for (size_t i = 0; i < stackSize; ++i)
	{
		postfixExpression += " ";
		postfixExpression += stack.back();
		stack.pop_back();
	}

	return postfixExpression;
}

// 후위 표기법 계산
double Calculator::Calculate(string& postfixExpression)
{
	vector<double> stack;
	string str = "dumy";
	double d1, d2;
	size_t find;

	stringstream temp(postfixExpression);
	while(!temp.eof())
	{
		temp >> str;
		find = simbols.find(str);
		if (find == string::npos)
		{
			if (simbols_single.find(str) != string::npos)
			{// 단항 연산자 계산
				d1 = stack.back();
				stack.pop_back();
				switch (simbols_single[simbols_single.find(str)])
				{
					case 'l': stack.push_back(log10(d1)); break;
					case 's': stack.push_back(sin(getRadian(d1))); break;
					case 'c': stack.push_back(cos(getRadian(d1))); break;
					case 't': stack.push_back(tan(getRadian(d1))); break;
				}

			}
			else
			{ // 이항, 단항 연산자도 아닌 상수인 경우 stack에 push
				double dtemp;
				stringstream(str) >> dtemp;
				stack.push_back(dtemp);
			}
		}
		else
		{// 이항 연산자 계산
			d2 = stack.back();
			stack.pop_back();
			d1 = stack.back();
			stack.pop_back();
			switch (simbols[find])
			{
			case '+':
				stack.push_back(d1 + d2); break;
			case '-':
				stack.push_back(d1 - d2); break;
			case '*':
				stack.push_back(d1 * d2); break;
			case '/':
				stack.push_back(d1 / d2); break;
			case '^':
				stack.push_back(powf(d1, d2)); break;
			}
		}
	}

	return stack.back();
}

// 전처리
void Calculator::preprocessing(string& infixExpression)
{
	//커스텀 함수를 문자 하나로 변경
	for (int i = 0; i < FUNC_SIZE; i++) {
		ReplaceAll(infixExpression, func_map[i][0], func_map[i][1]);
	}

	//커스텀 함수 위치 변경
	vector<pair<char, int>> stack;
	int count = 0;
	char cur_index;
	for (int i = 0; i != infixExpression.length(); ++i)
	{
		cur_index = infixExpression[i];
		if (cur_index == '(')
		{
			count++;
		}
		else if (cur_index == ')')
		{
			count--;
		}

		if (simbols_single.find(cur_index) != string::npos)
		{
			infixExpression.erase(i, 1);
			stack.push_back(pair<char, int>(cur_index, count));
			count++;
		}
		else if (')' == cur_index && stack.size() != 0 && stack.back().second == count)
		{
			infixExpression.insert(i + 1, 1, stack.back().first);
			stack.pop_back();
			i++;
		}
	}
}

void Calculator::compare(string::iterator i, string& postfixExpression, vector<char>& stack)
{
	while (stack.size() != 0 && priority_map[stack.back()] >= priority_map[*i])
	{
		postfixExpression += stack.back();
		postfixExpression += " ";
		stack.pop_back();
	}
	stack.push_back(*i);
}

void Calculator::ReplaceAll(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
}

double Calculator::getRadian(int _num)
{
	return _num * (M_PI / 180);
}

string Calculator::Mapping(string params[][2])
{
	for (int i = 0; i < size; i++)
	{
		ReplaceAll(formula, params[i][0], params[i][1]);
	}
	return formula;
}