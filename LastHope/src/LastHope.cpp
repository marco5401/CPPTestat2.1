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
using namespace std;

int main() {
	kwic::Kwic test{};

	test.addSentence(std::cin);


	return 0;
}
