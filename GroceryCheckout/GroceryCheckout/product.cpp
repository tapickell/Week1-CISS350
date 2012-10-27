#include "stdafx.h"
#include "product.h"


product::product(void)
{
}

product::product(std::string val0, std::string val1, std::string val2, std::string val3, int val4)
{
	setProdNum(atoi(val0.c_str()));
	setDescrip(val1);
	setPrice(atof(val2.c_str()));
	setTax(val3[0]);
	setQuantity(val4);
}

product::~product(void)
{
}

// setters 
void product::setProdNum(int num)
{
	prodNum = num;
}
void product::setDescrip(std::string desc)
{
	descrip = desc;
}
void product::setPrice(float amount)
{
	price = amount;
}
void product::setTax(char tax)
{
	taxable = tax;
}
void product::setQuantity(int times)
{
	quantity = times;
}

// getters
int product::getProdNum()
{
	return prodNum;
}
std::string product::getDescrip()
{
	return descrip;
}
float product::getTotalPrice()
{
	float totalPrice = price * quantity;
	return totalPrice;
}
float product::getPrice()
{
	return price;
}
char product::getTax()
{
	return taxable;
}
int product::getQuantity()
{
	return quantity;
}

std::string product::toString()
{
	//create string for product that will display on receipt
	std::string stringOut;
	stringOut = stringOut.append(getDescrip());
	stringOut = stringOut.append(" ");
	std::stringstream is;
	is << getQuantity();
	stringOut = stringOut.append(is.str());
	stringOut = stringOut.append(" @ ");
	std::stringstream fs;
	fs << getPrice();
	stringOut = stringOut.append(fs.str());
	stringOut = stringOut.append(" ");
	std::stringstream tfs;
	tfs << getTotalPrice();
	stringOut = stringOut.append(tfs.str());
	std::string check = "T";
	if (getTax() == check[0])
	{
		stringOut = stringOut.append(" TX ");
	}
	return stringOut;
}