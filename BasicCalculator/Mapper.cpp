#include "Mapper.h"
#include "Calculator.h"
#include <time.h>

Mapper::Mapper()
{
}

Mapper::~Mapper()
{
}

string Mapper::Mapping(string formula,  map<string, string> params)
{
	Calculator cal = Calculator();
	map<string, string>::iterator end = params.end();
	
	for (map<string, string>::iterator it = params.begin(); it != end; it++)
	{
		cal.ReplaceAll(formula, it->first, it->second);
	}

	return formula;
}