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

	std::vector<word::Word> actual{kwicObject.readTextLine(in)};

	//How do I initialize a vector with objects?
	word::Word one{"this"};
	word::Word two{"is"};
	word::Word three{"a"};
	word::Word four{"test"};

	std::vector<word::Word> expected{one, two, three, four};

	/*
	 * I tested the assertion with the code below and it worked
	std::vector<word::Word> expected{one, two, three, four};
	std::vector<word::Word> expected2{one, two, three, four};
	 */

	ASSERT_EQUAL(true, std::equal(actual.begin(), actual.end(), expected.begin(), expected.end(), [](const auto it1, const auto it2) -> bool{ return (it1 == it2);}));

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

//returns true if first is lexicographically after second or equal
void testCompareVectorsSame()
{
	word::Word one{"this"};
	word::Word two{"is"};
	word::Word three{"a"};
	word::Word four{"test"};
	std::vector<word::Word> v1{one, two, three, four};
	std::vector<word::Word> v2{one, two, three, four};

	kwic::Kwic kwicObject{};

	ASSERT_EQUAL(true, kwicObject.compareVectors(v1, v2));
}

void testCompareVectorsFistIsSmaller()
{
	word::Word one{"this"};
	word::Word two{"is"};
	word::Word three{"a"};
	word::Word four{"test"};
	std::vector<word::Word> v1{one, two, three};
	std::vector<word::Word> v2{one, two, three, four};

	kwic::Kwic kwicObject{};

	ASSERT_EQUAL(false, kwicObject.compareVectors(v1, v2));
}

void testCompareVectorsSecondIsSmaller()
{
	word::Word one{"this"};
	word::Word two{"is"};
	word::Word three{"a"};
	word::Word four{"test"};
	std::vector<word::Word> v1{one, two, three, four};
	std::vector<word::Word> v2{one, two, three};

	kwic::Kwic kwicObject{};

	ASSERT_EQUAL(true, kwicObject.compareVectors(v1, v2));
}

void testCompareVectorsFirstIsLexicographicallyBefore()
{
	word::Word one{"aaa"};
	word::Word two{"is"};
	word::Word three{"a"};
	word::Word four{"test"};
	std::vector<word::Word> v1{one, two, three, four};
	std::vector<word::Word> v2{four, two, three};

	kwic::Kwic kwicObject{};

	ASSERT_EQUAL(true, kwicObject.compareVectors(v1, v2));
}

void testCompareVectorsSecondIsLexicographicallyBefore()
{
	word::Word one{"aaa"};
	word::Word two{"is"};
	word::Word three{"a"};
	word::Word four{"test"};
	std::vector<word::Word> v1{four, two, three, four};
	std::vector<word::Word> v2{one, two, three};

	kwic::Kwic kwicObject{};

	ASSERT_EQUAL(false, kwicObject.compareVectors(v1, v2));
}

void testSortedInsertion()
{

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
	s.push_back(CUTE(testCompareVectorsSame));
	s.push_back(CUTE(testCompareVectorsFistIsSmaller));
	s.push_back(CUTE(testCompareVectorsSecondIsSmaller));
	s.push_back(CUTE(testCompareVectorsFirstIsLexicographicallyBefore));
	s.push_back(CUTE(testCompareVectorsSecondIsLexicographicallyBefore));
	s.push_back(CUTE(testCreateVariatons));
	s.push_back(CUTE(testSortSentences));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
