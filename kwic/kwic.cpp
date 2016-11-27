#include "Word.h"
#include "kwic.h"
#include <istream>
#include <ostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <sstream>

std::vector<std::vector<word::Word>> list{};

std::vector<word::Word> kwic::Kwic::readSentence(std::istream & in)
{
	std::vector<word::Word> textLine{};
	while(!in.eof())
		{
			word::Word word{in};
			if(in.eof()) break; // HACK this is a workaround because of a /n word that is generated
			textLine.push_back(word);
		}
	return textLine;
}

std::vector<std::vector<word::Word>> kwic::Kwic::createVariatons(std::vector<word::Word> textLine){
	std::vector<std::vector<word::Word>> allVariations{};

	for(unsigned int i = 0; i < textLine.size(); i++){
		allVariations.push_back(textLine);
		//rotate first element to the end
		std::rotate(textLine.begin(), textLine.begin()+1, textLine.end());
	}

	return allVariations;
}

void kwic::Kwic::addTextLine(std::istream & in)
{
	std::vector<word::Word> textLine{readSentence(in)};
	std::vector<std::vector<word::Word>> toInsert{createVariatons(textLine)};
	std::for_each(toInsert.begin(), toInsert.end(), [](std::vector<word::Word> sentence){list.push_back(sentence);});

	std::sort(list.begin(), list.end());
	//sortSentences(list);
}
/*
void kwic::Kwic::sortSentences(std::vector<std::vector<word::Word>> & sentences)
{
	std::sort(sentences.begin(), sentences.end());
}*/

void kwic::Kwic::print(std::ostream & out)
{
	std::for_each(list.begin(), list.end(), [&](std::vector<word::Word> sentence){printSentence(sentence, out);});
}

void kwic::Kwic::printSentence(std::vector<word::Word> sentence, std::ostream & out)
{

	std::copy(sentence.begin(), sentence.end(), std::ostream_iterator<word::Word>{out, " "});
	out << "\n";
}

