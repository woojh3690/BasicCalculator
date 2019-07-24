#include <string>
#include <map>
using namespace std;

class Mapper
{
public:
	Mapper();
	~Mapper();

public:
	string Mapping(string formula, map<string, string> params);
};