#include "Word.h"
#include "kwic.h"
#include <istream>
#include <ostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <sstream>
#include <set>
#include <string>

using word::Word;
using line = std::vector<Word>;

std::vector<line> readLines(std::istream & in)
{
	std::vector<line> allInputLines{};
	std::string input{};
	while(std::getline(in, input))
		{
			std::istringstream lineStream{input};
			std::istream_iterator<Word> wordIt{lineStream}, eof{};
			allInputLines.push_back(line{wordIt, eof});				//Vector constructor is overloaded with a iterator range
		}
	return allInputLines;
}

std::set<line> rotateLines(std::vector<line> const & inputLines)
{
	std::set<line> rotatedLines{};
	for_each(inputLines.begin(), inputLines.end(), [&](line lineToRotate)
	{
		for (auto it = lineToRotate.begin(); it != lineToRotate.end(); it++)
		{
			line rotated_line{lineToRotate.size()};
			std::rotate_copy( std::begin(lineToRotate), it, std::end(lineToRotate), std::begin(rotated_line));
		}
	});
	return rotatedLines;
}



void kwic::kwic(std:: istream & in, std::ostream & out)
{
	std::vector<line> inputLines = readLines(in);
	std::set<line> rotatedLines = rotateLines(inputLines);
	std::copy(
			std::begin(rotatedLines),
			std::end(rotatedLines),
			std::ostream_iterator<line>{out, "\n"});
}

namespace word {
	std::ostream & operator<<(std::ostream & os, line const & l) {
		std::copy(
				std::begin(l), std::end(l),
				std::ostream_iterator<Word>{os, " "});
		return os;
	}
}
