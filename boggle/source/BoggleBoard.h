#pragma once
//
// An interface to a boggle board
//
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>

namespace boggle {

class BoggleDictionary;

// Board:
//  The board file is an ASCII text file that is 4 lines of 4 characters.  
//  These represent the game board, a 4x4 matrix of characters.  
//  These may be mixed case.
//  Whitespace is optional and should be ignored.  Only letters 'a' to 'z' or 'A' to 'Z' are used.
class BoggleBoard
{
public:
	BoggleBoard(void);
	virtual ~BoggleBoard(void) = 0;

	// returns the number of columns on the board
	virtual long GetWidth() const = 0;

	// returns the number of rows on the board
	virtual long GetHeight() const = 0;

	// from a (x,y) coord find all the words that can be found in the supplied dictionary; returns the number of matching words in results
	// 'results' should contain a set of words already found
	virtual size_t FindWordListFrom(long x, long y, const BoggleDictionary& dictionary, std::set<std::string>& results) = 0;

	// sets up the boggle board from a file
	virtual bool LoadBoardFromFile(std::ifstream& stream);

protected:

	enum Contants { MAX_WORD_SIZE = 2 };

	// derived classes must create the table data 
	typedef std::vector< std::vector<char> > BoggleTable;
	virtual bool Create(const BoggleTable& table) = 0;

	// helper class to help traverse the graph
	template <typename T> 
	struct VisitMarker
	{ 
		T* m_node;
		std::string& m_buffer;
		bool isQ;

		VisitMarker(T* node, std::string& buffer) : m_node(node), m_buffer(buffer), isQ(false)
		{
			m_node->m_visited = true;
			m_buffer.push_back(m_node->m_value);

			if( m_node->m_value == 'q' )
			{
				m_buffer.push_back('u');
				isQ = true;
			}
		}
		~VisitMarker()
		{
			m_node->m_visited = false;
			if( isQ )
			{
				m_buffer.pop_back();
				m_buffer.pop_back();
			}
			else
			{
				m_buffer.pop_back();
			}
		}

	private:
		VisitMarker(const VisitMarker&) {}
		VisitMarker& operator=(const VisitMarker&) {}
	}; 

private:
	// just to make it clear to not allow copying or assignment
	BoggleBoard( const BoggleBoard& ) {}
	BoggleBoard& operator=(const BoggleBoard&) {}
};

}; // namespace boggle 