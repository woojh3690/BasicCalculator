#include "Mapper.h"
#include "Calculator.h"

Mapper::Mapper()
{
}

Mapper::~Mapper()
{
}

string Mapper::Mapping(string formula,  map<string, string> params)
{
	for (map<string, string>::iterator it = params.begin(); it != params.end(); it++)
	{
		Calculator cal = Calculator();
		formula = cal.ReplaceAll(formula, it->first, it->second);
	}

	return formula;
}