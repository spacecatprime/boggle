#pragma once
//
// Implements a boggle board in the form of a graph
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "BoggleBoard.h"

namespace boggle {

class BoggleBoardGrid : public BoggleBoard
{
public:
	BoggleBoardGrid(void);
	virtual ~BoggleBoardGrid(void);

	// returns the number of columns on the board
	virtual long GetWidth() const;

	// returns the number of rows on the board
	virtual long GetHeight() const;

	// from a (x,y) coord find all the words that can be found in the supplied dictionary; returns the number of matching words in results
	// 'results' should contain a set of words already found
	virtual size_t FindWordListFrom(long x, long y, const boggle::BoggleDictionary& dictionary, std::set<std::string>& results);

protected:
	virtual bool Create(const BoggleTable& table);

	long m_width;
	long m_height;

	struct Node
	{
		char m_value;
		bool m_visited;

		Node() : m_value('?'), m_visited(false) {}
	};

	std::vector< std::vector<Node> > m_nodeGrid;

	inline Node* GetNodeAt(long x, long y)
	{
		if( y >= 0 && x >= 0 )
		{
			if( y < static_cast<long>(m_nodeGrid.size()) && x < static_cast<long>(m_nodeGrid[0].size()) )
			{
				return &m_nodeGrid[y][x];
			}
		}
		return NULL;
	}

	void TraverseForWords(Node* node, long x, long y, std::string& buffer, const BoggleDictionary& dictionary, std::set<std::string>& results);

private:
	// just to make it clear to not allow copying or assignment
	BoggleBoardGrid( const BoggleBoardGrid& ) {}
	BoggleBoardGrid& operator=(const BoggleBoardGrid&) {}
};

}; // namespace boggle