#include "Word.h"
#include "kwic.h"
#include <set>
#include <iostream>
#include <iterator>
#include <vector>
#include <deque>
#include <algorithm>
#include <sstream>

std::vector<std::string> list{};

void kwic::Kwic::addSentence(std::istream & in)
{
	std::deque<word::Word> deque{};

	while(!in.eof())
	{
		word::Word word{in};
		deque.push_back(word);
	}
	for(unsigned int i = 0; i < deque.size(); i++){
		std::string temp{};

		for(auto it = deque.begin(); it != deque.end(); it++)
		{
			std::ostringstream out{};
			(*it).print(out);
			temp += out.str() + " ";
		}

		list.push_back(temp);
		word::Word w = deque.front();
		deque.pop_front();
		deque.push_back(w);
	}

}

void kwic::Kwic::sortVector(std::vector<std::string> v)
{
	std::sort(v.begin(), v.end());
}

void kwic::Kwic::print(std::ostream & out){
	printVector(out, list);
}

void kwic::Kwic::printVector(std::ostream & out, std::vector<std::string> v)
{
	for(auto it = v.begin(); it != v.end(); it++)
	{
		out << (*it);
	}
}
