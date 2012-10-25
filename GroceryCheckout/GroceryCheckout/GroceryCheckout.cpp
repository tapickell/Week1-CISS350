// GroceryCheckout.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fileHandler.h"
#include "product.h"
#include "order.h"
#include "DuplicateProductError.h"
#include "NotInInventoryError.h"
#include "NotInSpecifiedRangeError.h"

using namespace std;

//declarations
product stringsToProduct(string stringsIn, int times);

int _tmain(int argc, _TCHAR* argv[])
{
	//**get file handlers**
	fileHandler inventoryIn("Invent.dat");
	fileHandler receiptOut("Receipts.out");
	receiptOut.getFile(); //create new reciept file

	//**get inventory**
	//take in inventory from file and store into vector for usage
	vector<string> inventToBeProc = inventoryIn.getFile();
	vector<string> inventOut;
	vector<string> inventClean;

	//**process inventory**
	//iterate through inventory from file
	for (size_t i = 0; i < inventToBeProc.size(); i++)
	{
		//check for duplication of items
		for (size_t j = 0; j < inventClean.size(); j++)
		{
			//compare product number from file to product number stored in clean inventory
			if (inventClean[j].compare(0, 5, inventToBeProc[i], 0, 5) != 0)
			{
				//push clean items onto stores
				inventClean.push_back(inventToBeProc[i]);
				inventOut.push_back(inventToBeProc[i]);
			} else {
				//if file contains duplication dont add second entry to storage
				//write error out to reciept
				inventOut.push_back("*** duplicate item removed ***");
				//through exception, would like to pass product number to error class
				throw DuplicateProductError();
				//throw DuplicateProductError(inventToBeProc[i].substr(0, 5));
			}
		}
	}

	//**echo print to file**
	//dump inventory vector contents to output file && screen
	receiptOut.putFile(inventOut);
	for (size_t i = 0; i < inventOut.size(); i++)
	{
		cout << inventOut[i] << endl;
	}

	//prompt user for input
	cout << endl << "Ready for orders." << endl;

	//**process order**
	vector<order> orders;
	bool moreOrders = true;
	while (moreOrders)
	{
		//create product storage
		order myOrder = order();

		bool moreProducts = true;
		while (moreProducts)
		{
			string number;
			string quant;
			cout << "Enter product number and quantity:" << endl;
			cin >> number >> quant;
			cout << endl;

			if (number.compare("0") != 0)
			{
				//if item number entered is not in inventory || if times is not within [1..100]
					//write error to reciept and start prompt again
				//push item to storage
				myOrder.addToOrder(myProduct);
				//**output reciept**
				//when order is complete output to receipt && screen
			} else {

				moreProducts = false;
			}
		}
		
		orders.push_back(myOrder);

		//prompt cashier to create another order
		string answer;
		cout << "Would you like to enter another order?" << endl;
		cin >> answer;
		cout << endl;
		//if done entering orders set flag to exit while loop
		if (answer.compare("N"))
		{
			moreOrders = false;
		}

	}


	cout << "it works duh!" << endl;
	system("pause");
	return 0;
}

//convert from strings to products to make use of (ADT) product class
product stringsToProduct(string stringsIn, int times)
{
	vector<string> myStack;
	//split variables from string
	stringstream myStr(stringsIn);
	myStr >> myStack[0] >> myStack[1] >> myStack[2] >> myStack[3];

	//create new inventory product from variables
	product myProduct = product(myStack[0], myStack[1], myStack[2], myStack[3], times);
	return myProduct;
}