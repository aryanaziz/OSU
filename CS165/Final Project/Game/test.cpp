#include <iostream>
#include <fstream>
#include <string>

std::string twoDimensionalArray[5][5];
std::string level;

class question {
	private:
		std::string questionText;
	public:
		void setQuestionText(std::string x) {
			questionText = x;
		}
		std::string getQuestionText(void) {
			return questionText;
		}
};

struct answer {
	std::string answerText;
};

int generateRandom() {
	srand(time(NULL));
	return rand() % 5 + 1;
};

question aQuestion;
answer answer1;
answer answer2;
answer answer3;
answer answer4;


/*void getQuestion() {
	
	int lineBegin = generateRandom()*5;
	std::string line;

	for(int i = 0; getline(ifs, line) && i <= 100; i++) {
		if(i == lineBegin) {
			twoDimensionalArray[0][0] = line;
			aQuestion.setQuestionText(line);
		}
		if(i == lineBegin+1) {
			twoDimensionalArray[0][1] = line;
			answer1.answerText = twoDimensionalArray[0][1];
		}
		if(i == lineBegin+2) {
			twoDimensionalArray[0][2] = line;
			answer1.answerText = line;
		}
		if(i == lineBegin+3) {
			twoDimensionalArray[0][3] = line;
			answer1.answerText = line;
		}
		if(i == lineBegin+4) {
			twoDimensionalArray[0][4] = line;
			answer1.answerText = line;
		}
	}

};*/

void putQuestionsInArray(std::string level) {
	std::ifstream ifs;
	std::string fileName = "questions" + level + ".txt";
	ifs.open(fileName.c_str());

	int lineBegin = generateRandom()*5;
	std::string line;

	for(int i = 0; getline(ifs, line) && i <= 100; i++) {
		if(i == lineBegin) {
			twoDimensionalArray[0][0] = line;
			aQuestion.setQuestionText(line);
		}
		if(i == lineBegin+1) {
			twoDimensionalArray[0][1] = line;
			answer1.answerText = twoDimensionalArray[0][1];
		}
		if(i == lineBegin+2) {
			twoDimensionalArray[0][2] = line;
			answer1.answerText = line;
		}
		if(i == lineBegin+3) {
			twoDimensionalArray[0][3] = line;
			answer1.answerText = line;
		}
		if(i == lineBegin+4) {
			twoDimensionalArray[0][4] = line;
			answer1.answerText = line;
		}
	}


};


int main() {
	
	putQuestionsInArray("1");
	for(int i = 0; i < 5; i++) {
		std::cout << twoDimensionalArray[0][i] << std::endl;
	}



	return 0;
}