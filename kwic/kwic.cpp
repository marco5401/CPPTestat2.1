#include "Word.h"
#include "kwic.h"
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <sstream>

std::vector<std::vector<word::Word>> list{};

std::vector<word::Word> kwic::Kwic::readTextLine(std::istream & in)
{
	std::vector<word::Word> textLine{};
	while(!in.eof())
		{
			word::Word word{in};
			textLine.push_back(word);
		}
	return textLine;
}

std::vector<std::vector<word::Word>> kwic::Kwic::createVariatons(std::vector<word::Word> textLine){
	std::vector<std::vector<word::Word>> allVariations{};

	auto it = textLine.begin();

	do{
		allVariations.push_back(textLine);
		//rotate first element to the end
		std::rotate(textLine.begin(), textLine.begin()+1, textLine.end());
	}while(textLine.begin() != it);

	return allVariations;
}

//returns true if first is lexicographically after second or equal
bool kwic::Kwic::compareVectors(std::vector<word::Word> first, std::vector<word::Word> second)
{
	auto firstIt = first.begin();
	auto secondIt = second.begin();

	while(firstIt != first.end() && secondIt != second.end())
	{
		// return the comparision of the first words that are different
		if((*firstIt) != (*secondIt))
		{
			return (*firstIt) >= (*secondIt);
		}
		firstIt++;
		secondIt++;
	}

	//if the vectors have the same words but differ in length
	if(first.size() != second.size())
	{
		return first.size() >= second.size();
	}

	//if the vectors are the same return true
	if((*first.end()) == (*second.end()))
	{
		return true;
	}

	return true;
}

std::vector<std::vector<word::Word>> kwic::Kwic::sortedInsertion(std::vector<std::vector<word::Word>> toInsert)
{
	for(auto elementToInsert = toInsert.begin(); elementToInsert != toInsert.end(); elementToInsert++)
	{
		if(list.size() == 0)
		{
			list.push_back(*elementToInsert);
			elementToInsert++;
		}

		bool notInserted{true};
		for(auto comparisionVector = list.begin(); comparisionVector != list.end(); comparisionVector++)
		{
			//if the vector elementToInsert is before the comparisionVector - insert elementToInsert before it
			if(!compareVectors(*elementToInsert, *comparisionVector))
			{
				list.insert(comparisionVector, *elementToInsert);
				notInserted = false;
				break;
			}
		}

		//If the element has to be inserted on the last position
		if(notInserted)
		{
			list.insert(list.end(), *elementToInsert);
		}
	}

	return list;
}

void kwic::Kwic::addTextLine(std::istream & in)
{
	std::vector<word::Word> textLine{readTextLine(in)};
	std::vector<std::vector<word::Word>> toInsert{createVariatons(textLine)};
	kwic::Kwic::sortedInsertion(toInsert);
}

void kwic::Kwic::print(std::ostream & out)
{
	for(auto it = list.begin(); it != list.end(); it++)
	{
		for(auto itWord = (*it).begin(); itWord != (*it).end(); itWord++)
		{
			out << (*itWord) << " ";
		}
		out << "/n";
	}
}


