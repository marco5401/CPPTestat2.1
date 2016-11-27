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

void testReadTextLine()
{
	std::istringstream in{"this is a test"};
	kwic::Kwic kwicObject{};

	std::vector<word::Word> actual{kwicObject.readSentence(in)};

	//How do I initialize a vector with objects?
	word::Word one{"this"};
	word::Word two{"is"};
	word::Word three{"a"};
	word::Word four{"test"};

	std::vector<word::Word> expected{one, two, three, four};

	ASSERT_EQUAL(expected, actual);

}

void testCreateVariatons()
{
	word::Word one{"this"};
	word::Word two{"is"};
	word::Word three{"a"};
	word::Word four{"test"};

	std::vector<word::Word> v1{one, two, three, four};

	kwic::Kwic kwicObject{};
	std::vector<std::vector<word::Word>> actual{kwicObject.createVariatons(v1)};

	std::vector<word::Word> v2{two, three, four, one};
	std::vector<word::Word> v3{three, four, one, two};
	std::vector<word::Word> v4{four, one, two, three};

	std::vector<std::vector<word::Word>> expected{v1, v2, v3, v4};

	ASSERT_EQUAL(true, (expected == actual));

}

/*
void testSortSentences()
{
	word::Word one{"aaa"};
	word::Word two{"bbb"};
	word::Word three{"ccc"};
	word::Word four{"ddd"};

	std::vector<word::Word> v1{one, two, three, four};
	std::vector<word::Word> v2{two, three, four, one};
	std::vector<word::Word> v3{three, four, one, two};
	std::vector<word::Word> v4{four, one, two, three};

	std::vector<std::vector<word::Word>> actual{v3, v1, v2, v4};
	std::vector<std::vector<word::Word>> expected{v1, v2, v3, v4};

	kwic::Kwic kwicObject{};
	kwicObject.sortSentences(actual);

	ASSERT_EQUAL(expected, actual);

}
*/

void testPrintSentence()
{
	std::ostringstream out{};
	word::Word one{"aaa"};
	word::Word two{"bbb"};
	std::vector<word::Word> v1{one, two};
	kwic::Kwic kwicObject{};

	kwicObject.printSentence(v1, out);

	ASSERT_EQUAL("aaa bbb \n", out.str());
}





void testPrint()
{
	/*
	std::istringstream in{"this is a test"};
	kwic::Kwic kwicObject{};

	std::ostringstream out{};

	kwicObject.print(out);

	ASSERT_EQUAL(, out.str());
	 */
}


bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(testReadTextLine));
	s.push_back(CUTE(testCreateVariatons));
	//s.push_back(CUTE(testSortSentences));
	s.push_back(CUTE(testPrintSentence));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
