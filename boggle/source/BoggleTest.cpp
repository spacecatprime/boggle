// BoggleTest.cpp
//
#include <iostream>
#include <fstream>
#include <memory>
#include <set>
#include <algorithm>
#include <time.h>       // time_t, struct tm, difftime, time, mktime

#include "BoggleDictionaryTrie.h"
#include "BoggleBoardGrid.h"

// forward declare some functions
boggle::BoggleDictionary* LoadBoggleDictionary(const char* const filename);
boggle::BoggleBoard* LoadBoggleBoard(const char* const filename);
int FindBoggleWords(const char* const dictFilename, const char* const boardFilename, const char* const reportFilename);

// ----------------------------------------------------------------------------

int main(const int argc, const char* const argv[])
{
	if (argc != 4)
	{
		std::cerr << "Usage: BoggleTest <dictionary_filename> <board_filename> <output_filename>" << std::endl;
		return -1;
	}

	int ret = 0;
	try
	{
		const char* const dictFilename = argv[1];
		const char* const boardFilename = argv[2];
		const char* const reportFilename = argv[3];
		ret = FindBoggleWords(dictFilename, boardFilename, reportFilename);
	}
	catch(std::exception& exp)
	{
		std::cerr << exp.what() << std::endl;
		ret = -1;
	}
	return ret;
}

// ----------------------------------------------------------------------------

int FindBoggleWords(const char* const dictFilename, const char* const boardFilename, const char* const reportFilename)
{
	// load dictionary file
	std::unique_ptr<const boggle::BoggleDictionary> dictionary(LoadBoggleDictionary(dictFilename));
	if( dictionary.get() == NULL )
	{
		return -1;
	}

	// load board file
	std::unique_ptr<boggle::BoggleBoard> board(LoadBoggleBoard(boardFilename));
	if( board.get() == NULL )
	{
		return -1;
	}	

	// make this file can be used for output
	std::ofstream report;
	report.open(reportFilename);
	if( report.fail() )
	{
		std::cerr << "Can not use output_filename " << reportFilename << " for the report." << std::endl;
		return -1;
	}
	report.clear();

	// to report total time later
	clock_t then = clock();
	
	// for each pos(x,y) find the list of words
	std::set<std::string> results;
	for(auto x = 0; x < board->GetWidth(); ++x )
	{
		for(auto y = 0; y < board->GetHeight(); ++y)
		{
			board->FindWordListFrom(x, y, *dictionary, results);
		}
	}

	// report time in clock ticks spent to find the solution
	std::cout << "Found all words in " << clock() - then << " clock ticks." << std::endl;

	// print the results
	std::cout << "Results:" << std::endl;
	for(auto printIt = results.cbegin(); printIt != results.cend(); ++printIt)
	{
		std::cout << *printIt << std::endl;
		report << *printIt << std::endl;
	}

	report.close();
	std::cout << "Saved output to file " << reportFilename << std::endl;

	return 0;
}

// ----------------------------------------------------------------------------

boggle::BoggleDictionary* LoadBoggleDictionary(const char* const filename)
{
	boggle::BoggleDictionary* dictionary = NULL;

	std::ifstream dictionaryFile(filename);
	if( dictionaryFile.is_open() )
	{
		dictionary = new boggle::BoggleDictionaryTrie();
		auto loadedWords = dictionary->LoadWordStream(dictionaryFile);
		if( loadedWords == 0 )
		{
			delete dictionary;
			dictionary = NULL;
			std::cerr << "The dictionary must have valid words." << std::endl;
		}
		else
		{
			std::cout << "Loaded " << loadedWords << " number of words from " << filename << std::endl;
		}
		dictionaryFile.close();
	}
	else
	{
		std::cerr << "Dictionary could not be loaded." << std::endl;
	}

	return dictionary;
}

// ----------------------------------------------------------------------------

boggle::BoggleBoard* LoadBoggleBoard(const char* const filename)
{
	boggle::BoggleBoard* board = NULL;

	std::ifstream boardFile(filename);
	if( boardFile.is_open() )
	{
		board = new boggle::BoggleBoardGrid();
		if( false == board->LoadBoardFromFile(boardFile) )
		{
			delete board;
			board = NULL;
			std::cerr << "The board was not valid." << std::endl;
		}
		else
		{
			std::cout << "Loaded " << filename << " boggle board." << std::endl;
		}
		boardFile.close();
	}
	else
	{
		std::cerr << "Boggle board could not be loaded." << std::endl;
	}

	return board;
}

