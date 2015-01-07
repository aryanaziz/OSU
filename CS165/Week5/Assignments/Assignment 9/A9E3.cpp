/**********
** Program: A9E3.cpp
** Author: Aryan Aziz
** Description: Fun with structs and functions!
** Input: None. 
** Output: The person's age after they had a birthday. 
**********/

#include <iostream>
#include <string>

class person{
	private:
		std::string name;
		int age;
	public:
		std::string getName() {
			return name;
		}
		int getAge() {
			return age;
		}
		void setAge(int x){
			age = x;
		}
		void setName(std::string x){
			name = x;
		}
		int having_birthday(void) {
			return age++;
		}
};

person newPerson() {
	person newPerson;
	newPerson.setName("Aryan");
	newPerson.setAge(23);

	newPerson.having_birthday();
	return newPerson;
}

int main() {

	std::cout << newPerson().getAge() << std::endl;



	return 0;
}