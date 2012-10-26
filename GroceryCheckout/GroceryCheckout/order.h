#pragma once
class order
{
public:
	order(void);
	~order(void);

	void addToOrder(product);
	std::vector<std::string> getReceiptHeader();
	std::vector<std::string> getReceiptFooter();

private:
	float sub;
	float taxes;
	float total;
	double tax;
	std::string check;
	static int orderNumber;
};

