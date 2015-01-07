/**********
** Program: A13E1.cpp
** Author: Aryan Aziz
** Description: Rudementary logging book. 
** Input: choice(std::string), name(std::string)
** Output: Log info
**********/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<std::string> visitors;
std::string choice;
std::string name;
char again;

void checkName(std::string name) {
    if(std::find(visitors.begin(), visitors.end(), name) != visitors.end()) {
        std::cout << "Person found" << std::endl;;
    }
    else {
        std::cout << "Person not found" << std::endl;
    }
}

void addName(std::string name) {
    visitors.push_back(name);
    std::cout << "Visitor, " << name << ", has been added." << std::endl;
}

void removeName(std::string name) {
    visitors.erase(std::find(visitors.begin(), visitors.end(), name));
    std::cout << "Visitor, " << name << ", has been removed." << std::endl;
}

int main()
{
    do {
        std::cout << "Hello, what would you like to do?" << std::endl;
        std::cout << "1) Check for a visitor" << std::endl;
        std::cout << "2) Add a new visitor" << std::endl;
        std::cout << "3) Remove a visitor" << std::endl;

        getline(std::cin, choice);
        while(choice.length() > 1) {
            std::cout << "That's not a valid choice; please choose 1, 2, or 3" << std::endl;
            getline(std::cin, choice);
        }
        while(choice[0] != '1' && choice[0] != '2' && choice[0] != '3') {
            std::cout << "That's not a valid choice; please choose 1, 2, or 3" << std::endl;
            getline(std::cin, choice);
        }

        if(choice[0] == '1') {
            std::cout << "Please enter a name to be searched: ";
            getline(std::cin, name);
            checkName(name);
        }

        if(choice[0] == '2') {
            std::cout << "Please enter a name to be added: ";
            getline(std::cin, name);
            addName(name);
        }

        if(choice[0] == '3') {
            std::cout << "Please enter a name to be removed: ";
            getline(std::cin, name);
            removeName(name);
        }

        std::cout << "Exit? (y/n) "; //Ask if you want to play again.
        std::cin >> again;
        std::cin.ignore();
        std::cin.clear();

    } while (again == 'n' || again == 'N');

    return 0;
}

