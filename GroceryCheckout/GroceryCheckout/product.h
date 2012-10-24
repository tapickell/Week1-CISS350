#pragma once
class product
{
public:
	product(void);
	~product(void);

	// setters 
	void setProdNum(int);
	void setDescrip(std::string);
	void setPrice(float);
	void setTax(char);

	// getters
	int getProdNum();
	std::string getDescrip();
	float getPrice();
	char getTax();


private:
	int prodNum;
	std::string descrip;
	float price;
	char taxable;

};

