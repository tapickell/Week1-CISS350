#pragma once
class order
{
public:
	order(void);
	~order(void);

	void addToOrder(product);
	std::vector<std::string> getReceipt();

private:
	//std::vector<product> products;  //caused errors vector out of bounds. 
	float sub;
	float tax;
	float total;
};

