#include "kwic.h"
#include "Word.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>


void testEmptyInput(){
	std::istringstream in{};
	std::ostringstream out{};
	kwic::kwic(in, out);
	ASSERT_EQUAL("", out.str());
}

void testSpecialCharOnly(){
	std::istringstream in{"1234!!! 13241234"};
	std::ostringstream out{};
	kwic::kwic(in, out);
	ASSERT_EQUAL("", out.str());
}

void testWithInput(){
	std::istringstream in{"This is"};
	std::ostringstream out{};
	kwic::kwic(in, out);
	ASSERT_EQUAL("is This \nThis is \n", out.str());
}

void testSpecialCharacters(){
	std::istringstream in{"This213!!234 !!!is12341324"};
	std::ostringstream out{};
	kwic::kwic(in, out);
	ASSERT_EQUAL("is This \nThis is \n", out.str());
}

void testMultipleLines(){
	std::istringstream in{"This is\n hallo du"};
	std::ostringstream out{};
	kwic::kwic(in, out);
	ASSERT_EQUAL("du hallo \nhallo du \nis This \nThis is \n", out.str());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(testEmptyInput));
	s.push_back(CUTE(testWithInput));
	s.push_back(CUTE(testSpecialCharacters));
	s.push_back(CUTE(testSpecialCharOnly));
	s.push_back(CUTE(testMultipleLines));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
