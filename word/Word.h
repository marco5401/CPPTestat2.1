/*
 * word.h
 *
 *  Created on: 16.11.2016
 *      Author: marco
 */

#ifndef WORD_H_
#define WORD_H_

#include <string>
#include <iosfwd>

namespace word {

class Word
{
	std::string word;

	public:
	Word() = default;
	explicit Word(std::string const & word);
	explicit Word(std::istream & in);

	std::istream & read(std::istream & is);
	std::ostream & print(std::ostream & os) const;

	bool operator==(const Word & right) const {
		return this->word.compare(right.word) == 0;
	}


	bool operator<(const Word & right) const {
		return this->word.compare(right.word) < 0;
	}


	private:
	bool isAccepted(char const c);
	std::istream & discardInvalidPrefix(std::istream & is);
};

/**
 * I/O Operator overloadings
 */

inline std::istream & operator>>(std::istream & is, Word & word)
{
	return word.read(is);
}

inline std::ostream & operator<<(std::ostream & os, Word const & word)
{
	return word.print(os);
}

inline bool operator!=(const Word & left, const Word & right) {
	return !(left == right);
}

inline bool operator>(const Word & left, const Word & right) {
	return right < left;
}

inline bool operator<=(const Word & left, const Word & right) {
	return !(left > right);
}

inline bool operator>=(const Word & left, const Word & right) {
	return !(left < right);
}

}


#endif /* WORD_H_ */
