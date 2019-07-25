#include "Mapper.h"

Mapper::Mapper(string formula)
{
	this->formula = formula;
}

Mapper::~Mapper()
{
}

string Mapper::Mapping(string params[][2])
{
	int end = sizeof(params) / sizeof(params[0]);
	for (int i = 0; i < end; i++)
	{
		cal.ReplaceAll(formula, params[i][0], params[i][1]);
	}
	return formula;
}