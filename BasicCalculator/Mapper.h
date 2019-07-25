#include <string>
#include <map>
#include "Calculator.h"
using namespace std;

class Mapper
{
private:
	Calculator cal = Calculator();
	int end;
public:
	Mapper();
	~Mapper();

public:
	string Mapping(string formula, string params[][2]);
};