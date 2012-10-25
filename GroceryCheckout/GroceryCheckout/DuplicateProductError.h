
#include <stdexcept>

using namespace std;

class DuplicateProductError : public runtime_error
{
public:
	DuplicateProductError() : runtime_error("Duplicate product number in inventory"){}
};