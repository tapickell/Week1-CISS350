
#include <stdexcept>

using namespace std;

class NotInInventoryError : public runtime_error
{
public:
	NotInInventoryError() : runtime_error("Product number not in inventory file"){}
};