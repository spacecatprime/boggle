#include "BoggleDictionary.h"

#include <algorithm> 
#include <cctype>
#include <fstream>
#include <functional> 
#include <iostream>
#include <locale>
#include <string>

namespace // utility functions
{
	// trim whitespace from start
	inline std::string& left_trim(std::string& s) 
	{
		s.erase( s.begin(), 
			     std::find_if( s.begin(), 
				               s.end(), 
							   std::not1(std::ptr_fun<int, int>(std::isspace) )));
		return s;
	}

	// trim whitespace from end
	inline std::string& right_trim(std::string& s) 
	{
		s.erase( std::find_if( s.rbegin(), 
			                   s.rend(), 
							   std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
			     s.end());
		return s;
	}

	// trim whitespace from both sides
	inline std::string& trim(std::string& s) 
	{
		return left_trim( right_trim(s) );
	}

	// determine if all characters are alphabet values
	inline bool is_all_alpha(std::string& s)
	{
		return std::find_if( s.begin(), 
			                 s.end(), 
							 std::not1(std::ptr_fun<int, int>(std::isalpha)) ) == s.end();
	}
};

namespace boggle {

BoggleDictionary::BoggleDictionary(void)
{
}

BoggleDictionary::~BoggleDictionary(void)
{
}

unsigned long BoggleDictionary::LoadWordStream(std::ifstream& stream)
{
	unsigned long numLoaded = 0;

	if( stream.is_open() )
	{
		const size_t LINE_SIZE = 256;
		char line[LINE_SIZE];

		// Boggle must have words larger than 2
		const size_t MIN_WORD_SIZE = 2;

		while( stream.getline(line, sizeof(line)-1) )
		{
			std::string word(line);
			std::transform(word.begin(), word.end(), word.begin(), (int(*)(int))std::tolower);
			trim(word);

			if( word.size() <= MIN_WORD_SIZE )
			{
				std::cerr << "WARN: Skipping small word:" << word << std::endl;
			}
			else if( is_all_alpha(word) )
			{
				if( AddWord(word) )
				{
					++numLoaded;
				}
			}
			else
			{
				std::cerr << "WARN: Found non-alpha dictionary word:" << word << std::endl;
			}
		}
	}

	return numLoaded;
}

}; // namespace boggle