#pragma once
class product
{
public:
	product(void);
	product(std::string, std::string, std::string, std::string, int);
	~product(void);

	// setters 
	void setProdNum(int);
	void setDescrip(std::string);
	void setPrice(float);
	void setTax(char);
	void setQuantity(int);

	// getters
	int getProdNum();
	std::string getDescrip();
	float getPrice();
	char getTax();
	int getQuantity();


private:
	int prodNum;
	std::string descrip;
	float price;
	char taxable;
	int quantity;

};

