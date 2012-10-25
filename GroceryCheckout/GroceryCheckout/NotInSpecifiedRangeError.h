
#include <stdexcept>

using namespace std;

class NotInSpecifiedRangeError : public runtime_error
{
public:
	NotInSpecifiedRangeError() : runtime_error("Quantity not in specified range"){}
};