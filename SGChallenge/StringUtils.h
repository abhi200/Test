#include <string>
#include <sstream>
#include <iomanip>

//STRING TO UINT
static bool StringToUInt(const std::string& s, unsigned int& u)
{
	std::stringstream ss(s);
	return !(ss >> u).fail();
}

//STRING TO INT
static bool StringToInt(const std::string& s, int& i)
{
	std::stringstream ss(s);
	return !(ss >> i).fail();
}


//STRING TO FLOAT
static bool StringToFloat(const std::string& s, float& f)
{
	std::stringstream ss(s);
	return !(ss >> f).fail();
}