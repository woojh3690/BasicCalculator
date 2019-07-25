#include <string>
#include "Calculator.h"
using namespace std;

class Mapper
{
private:
	Calculator cal = Calculator();
	int end;
	string formula;
public:
	Mapper(string formula);
	~Mapper();

public:
	string Mapping(string params[][2]);
};