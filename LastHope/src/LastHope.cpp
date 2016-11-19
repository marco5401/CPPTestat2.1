//============================================================================
// Name        : LastHope.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <Word.h>
#include <kwic.h>
#include <sstream>
using namespace std;

int main() {
	kwic::Kwic test{};

	cout << "Eingabe: ";

	//std::istringstream in{"Test me now"};

	test.addSentence(std::cin);
	cout << "Sentence added, printing now!" << endl;
	test.print(std::cout);


	return 0;
}
