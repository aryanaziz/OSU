/**********
** Program: A12E2.cpp
** Author: Aryan Aziz
** Description: Creates a product class 
** Input: none
** Output: 
**********/

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int getProductID( int ids[], string names[],
int numProducts, string target)	{
	for( int i=0; i < numProducts; i++)	{ 
		if(names[i] == target) 
			return ids[i]; 
	}

	std::string s = "Product Not Found";
	throw s;
	//return -1;// Not found
}

int main()	{
	int productIds[] = {4, 5, 8, 10, 13}; 
	string products[] = {"computer","flash drive", "mouse","printer","camera"}; 

	try {
		cout << getProductID(productIds, products, 5, "mouse") << endl; 
		cout << getProductID(productIds, products, 5, "camera") << endl; 
		cout << getProductID(productIds, products, 5, "laptop") << endl; 
	}

	catch(std::string s) {
		cout << s << endl;
	}
	
	return 0; 
}