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

	bool equal = equal(actual.begin(), actual.end(), expected.begin(), expected.end(), [](const auto it1, const auto it2) -> bool{ return (*it1 == *it2);});

	ASSERT_EQUAL(true, equal);

}


/*
void testAddingSentence() {
	std::istringstream in{"This is a test"};

	kwic::Kwic kwic{};
	kwic.addSentence(in);

	std::string vorlage{"This is a test  is a test  This a test  This is test  This is a  This is a test "};
	std::ostringstream out{};
	kwic.print(out);

	ASSERT_EQUAL(vorlage, out.str());
}


void testSortVector(){
	kwic::Kwic kwicObject{};
	std::istringstream in{"This is a"};
	kwicObject.addSentence(in);
	kwicObject.sort();
	std::ostringstream out{};
	kwicObject.print(out);
}
*/

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(testReadTextLine));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
