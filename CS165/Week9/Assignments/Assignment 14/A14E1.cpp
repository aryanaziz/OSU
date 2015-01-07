/**********
** Program: A14E1.cpp
** Author: Aryan Aziz
** Description: Children classes yo. 
** Input: None
** Output: some data about the classes
**********/

#include <iostream>
#include <string>

class SalariedEmployee {
	protected:
		std::string name;
		std::string ssn;
		double salary;
	public:
		void set_values(std::string x, std::string y, double z) {
			name = x;
			ssn = y;
			salary = z;
		}
		void printCheck();
};

class Administrator : public SalariedEmployee {
	public:
		Administrator(std::string x, std::string y, std::string z) {
			supervisor = x;
			department = y;
			title = z;
		}
		void setSupervisor(std::string x) {
			supervisor = x;
		}
		void setAdminData(void) {
			std::cout << "Please enter the Administrator's Title: ";
			getline(std::cin, title);
			std::cout << "Please enter the Department: ";
			getline(std::cin, department);
			std::cout << "Please enter the Supervisor: ";
			getline(std::cin, supervisor);
		}
		void print(void) {
			std::cout << "Administrator Title: " << title << std::endl;
			std::cout << "Administrator Department: " << department << std::endl;
			std::cout << "Administrator Supervisor: " << supervisor << std::endl;
			std::cout << "Administrator Name: " << name << std::endl;
			std::cout << "Administrator SSN: " << ssn << std::endl;
			std::cout << "Administrator Salary: " << salary << std::endl;
		}
		void printCheck() {
			std::cout << "Check for: " << name << std::endl;
			std::cout << "For the amount of: " << salary << std::endl;
			std::cout << "Signed by: " << supervisor << std::endl;
		}
	protected:
		std::string supervisor;
		std::string department;
		std::string title;
};
  
int main () {
	Administrator Employee1("John Doe", "Operations", "Director of Operations");
	Employee1.set_values("First Last", "123-456-7890", 1000.00);

	Employee1.print();
	std::cout << std::endl;
	Employee1.printCheck();
  return 0;
}