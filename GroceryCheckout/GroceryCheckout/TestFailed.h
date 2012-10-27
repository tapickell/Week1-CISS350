
#include <stdexcept>

using namespace std;

class TestFailed : public runtime_error
{
public:
	//would like to add custom message output by having error take string in and pass into runtime_error
	TestFailed() : runtime_error("One of the tests failed"){}
	//DuplicateProductError(string var) : runtime_error("Duplicate product number " + var + " in inventory"){}
};