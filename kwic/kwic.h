
#ifndef KWIC_H_
#define KWIC_H_

#include "Word.h"
#include <iosfwd>
#include <vector>
#include <Word.h>
namespace kwic {

class Kwic {
public:
	void read(std::istream & in);

	void addSentence(std::istream & in);

	void remove();

	void sortedInsert(std::vector<word::Word>);

	void sortVector(std::vector<std::string> v);

	void print(std::ostream & out);

private:
	void printVector(std::ostream & out, std::vector<std::string> v);

};

}



#endif /* KWIC_H_ */
