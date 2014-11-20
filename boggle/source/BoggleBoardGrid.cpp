#include "BoggleBoardGrid.h"
#include "BoggleDictionary.h"

#include <algorithm>

namespace boggle {

// ----------------------------------------------------------------------------

BoggleBoardGrid::BoggleBoardGrid(void) : m_width(0), m_height(0)
{
}

// ----------------------------------------------------------------------------

BoggleBoardGrid::~BoggleBoardGrid(void)
{
}

// ----------------------------------------------------------------------------

long BoggleBoardGrid::GetWidth() const
{
	return m_width;
}

// ----------------------------------------------------------------------------

long BoggleBoardGrid::GetHeight() const
{
	return m_height;
}

// ----------------------------------------------------------------------------

size_t BoggleBoardGrid::FindWordListFrom(long x, long y, const BoggleDictionary& dictionary, std::set<std::string>& results)
{
	std::string buffer;
	TraverseForWords(GetNodeAt(x, y), x, y, buffer, dictionary, results);
	return results.size();
}

// ----------------------------------------------------------------------------

void BoggleBoardGrid::TraverseForWords(Node* node, long xPos, long yPos, std::string& buffer, const BoggleDictionary& dictionary, std::set<std::string>& results)
{
	VisitMarker<Node> marker(node, buffer);
	
	if( buffer.size() > dictionary.GetMaxWordSize() )
	{
		// word is larger than any in the dictionary
		return;
	}
	// All words must be a minimum of 3 characters in length AND not already found
	else if( buffer.size() > MAX_WORD_SIZE && results.find(buffer) == results.end() )
	{
		bool isInvalidWord = false;
		bool isWordFound = dictionary.SearchForWord(buffer, isInvalidWord);

		if( isInvalidWord )
		{
			// this can not possibly be a valid word, skip the rest of the tries
			return;
		}
		else if( isWordFound )
		{
			results.insert(buffer);
		}
	}

	// search in around the character's grid location
	for( long x = xPos - 1; x <= xPos + 1; ++x )
	{
		for( long y = yPos - 1; y <= yPos + 1; ++y )
		{
			auto next = GetNodeAt(x,y);
			if( next != NULL && !next->m_visited )
			{
				TraverseForWords(next, x, y, buffer, dictionary, results);
			}
		}
	}
}

// ----------------------------------------------------------------------------

bool BoggleBoardGrid::Create(const BoggleTable& table)
{
	// can not load an empty table
	m_height = table.size();
	if( 0 == m_height )
	{
		std::cerr << "Table should have some rows." << std::endl;
		return false;
	}

	// make sure all rows sizes are the same
	m_width = table[0].size();
	if( 0 == m_width )
	{
		std::cerr << "Each row should have some data." << std::endl;
		return false;
	}

	// create new grid and assign node values
	m_nodeGrid.resize(m_height);
	for (long y = 0; y < m_height; ++y)
	{
		if( m_width != static_cast<long>(table[y].size()) )
		{
			std::cerr << "Not all row colSize match in the table!" << std::endl;
			return false;
		}
		// resize each row
		m_nodeGrid[y].resize(m_width);

		// fill out this row
		for(long x = 0; x < m_width; ++x)
		{
			m_nodeGrid[y][x].m_value = table[y][x];
		}
	}

	return true;
}

}; // namespace boggle