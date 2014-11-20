#pragma once
//
// An interface to the dictionary of words for the boggle test
//
#include <iostream>
#include <fstream>
#include <string>

namespace boggle {

class BoggleDictionary
{
public:
	BoggleDictionary(void);
	virtual ~BoggleDictionary(void) = 0;

	// return the the size of the largest word added to the dictionary
	virtual unsigned long GetMaxWordSize() const = 0;

	// adds a word to the dictionary
	virtual bool AddWord(std::string& word) = 0;

	// attempts to find a word from the dictionary
	// returns TRUE if the word is found in the dictionary
	// set the 'isInvalidWord' when no more word could be found when adding onto this word
	virtual bool SearchForWord(std::string& word, bool& isInvalidWord) const = 0;

	// loads a file of words per line and calls AddWord per word to dictionary; returns the number of words loaded
	// Notes:
	//  The dictionary file is an ASCII text file that lists acceptable words.  Each word is
	//  new line separated.  Words are in alphabetical order and all lowercase, utilizing
	//  only letters 'a' to 'z'.
	virtual unsigned long LoadWordStream(std::ifstream& stream);

private:
	// just to make it clear to not allow copying or assignment
	BoggleDictionary( const BoggleDictionary& ) {}
	BoggleDictionary& operator=(const BoggleDictionary&) {}
};

}; // namespace boggle 