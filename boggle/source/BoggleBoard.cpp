#include "BoggleBoard.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

namespace boggle {

BoggleBoard::BoggleBoard(void)
{
}


BoggleBoard::~BoggleBoard(void)
{
}

bool BoggleBoard::LoadBoardFromFile(std::ifstream& stream)
{
	if( false == stream.is_open() )
	{
		return false;
	}

	using namespace std;

	BoggleTable table;
	const size_t LINE_SIZE = 256;
	char line[LINE_SIZE];

	while( stream.getline(line, sizeof(line)-1) )
	{
		// find all the letters that could be seperated by whitespace or not
		vector<string> tokens;
		istringstream stream(line);
		copy(istream_iterator<string>(stream),
		     istream_iterator<string>(),
		     back_inserter(tokens));

		// create each row
		vector<char> row;

		for(auto it = tokens.cbegin(); it != tokens.cend(); ++it )
		{
			const string& rowData (*it);
			for(auto charIt = rowData.begin(); charIt != rowData.end(); ++charIt)
			{
				//  find invalid char values (should be a-z|A-Z)
				int charVal = tolower(static_cast<int>(*charIt));
				if( charVal >= static_cast<int>('a') && charVal <= static_cast<int>('z') )
				{
					row.push_back(static_cast<char>(charVal));
				}
				else
				{
					std::cerr << "WARN: The char value of " << charVal << " is not a value from a-z." << std::endl;
				}
			}
		}

		// save off the row
		table.push_back(row);
	}

	if( table.empty() )
	{
		std::cerr << "WARN: The table for the board could not be loaded. Ended up empty." << std::endl;
		return false;
	}
	return Create(table);
}

}; // namespace boggle
