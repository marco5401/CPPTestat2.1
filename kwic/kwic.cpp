#include "Word.h"
#include "kwic.h"
#include <set>
#include <iostream>
#include <iterator>
#include <vector>
#include <deque>
#include <algorithm>

std::vector<std::vector<word::Word>> list{};

void kwic::Kwic::addSentence(std::istream & in)
{
	std::deque<word::Word> deque{};
	while(!in.eof())
	{
		word::Word word{};
		in >> word;
//		in >> word;
		deque.push_back(word);
	}
	for(unsigned int i = 0; i < deque.size(); i++){
		std::vector<word::Word> temp;

		std::copy(deque.begin(), deque.end(), std::back_inserter(temp));

		list.push_back(temp);
		word::Word w = deque.front();
		deque.pop_front();
		deque.push_back(w);
	}

}
