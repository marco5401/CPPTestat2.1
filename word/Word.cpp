
#include "Word.h"

#include <string>
#include <algorithm>
#include <istream>
#include <ostream>
#include <cctype>
#include <locale>
#include <stdexcept>

namespace word
{
	const std::locale loc{};


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

	bool word::Word::isAccepted(char const c) {

		return std::isalpha(c, loc);
	}

	bool word::Word::isValidWord(const std::string& word) {

		return !word.empty()
				&& std::all_of(std::begin(word), std::end(word),
				static_cast<int(*)(int)>(std::isalpha));

	}

	std::istream & word::Word::discardInvalidPrefix(std::istream & is) {

		// Skip everything until it fails or the next character is accepted.
		while(is.good() && !std::isalpha(is.peek())) {
			is.ignore();
		}

		return is;
	}

	std::istream & word::Word::read(std::istream & is)
	{
		if(is.eof()) {
			throw std::out_of_range("invalid word");
		}

		discardInvalidPrefix(is);

		std::string readString{};

		while(isAccepted(is.peek())) {
			readString.push_back(is.get());
		}

		if(readString.empty()) {
			is.setstate(std::ios::failbit);
			return is;
		}

		try{
			// Make a temporary word-object
			Word input{readString};

			// overwrite the content of this object (COPY-Constructor!)
			(*this) = input;
			//clear stream, if read was OK
			is.clear();
		} catch(std::out_of_range & e) {
			//set state of istream to false, if read failed
			is.setstate(std::ios::failbit | is.rdstate());
		}
		return is;
	}

	std::ostream & word::Word::print(std::ostream & os) const
	{
		os << word;
		return os;
	}
}
