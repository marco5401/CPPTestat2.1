#include "Word.h"
#include "kwic.h"

#include <iterator>
#include <vector>
#include <algorithm>
#include <sstream>
#include <set>
#include <string>

using word::Word;
using line = std::vector<Word>;
using sorted_lines = std::set<line>;
using unsorted_lines = std::vector<line>;

unsorted_lines readLines(std::istream & in)
{
	unsorted_lines all_input_lines{};
	std::string input_line{};
	while(std::getline(in, input_line))
	{
		std::istringstream line_stream{input_line};
		std::istream_iterator<Word> word_it{line_stream}, eof{};
		all_input_lines.push_back(line{word_it, eof});
	}
	return all_input_lines;
}

sorted_lines rotate_lines(unsorted_lines const & input_lines)
{
	sorted_lines rotated_lines{};
	for_each(begin(input_lines), end(input_lines), [&](line line_to_rotate) {
		for (auto it = begin(line_to_rotate); it != end(line_to_rotate); it++) {
			line rotated_line{line_to_rotate.size()};
			std::rotate_copy(
					std::begin(line_to_rotate), it, std::end(line_to_rotate),
					std::begin(rotated_line));
				rotated_lines.insert(rotated_line);
		}
	});
	return rotated_lines;
}

void kwic::kwic(std::istream & input, std::ostream & output)
{
	unsorted_lines input_lines = readLines(input);
	sorted_lines rotated_lines = rotate_lines(input_lines);
	std::copy(
			std::begin(rotated_lines),
			std::end(rotated_lines),
			std::ostream_iterator<line>{output, "\n"});
}

namespace word
{
	std::ostream & operator<<(std::ostream & os, line const & l)
	{
		std::copy(
				std::begin(l), std::end(l),
				std::ostream_iterator<Word>{os, " "});
		return os;
	}
}