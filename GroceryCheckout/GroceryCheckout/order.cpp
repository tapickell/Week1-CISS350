#include "stdafx.h"
#include "product.h"
#include "order.h"


order::order(void)
{
	sub = 0.0;
	tax = 0.0;
	total = 0.0;
}


order::~order(void)
{
}

void order::addToOrder(product)
{

}

std::vector<std::string> order::getReceipt()
{
	std::vector<std::string> myVector;
	return myVector;
}