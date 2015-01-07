/**********
** Program: A14E1.cpp
** Author: Aryan Aziz
** Description:
** Input:
** Output:
**********/

#include <iostream>
#include <string>

/////Taken from Display 14.4 with some modifcations to add some extra member functions and protected
class SalariedEmployee {
	public:
		SalariedEmployee();
		SalariedEmployee(std::string theName, std::string theSsn, double theWeeklySalary) {
			setName(theName);
			setSsn(theSsn);
			setSalary(theWeeklySalary);

		};
		double getsalary() {
			return salary;
		}
		void setSalary(double newSalary) {
			salary = newSalary * 52;
		};
		void setName(std::string theName) {
			name = theName;
		}
		std::string getName() {
			return name;
		}
		void setSsn(std::string theSsn) {
			ssn = theSsn;
		}
		std::string getSsn() {
			return ssn;
		}
		void printCheck();
	private:		
	protected:
		double salary;
		std::string name;
		std::string ssn;
};

/////Administrator Child
class Administrator : public SalariedEmployee {
	public:
		Administrator(std::string department, std::string title, std::string supervisor);
		Administrator();
		void setSupervisor(std::string x) {
			supervisor = x;
		}
		void setDepartment(std::string x) {
			department = x;
		}
		void setTitle(std::string x) {
			title = x;
		}
		void print(void) {
			std::cout << "Administrator Title: " << title << std::endl;
			std::cout << "Administrator Department: " << department << std::endl;
			std::cout << "Administrator Supervisor: " << supervisor << std::endl;
		}
		void printCheck() {
			std::cout << "/////////////////////////////////////////////////" << std::endl;
			std::cout << "///// Pay to the order of: ";
		}
	private:
		std::string title;
		std::string department;
		std::string supervisor;
};

Administrator::Administrator() {
	supervisor = "";
	department = "";
	title = "";
}



int main() {
	SalariedEmployee Employee1("First Last", "123-456-7890", 1000.00);
	Administrator Position1;


	std::cout << Employee1.getSsn();
	return 0;
}