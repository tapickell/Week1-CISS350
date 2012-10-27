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

    //check inventory to be processed vector for contents
	cout << endl;
	cout << "inventory checkup" << endl;
    for (size_t i = 0; i < inventToBeProc.size(); i++)
    {
        cout << inventToBeProc[i] << endl;
    }

	//**process inventory**
	//iterate through inventory from file
	for (size_t i = 0; i < inventToBeProc.size(); i++)
	{
		cout << endl;
		cout << "Inventory to be proc:" << inventToBeProc[i] << endl;
		//check for duplication of items if there is anything in clean
		if (!inventClean.empty())
		{
			//****** ISSUE: is causing incremental increase in products being added to clean ********// RESOLVED 10-26-12
			cout << "InventClean size: " << inventClean.size() << endl;
			bool match = false;
			for (size_t j = 0; j < inventClean.size(); j++) 
			{
				//compare product number from file to product number stored in clean inventory
				if (inventClean[j].compare(0, 5, inventToBeProc[i], 0, 5) == 0)
				{
					//if match found
					match = true;
				}//end if
			}//end for

			try
			{
				if (!match)
				{
					//push clean items onto stores
					inventClean.push_back(inventToBeProc[i]);
					inventOut.push_back(inventToBeProc[i]);
					cout << inventToBeProc[i] << " added to clean inventory from if" << endl;
				} else {
					cout << "hit else for match in vectors!" <<  endl;
					//throw exception, would like to pass product number to error class
					throw DuplicateProductError();
					//throw DuplicateProductError(inventToBeProc[i].substr(0, 5));
				}//end if else
			}
			catch (DuplicateProductError &e)
			{
				cout << "Exception: " << e.what() <<  endl;
				//if file contains duplication dont add second entry to storage
				//write error out to reciept
				string errorString = "*** Duplicate ";
				errorString = errorString.append(inventToBeProc[i].substr(0,5));
				errorString = errorString.append(" in inventory file ***");
				inventOut.push_back(errorString);
			}

		} else {
			//push clean item onto stores
			inventClean.push_back(inventToBeProc[i]);
			inventOut.push_back(inventToBeProc[i]);
			cout << inventToBeProc[i] << " added to clean inventory from else" << endl;
		}//end if else
	}//end for

	//**echo print to file**
	//dump inventory vector contents to output file && screen
	//receiptOut.putFile(inventOut); *************** UNCOMMENT AFTER TESTING IS READY ********************
	cout << endl;
	for (size_t i = 0; i < inventOut.size(); i++)
	{
		cout << "Inventory out " << inventOut[i] << endl; //not printing out to screen
	}//would like to pull this out into seprerate function to DRY it out

	//prompt user for input
	cout << endl << "Ready for orders." << endl;

	//**process order**
	vector<order> orders; //could be used to expand program to have an end of shift totals printout
	bool moreOrders = true; //flag for exiting while loop
	while (moreOrders)
	{
		//create product storage
		order myOrder = order();   //*********  creating order  ***********//
		vector<string> recpt;

		bool moreProducts = true; //flag for exiting while loop
		while (moreProducts)
		{
			//variables to hold input
			string number;
			int quant;

			//prompt for product info from cashier
			cout << "Enter product number and quantity:" << endl;
			cin >> number >> quant;
			cout << endl;

			if (number.compare("0") != 0)
			{
				try //for NotInSpecifiedRangeError 
				{
					//check quantity range if not in range don't bother searching inventory
					if (quant > 0 && quant < 100)
					{
						bool found = false;
						//find product in inventory by product number
						try
						{
							for (size_t i = 0; i < inventClean.size(); i++)
							{
								int y = inventClean[i].find(number);
								//if that product is in inventory found by product number
								if (y > -1 && y < 6)
								{
									//set flag
									found = true;
									//create product passing in string from inventory and quantity
									product myProduct = stringsToProduct(inventClean[i], quant);  //****** creating product *********//
									//push item to receipt
									recpt.push_back(myProduct.toString());
									//push item to storage
									myOrder.addToOrder(myProduct);
								}//end if
							}//end for

							if (!found)
							{
								//through exception, would like to pass product number to error class
								throw NotInInventoryError();
								//throw NotInInventoryError(inventClean[i].substr(0, 5));
							}
						}
						catch (NotInInventoryError &e)
						{
							cout << "Exception: " << e.what() <<  endl;
							//if product not found add error message to recept and skip entry
							string errorStrng = "*** item ";
							errorStrng = errorStrng.append(number);
							errorStrng = errorStrng.append(" not in invntory ***");
							recpt.push_back(errorStrng);
						}

					} else {
						//through exception, would like to pass product number to error class
						throw NotInSpecifiedRangeError();
						//throw NotInSpecifiedRangeError(quant);
					}//end if else
				}
				catch (NotInSpecifiedRangeError &e)
				{
					cout << "Exception: " << e.what() <<  endl;
					//if not in range add error message to recept and skip entry
					string errorString = "*** ";
					stringstream stupidconversions;
					stupidconversions << quant;
					errorString = errorString.append(stupidconversions.str());
					errorString = errorString.append(" not in specified range ***");
					recpt.push_back(errorString);
				}//end try catch

			} else {
				//done entering products for this order
				//set flag to exit while loop
				moreProducts = false;
			}
		}

		//*** Print Order Here ***//
		//when order is complete output to receipt && screen
		//print receipt header
		vector<string> header = myOrder.getReceiptHeader();
		receiptOut.putFile(header);
		for (size_t i = 0; i < header.size(); i++)
		{
			cout << header[i] << endl;
		}

		//print products
		receiptOut.putFile(recpt);
		for (size_t i = 0; i < recpt.size(); i++)
		{
			cout << recpt[i] << endl;
		}//would like to pull this out into seprerate function to DRY it out

		//print receipt footer
		vector<string> footer = myOrder.getReceiptFooter();
		receiptOut.putFile(footer);
		for (size_t i = 0; i < footer.size(); i++)
		{
			cout << footer[i] << endl;
		}
		cout << endl;

		//add order to orders store
		orders.push_back(myOrder);

		//variable to hold input
		string answer;

		//prompt cashier to create another order
		cout << "Would you like to enter another order?  [Y/N]" << endl;
		cin >> answer;
		cout << endl;
		//if done entering orders set flag to exit while loop
		if (answer.compare("N") == 0)
		{
			//exit with freindly message
			cout << "Thank you for using the Pickle POS system" << endl << "Have a nice day" << endl;
			moreOrders = false;
		}

	}


	cout << endl;
	system("pause");
	return 0;
}

//convert from strings to products to make use of (ADT) product class
product stringsToProduct(string stringsIn, int times)
{
	vector<string> myStack (4);
	//split variables from string
	stringstream myStr(stringsIn);
	myStr >> myStack[0] >> myStack[1] >> myStack[2] >> myStack[3]; //**** CAUSED VECTOR OUT OF RANGE ****//

	//create new inventory product from variables
	product myProduct = product(myStack[0], myStack[1], myStack[2], myStack[3], times);
	return myProduct;
}