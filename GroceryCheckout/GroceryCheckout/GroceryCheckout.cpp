// GroceryCheckout.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fileHandler.h"
#include "product.h"
#include "DuplicateProductError.h"
#include "NotInInventoryError.h"
#include "NotInSpecifiedRangeError.h"

using namespace std;

//declarations
vector<product> stringsToProducts(vector<string> &stringsIn);

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

	//dump inventory vector contents to output file???
	//not sure why, just do it.
	receiptOut.putFile(inventOut);

	//convert from strings to products to make use of (ADT) product class
	vector<product> productInventory = stringsToProducts(inventClean);

	//**process order**
	//create product storage
	//prompt user for input
	//if item number entered is not in inventory || if times is not within [1..100]
		//write error to reciept and start prompt again
	//push item to storage

	//**output reciept**
	//when order is complete output to recipt



	cout << "it works duh!" << endl;
	system("pause");
	return 0;
}

//convert from strings to products to make use of (ADT) product class
vector<product> stringsToProducts(vector<string> &stringsIn)
{
	vector<product> myProducts;

	//get strings from vector
	for (int i = 0; i < stringsIn.size(); i++)
	{
		//split string to variables using stream
		vector<string> myStack;
		stringstream myStr(stringsIn[i]);
		myStr >> myStack[0] >> myStack[1] >> myStack[2] >> myStack[3];

		//create new inventory product from variables
		product myProduct = product(myStack[0], myStack[1], myStack[2], myStack[3]);
		myProducts.push_back(myProduct);
	}
	return myProducts;
}