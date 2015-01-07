/**********
** Program: A8E3.cpp
** Author: Aryan Aziz
** Description: PP6.1 but taking into consideration if there are command line values. 
** Input: quiz1(int), quiz2(int), midterm(int), final(int)
** Output: Student's grades. 
**********/

#include <iostream>
#include <cstdlib>

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

int main(int argc, char *argv[]) {
	grades gradesStruct;

	if(argc < 5){
		gradesStruct = new_grades();
	}

	else {
		gradesStruct.quiz1 = std::atoi(argv[1]);
		gradesStruct.quiz2 = std::atoi(argv[2]);
		gradesStruct.midterm = std::atoi(argv[3]);
		gradesStruct.final = std::atoi(argv[4]);
	}
	

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