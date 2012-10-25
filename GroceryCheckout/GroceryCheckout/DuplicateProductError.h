
#include <stdexcept>

using namespace std;

class DuplicateProductError : public runtime_error
{
public:
	//would like to add custom message output by having error take string in and pass into runtime_error
	DuplicateProductError() : runtime_error("Duplicate product number in inventory"){}
	//DuplicateProductError(string var) : runtime_error("Duplicate product number " + var + " in inventory"){}
};