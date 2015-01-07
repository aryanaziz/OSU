/**********
** Program: A12E3.cpp
** Author: Aryan Aziz
** Description: Creates product class with all appropriate items and constructors. 
** Input: none
** Output: 
**********/

#include <iostream>
#include <string>

class product {
	private:
		std::string name;
		int age;
		std::string color;
		double askingPrice;
		double pricePaid;
	public:
		product(std::string name, double pricePaid, int age = 0, std::string color = "none", double askingPrice = 0.0) {
			setName(name);
			setAge(age);
			setColor(color);
			setAskingPrice(askingPrice);
			setPricePaid(pricePaid);
		}
		void setName(std::string x) {
			name = x;
		}
		void setAge(int x) {
			age = x;
		}
		void setColor(std::string x) {
			color = x;
		}
		void setAskingPrice(double x) {
			askingPrice = x;
		}
		void setPricePaid(double x) {
			pricePaid = x;
		}
		std::string getName() {
			return name;
		}
		int getAge() {
			return age;
		}
		std::string getColor() {
			return color;
		}
		double getAskingPrice() {
			return askingPrice;
		}
		double getPricePaid() {
			return pricePaid;
		}
};

int main() {

	product product1("test", 1.0, 0, "blue", 2.0);

	std::cout << product1.getName();

	return 0;
}