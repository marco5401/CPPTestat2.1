
#ifndef KWIC_H_
#define KWIC_H_

#include "Word.h"
#include <iosfwd>
namespace kwic {

class Kwic {
public:
	void read(std::istream & in);

	void addSentence(std::istream & in);

	void remove();


};

}



#endif /* KWIC_H_ */
