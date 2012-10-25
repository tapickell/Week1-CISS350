#pragma once
class order
{
public:
	order(void);
	~order(void);

	void addToOrder(product);
	std::vector<std::string> getReceipt();

private:
	std::vector<product> products;
	float sub;
	float tax;
	float total;
};

