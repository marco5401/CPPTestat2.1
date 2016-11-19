#include "word.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <iostream>

const std::string DEFAULT_FIRST_WORD{"This"}; // This
const std::string DEFAULT_SECOND_WORD{"is"}; // is
const std::string DEFAULT_THIRD_WORD{"weird"}; // weird
const std::string DEFAULT_MULTI_WORD{DEFAULT_FIRST_WORD + " " + DEFAULT_SECOND_WORD}; //  This
const std::string DEFAULT_UNFORMATTED_WORD_LEADING_THRASH{"%*" + DEFAULT_FIRST_WORD}; // %*This
const std::string DEFAULT_UNFORMATTED_THRASH_MULTI_WORD{"11" + DEFAULT_FIRST_WORD + "44"
	+ DEFAULT_SECOND_WORD + "55"
	+ DEFAULT_THIRD_WORD + "22"}; // This44is55weird22    ["This", "is", "weird"]

/**
 * Test the output stream of a word using the print method.
 */
void testOutStreamPrintMethod() {
	word::Word wordObject{DEFAULT_FIRST_WORD};
	std::ostringstream out{};

	wordObject.print(out);

	ASSERT_EQUAL(DEFAULT_FIRST_WORD, out.str());
}

/**
 * Test the output stream of a word using the overloaded << operator.
 */
void testOutStreamWithOperator()
{
	word::Word wordObject{DEFAULT_FIRST_WORD};
	std::ostringstream out{};

	out << wordObject;

	ASSERT_EQUAL(DEFAULT_FIRST_WORD, out.str());
}

/**
 * Test the input stream of a word using the read() method.
 */
void testInStreamReadMethod()
{
	word::Word wordObject{};
	std::istringstream in{DEFAULT_FIRST_WORD};

	wordObject.read(in);

	std::ostringstream out{};
	wordObject.print(out);

	ASSERT_EQUAL(DEFAULT_FIRST_WORD, out.str());
}

/**
 * Test the input stream of a word using the constructor.
 */
void testInStreamWithConstructor()
{
	std::istringstream in{DEFAULT_FIRST_WORD};

	word::Word wordObject{in};

	std::ostringstream out{};
	wordObject.print(out);

	ASSERT_EQUAL(DEFAULT_FIRST_WORD, out.str());
}

/**
 * Test the input stream of a word using the overloaded >> operator.
 */
void testInStreamWithOperator()
{
	word::Word wordObject{};
	std::istringstream in{DEFAULT_FIRST_WORD};

	in >> wordObject;

	// Assert, that the input stream is still good.
	ASSERT_EQUAL(in.fail(), false);

	std::ostringstream out{};
	wordObject.print(out);

	ASSERT_EQUAL(DEFAULT_FIRST_WORD, out.str());
}

/**
 * Test the input stream of a word with leading "thrash" characters that should be omitted.
 */
void testWordWithLeadingThrash()
{
	word::Word wordObject{};
	std::istringstream in{DEFAULT_UNFORMATTED_WORD_LEADING_THRASH};

	wordObject.read(in);

	std::ostringstream out{};
	wordObject.print(out);

	ASSERT_EQUAL(DEFAULT_FIRST_WORD, out.str());
}

/**
 * Test the input stream using multiple words separated by a space.
 */
void testMultipleWords()
{
	word::Word wordObject1{};
	word::Word wordObject2{};
	std::istringstream in{DEFAULT_MULTI_WORD};

	wordObject1.read(in);
	wordObject2.read(in);

	std::ostringstream out1{};
	std::ostringstream out2{};

	wordObject1.print(out1);
	ASSERT_EQUAL(DEFAULT_FIRST_WORD, out1.str());

	wordObject2.print(out2);
	ASSERT_EQUAL(DEFAULT_SECOND_WORD, out2.str());
}

void testMultipleThrashWords()
{
	word::Word wordObject1{};
	word::Word wordObject2{};
	word::Word wordObject3{};

	std::istringstream in{DEFAULT_UNFORMATTED_THRASH_MULTI_WORD};

	wordObject1.read(in);
	wordObject2.read(in);
	wordObject3.read(in);

	std::ostringstream out1{};
	std::ostringstream out2{};
	std::ostringstream out3{};

	wordObject1.print(out1);
	ASSERT_EQUAL(DEFAULT_FIRST_WORD, out1.str());

	wordObject2.print(out2);
	ASSERT_EQUAL(DEFAULT_SECOND_WORD, out2.str());

	wordObject3.print(out3);
	ASSERT_EQUAL(DEFAULT_THIRD_WORD, out3.str());
}

void testEqualOperator() {
	word::Word wordObject1{DEFAULT_FIRST_WORD};
	word::Word wordObject2{DEFAULT_FIRST_WORD};

	bool result{(wordObject1 == wordObject2)};

	ASSERT_EQUAL(true, result);
}

void testSmallerThan() {
	word::Word wordObject1{"abc"}; // Is smaller
	word::Word wordObject2{"cba"}; // Is greater

	bool result{wordObject1 < wordObject2};

	ASSERT_EQUAL(true, result);
}

void testGreaterThan() {
	word::Word wordObject1{"cba"}; // Is greater
	word::Word wordObject2{"abc"}; // Is smaller

	bool result{wordObject1 > wordObject2};

	ASSERT_EQUAL(true, result);
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(testOutStreamWithOperator));
	s.push_back(CUTE(testInStreamWithOperator));
	s.push_back(CUTE(testInStreamReadMethod));
	s.push_back(CUTE(testOutStreamPrintMethod));
	s.push_back(CUTE(testInStreamWithConstructor));
	s.push_back(CUTE(testWordWithLeadingThrash));
	s.push_back(CUTE(testMultipleWords));
	s.push_back(CUTE(testMultipleThrashWords));
	s.push_back(CUTE(testEqualOperator));
	s.push_back(CUTE(testSmallerThan));
	s.push_back(CUTE(testGreaterThan));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
