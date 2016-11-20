
#ifndef KWIC_H_
#define KWIC_H_

#include "Word.h"
#include <iosfwd>
#include <vector>
#include <Word.h>
namespace kwic {

class Kwic {
public:
	std::vector<word::Word> readTextLine(std::istream & in);

	std::vector<std::vector<word::Word>> createVariatons(std::vector<word::Word>);

	bool compareVectors(std::vector<word::Word> first, std::vector<word::Word> second);

	std::vector<std::vector<word::Word>> sortedInsertion(std::vector<std::vector<word::Word>>);

	void addTextLine(std::istream & in);

	void print(std::ostream & out);

};

}



#endif /* KWIC_H_ */
