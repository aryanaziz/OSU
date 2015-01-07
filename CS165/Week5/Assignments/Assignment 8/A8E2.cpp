/**********
** Program: A8E2.cpp
** Author: Aryan Aziz
** Description: Programming project 6.1. 
** Input: quiz1(int), quiz2(int), midterm(int), final(int)
** Output: The students grades. 
**********/

#include <iostream>

double quizAverage;
double midtermAverage;
double finalAverage;
double overallScore;

struct grades {
	int quiz1;
	int quiz2;
	int midterm;
	int final;
};

grades new_grades(void);

int main() {
	grades gradesStruct;

	gradesStruct = new_grades();

	std::cout << "Student's Grades: " << std::endl;
	std::cout << "Quiz 1: " << gradesStruct.quiz1 << std::endl;
	std::cout << "Quiz 2: " << gradesStruct.quiz2 << std::endl;
	std::cout << "Midterm: " << gradesStruct.midterm << std::endl;
	std::cout << "Final: " << gradesStruct.final << std::endl;

	quizAverage = (((gradesStruct.quiz1 + gradesStruct.quiz2) / 2.0) * 10) * .25;
	midtermAverage = gradesStruct.midterm * .25;
	finalAverage = gradesStruct.final * .5;
	overallScore = quizAverage + midtermAverage + finalAverage;

	std::cout << "The student's overall grade is: " << overallScore << "%" << std::endl;

	if(overallScore >= 90){
		std::cout << "The student receives an A in the class" << std::endl;
	}

	else if(overallScore >= 80 && overallScore < 90){
		std::cout << "The student receives a B in the class" << std::endl;
	}

	else if(overallScore >= 70 && overallScore < 80){
		std::cout << "The student receives a C in the class" << std::endl;
	}

	else if(overallScore >= 60 && overallScore < 70){
		std::cout << "The student receives a D in the class" << std::endl;
	}

	else {
		std::cout << "The student receives an F in the class";
	}


	return 0;
}

grades new_grades(void) {
	grades newGrades;

	std::cout << "Please enter the score for quiz1: ";
	std::cin >> newGrades.quiz1;
	std::cout << "Please enter the score for quiz2: ";
	std::cin >> newGrades.quiz2;
	std::cout << "Please enter the score for midterm: ";
	std::cin >> newGrades.midterm;
	std::cout << "Please enter the score for final: ";
	std::cin >> newGrades.final;

	return newGrades;
}