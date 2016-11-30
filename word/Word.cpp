
#include "Word.h"

#include <string>
#include <algorithm>
#include <istream>
#include <ostream>
#include <vector>
#include <cctype>
#include <locale>
#include <stdexcept>

namespace word
{
	const std::locale loc{};

	Word::Word(std::string const & word)
		: word{word}
	{
	}

	Word::Word(std::istream & in)
		: word{}
	{
		read(in);
	}

	/**
	 * Checks if the character is one of the accepted ones.
	 */
	bool word::Word::isAccepted(char const c) {

		return std::isalpha(c, loc);
	}

	/**
	 * Call this method to discard invalid prefixes.
	 * If there are no invalid prefixes, this method will just return immediately.
	 */
	std::istream & word::Word::discardInvalidPrefix(std::istream & is) {

		// Skip everything until it fails or the next character is accepted.
		while(!is.fail() && !isAccepted(is.peek())) {
			is.get();
		}

		return is;
	}

	std::istream & word::Word::read(std::istream & is)
	{
		// Bei End of File, mache nichts
		if(is.eof()) {
			throw std::out_of_range("invalid word");
		}

		// Discard everything invalid.
		discardInvalidPrefix(is);

		/* Implementation gemäss Folie 7, Vorlesung 6 */

		std::string readString{};

		// Fill the characters in the string, until one is not accepted.
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
