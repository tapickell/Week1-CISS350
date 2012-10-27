#include "stdafx.h"
#include "product.h"
#include "order.h"


int order::orderNumber = 0;

order::order(void)
{
	sub = 0.0;
	taxes = 0.0;
	total = 0.0;
	tax = 0.075;
	check = "T";
	++orderNumber;
}


order::~order(void)
{
	//--orderNumber;
}

void order::addToOrder(product myProd)
{
	sub += myProd.getTotalPrice();
	if (myProd.getTax() == check[0])
	{
		taxes += (myProd.getTotalPrice() * tax); // may need to make sure rounds to 2 decimal places
		//std::cout << "TAXES: " << taxes << std::endl;
	}
}

std::vector<std::string> order::getReceiptHeader()
{
	std::vector<std::string> myVector;
	myVector.push_back("----------------------------");
	//add timestamp to receipt *optional*
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	std::string myTime = ctime(&rawtime);
	myVector.push_back(myTime);
	//add timestamp to receipt *optional*
	std::string cust = "Customer ";
	std::stringstream is;
	is << orderNumber;
	myVector.push_back(cust.append(is.str()));
	return myVector;
}

std::vector<std::string> order::getReceiptFooter()
{
	std::vector<std::string> myVector;
	//subtotal
	std::string subString = "Subtotal ";
	std::stringstream ss;
	ss << sub;
	myVector.push_back(subString.append(ss.str()));
	//tax
	std::string taxString = "Tax ";
	std::stringstream ts;
	ts << taxes;
	myVector.push_back(taxString.append(ts.str()));

	myVector.push_back("-----------");

	//total
	total = sub + taxes;
	std::string totalString = "Total ";
	std::stringstream tts;
	tts << total;
	myVector.push_back(totalString.append(tts.str()));

	return myVector;
}