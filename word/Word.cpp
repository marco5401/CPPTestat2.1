
#include "Word.h"

#include <string>
#include <algorithm>
#include <istream>
#include <ostream>
#include <cctype>
#include <stdexcept>

namespace word
{
	Word::Word(std::string const & word)
		: word{word}
	{
		if(!isValidWord(word)) {
			throw std::invalid_argument("invalid word");
		}
	}

	Word::Word(std::istream & in)
		: word{}
	{
		read(in);
	}

	bool word::Word::isValidWord(const std::string& word) {

		return !word.empty() &&
				std::all_of(
						std::begin(word),
						std::end(word),
						static_cast<int(*)(int)>(std::isalpha)); // Pointer auf Funktion mit int Return und int Param.
	}

	std::istream & word::Word::read(std::istream & is)
	{
		if(is.eof()) {
			throw std::out_of_range("invalid word");
		}

		// Discard invalid prefix
		while(is.good() && !std::isalpha(is.peek())) {
			is.ignore();
		}

		std::string buffer{};

		while(is.good() && std::isalpha(is.peek())) {
			buffer += is.get();
		}

		if(isValidWord(buffer)){
			word = buffer;
		} else {
			is.setstate(std::ios_base::failbit);
			return is;
		}

		return is;
	}

	std::ostream & word::Word::print(std::ostream & os) const
	{
		os << word;
		return os;
	}
}
