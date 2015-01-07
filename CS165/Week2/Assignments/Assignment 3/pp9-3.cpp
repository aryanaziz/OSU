/**********
** Program: pp9-3.cpp
** Author: Aryan Aziz
** Description: Reads the person's name in the format of First Middle Last and outputs it as Last, First, Middle Initial
** Input: my_str(string)
** Output: Last name, first name, middle initial
**********/

#include <iostream>
#include <string>

std::string my_str;
int numSpaces;
int spaceLocation;
std::string firstName;
std::string secondName;
std::string thirdName;
int secondNameLength;
int thirdNameLength;

//Find the number of spaces in the word
void numberOfSpaces(std::string my_str){
	for(int i = 0; i < my_str.length(); i++){ //Go through each character in the string
		if(my_str[i] == ' '){ //Check if that specific character is a space
			numSpaces++; //Add to the counter
		}
	}
}

//Separate the First Name
void getFirstName(std::string my_str){
	spaceLocation = my_str.find(' ', 0); //Find the location of the space in the string
	firstName = my_str.substr(0, spaceLocation); //Create new string from beginning to space location
}

//Separate the Second Name
void getSecondName(int numSpaces, std::string my_str, std::string firstName){
	if(numSpaces == 1){ //If there are only 2 names
		secondNameLength = (my_str.length() - firstName.length() - 1); //Find the length of the second name for the substring
		secondName = my_str.substr((firstName.length() + 1), secondNameLength); //Create new string from beginning of 2nd name to end of string
	}	
	if(numSpaces == 2){ //If there are 3 names
		spaceLocation = my_str.find(' ', (firstName.length() + 1)); //Find the next space location in the string
		secondNameLength = (spaceLocation - firstName.length() - 1); //Find the length of the second name for the substring
		secondName = my_str.substr((firstName.length() + 1), secondNameLength); //Create new string from beginning of 2nd name to end of 2nd name

		if(secondNameLength == 1){ //If the user only entered an initial for the middle name
			secondName = secondName.append("."); //Add a period at the end
		}

		if(secondNameLength == 2){ //If the user entered a middle name with 2 characters
			if(secondName.find('.', 0) == -1){ //If there is no period within the 2 characters (people with 2 letter last names?)
				secondName = secondName.substr(0, 1).append("."); //Take just the first character and add a period
			}
		}

		if(secondNameLength > 2){ //If the user entered their full middle name
			secondName = secondName.substr(0, 1).append("."); //Take just the first character and add a period
		}
	}	
}

//Separate the Third Name
void getThirdName(std::string my_str){
	thirdNameLength = (my_str.length() - spaceLocation - 1); //Find the length of the third name
	thirdName = my_str.substr(spaceLocation + 1, thirdNameLength); //Start from 1 unit after the space location (because spaceLocation = beginning of space) and get third name
}

int main(){
	std::cout << "Please enter your name in the format of First Middle Last: "; //Ask for Input
	getline(std::cin, my_str);
	numberOfSpaces(my_str); //Run the numberOfSpaces function

	if(numSpaces == 1){ //If there are only 2 names
		getFirstName(my_str); //Get First Name
		getSecondName(numSpaces, my_str, firstName); //Get Last Name

		std::cout << "Your name in Last, First: " << secondName << ", " << firstName << std::endl;
	}

	if(numSpaces == 2){ //If there are 3 names
		getFirstName(my_str); //Get First Name
		getSecondName(numSpaces, my_str, firstName); //Get Middle Name
		getThirdName(my_str); //Get Last Name

		std::cout << "Your name in Last, First M: " << thirdName << ", " << firstName << " " << secondName << std::endl;
	}
	return 0;
}