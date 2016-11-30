#include "word.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <iostream>
#include <sstream>

using word::Word;

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

	ASSERT(result);
}

void testReadUntilEOF() {
	std::string sentence{"This is a test"};
	std::istringstream in{sentence};

	unsigned int retrys{0};

	for(unsigned retrys = 0; retrys < sentence.length(); retrys++) {
		word::Word wordObject{in};
		if(in.eof()) {
			break;
		}
	}

	if(retrys >= sentence.length()) {
		FAILM("The reading is in an endless loop or took too long");
	}
}

/**
 * Week 7 Tests!
 */
void test_cannot_create_empty_word() {
	ASSERT_THROWS(Word { "" }, std::invalid_argument);
}

void test_cannot_create_word_with_space() {
	ASSERT_THROWS(Word { "abc xyz" }, std::invalid_argument);
}

void test_cannot_create_word_with_number() {
	ASSERT_THROWS(Word { "abc3xyz" }, std::invalid_argument);
}

void test_cannot_create_word_with_punctuation() {
	ASSERT_THROWS(Word { "abc.xyz" }, std::invalid_argument);
}

void test_output_operator() {
	std::string const expected { "Python" };
	Word const w { expected };
	std::ostringstream output { };
	output << w;
	ASSERT_EQUAL(expected, output.str());
}

void test_same_words_are_equal() {
	ASSERT_EQUAL(Word { "Ruby" }, Word { "Ruby" });
}

void test_different_words_are_not_equal() {
	ASSERT_NOT_EQUAL_TO(Word{"Haskell"}, Word{"ML"});
}

void test_same_word_with_different_cases_are_equal() {
	ASSERT_EQUAL(Word { "BASIC" }, Word { "basic" });
}

void test_same_word_is_not_lower_than() {
	ASSERT(!(Word { "Erlang" } < Word { "Erlang" }));
}

void test_smaller_word_is_smaller() {
	ASSERT_LESS(Word { "Erlang" }, Word { "Fortran" });
}

void test_smaller_word_with_capital_letters_is_smaller() {
	ASSERT_LESS(Word { "ADA" }, Word { "java" });
}

void test_same_word_with_different_cases_are_not_smaller() {
	ASSERT(!(Word {"Groovy"} < Word {"groovy"}));
}

void test_greater_word_is_greater() {
	ASSERT_GREATER(Word { "Rust" }, Word { "Prolog" });
}

void test_greater_word_with_capital_letters_is_greater() {
	ASSERT_GREATER(Word { "Lisp" }, Word { "brainfuck" });
}

void test_smaller_word_is_less_equal() {
	ASSERT_LESS_EQUAL(Word { "Algol" }, Word { "BCPL" });
}

void test_same_word_is_less_equal() {
	ASSERT_LESS_EQUAL(Word { "Assembler" }, Word { "Assembler" });
}

void test_greater_word_is_greater_equal() {
	ASSERT_GREATER_EQUAL(Word { "RPG" }, Word { "Perl" });
}

void test_same_word_is_greater_equal() {
	ASSERT_GREATER_EQUAL(Word { "Scala" }, Word { "Scala" });
}

void test_input_operator_single_word() {
	std::istringstream input{"Elixir"};
	Word w{};
	input >> w;
	ASSERT_EQUAL(Word{"Elixir"}, w);
}

void test_input_operator_single_word_stream_good() {
	std::istringstream input{"Cobol"};
	Word w{};
	ASSERT(input >> w);
}

void test_input_operator_called_once_first_word() {
	std::istringstream input{"Ceylon Go"};
	Word w{};
	input >> w;
	ASSERT_EQUAL(Word{"Ceylon"}, w);
}

void test_input_operator_called_once_stream_good() {
	std::istringstream input{"Lua Oberon"};
	Word w{};
	ASSERT(input >> w);
}

void test_input_operator_on_empty_stream_fail() {
	std::istringstream input{};
	Word w{};
	input >> w;
	ASSERT(input.fail());
}

void test_input_operator_on_stream_without_word() {
	std::istringstream input{"1337"};
	Word w{};
	input >> w;
	ASSERT(input.fail());
}

void test_input_operator_on_empty_stream_word_unchanged() {
	std::istringstream input{};
	Word w{"Eiffel"};
	input >> w;
	ASSERT_EQUAL(Word{"Eiffel"}, w);
}

void test_input_operator_stops_on_slash() {
	std::istringstream input{"PL/SQL"};
	Word w{};
	input >> w;
	ASSERT_EQUAL(Word{"PL"}, w);
}

void test_input_operator_stops_at_end_of_word() {
	std::istringstream input{"VB6"};
	Word w{};
	int i{};
	input >> w >> i;
	ASSERT_EQUAL(6, i);
}

void test_input_operator_skips_leading_non_alpha() {
	std::istringstream input{"3switchBF"};
	Word w{};
	input >> w;
	ASSERT_EQUAL(Word{"switchBF"}, w);
}

void test_input_operator_overwrites_word() {
	std::istringstream input{"Kotlin"};
	Word w{"JavaScript"};
	input >> w;
	ASSERT_EQUAL(Word{"Kotlin"}, w);
}

void test_exercise_example() {
	std::istringstream input{"compl33tely ~ weird !!??!! 4matted in_put"};
	Word w{};
	input >> w;
	ASSERT_EQUAL(Word{"compl"}, w);
	input >> w;
	ASSERT_EQUAL(Word{"tely"}, w);
	input >> w;
	ASSERT_EQUAL(Word{"weird"}, w);
	input >> w;
	ASSERT_EQUAL(Word{"matted"}, w);
	input >> w;
	ASSERT_EQUAL(Word{"in"}, w);
	input >> w;
	ASSERT_EQUAL(Word{"put"}, w);
	input >> w;
	ASSERT_EQUAL(Word{"put"}, w);
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
	s.push_back(CUTE(testReadUntilEOF));
	s.push_back(CUTE(test_cannot_create_empty_word));
	s.push_back(CUTE(test_cannot_create_word_with_space));
	s.push_back(CUTE(test_cannot_create_word_with_number));
	s.push_back(CUTE(test_cannot_create_word_with_punctuation));
	s.push_back(CUTE(test_input_operator_on_empty_stream_word_unchanged));
	s.push_back(CUTE(test_input_operator_stops_on_slash));
	s.push_back(CUTE(test_input_operator_stops_at_end_of_word));
	s.push_back(CUTE(test_input_operator_skips_leading_non_alpha));
	s.push_back(CUTE(test_input_operator_overwrites_word));
	s.push_back(CUTE(test_input_operator_on_stream_without_word));
	s.push_back(CUTE(test_greater_word_is_greater_equal));
	s.push_back(CUTE(test_same_word_is_greater_equal));
	s.push_back(CUTE(test_input_operator_single_word));
	s.push_back(CUTE(test_same_word_is_less_equal));
	s.push_back(CUTE(test_smaller_word_is_less_equal));
	s.push_back(CUTE(test_greater_word_with_capital_letters_is_greater));
	s.push_back(CUTE(test_greater_word_is_greater));
	s.push_back(CUTE(test_same_word_with_different_cases_are_not_smaller));
	s.push_back(CUTE(test_smaller_word_with_capital_letters_is_smaller));
	s.push_back(CUTE(test_smaller_word_is_smaller));
	s.push_back(CUTE(test_same_word_is_not_lower_than));
	s.push_back(CUTE(test_same_word_with_different_cases_are_equal));
	s.push_back(CUTE(test_different_words_are_not_equal));
	s.push_back(CUTE(test_same_words_are_equal));
	s.push_back(CUTE(test_output_operator));
	s.push_back(CUTE(test_input_operator_called_once_stream_good));
	s.push_back(CUTE(test_input_operator_on_empty_stream_fail));
	s.push_back(CUTE(test_input_operator_called_once_first_word));
	s.push_back(CUTE(test_input_operator_single_word_stream_good));
	s.push_back(CUTE(test_exercise_example));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
