#pragma once
//
// Implements the dictionary as Trie tree of words (NOTE, only 26 letters are supported)
//
#include "BoggleDictionary.h"

#include <string>
#include <vector>

namespace boggle {

class BoggleDictionaryTrie : public BoggleDictionary
{
public:
	BoggleDictionaryTrie(void);
	virtual ~BoggleDictionaryTrie(void);

	// return the the size of the largest word added to the dictionary
	virtual unsigned long GetMaxWordSize() const;

	// adds a word to the dictionary
	virtual bool AddWord(std::string& word);

	// attempts to find a word from the dictionary
	// returns TRUE if the word is found in the dictionary
	// set the 'isInvalidWord' when no more word could be found when adding onto this word
	virtual bool SearchForWord(std::string& word, bool& isInvalidWord) const;

protected:
	enum Constants { NUM_ALPHABET = 26 };

	struct CharNode
	{
	public:
		CharNode(char value, bool wordMarker) : m_value(value), m_wordMarker(wordMarker) 
		{
			for(int i = 0; i < NUM_ALPHABET; ++i)
			{
				m_children[i] = NULL;
			}
		}

		~CharNode()
		{
			for(int i = 0; i < NUM_ALPHABET; ++i)
			{
				delete m_children[i];
			}
		}

		const char m_value;
		bool       m_wordMarker;
		CharNode*  m_children[NUM_ALPHABET];

	private:
		// do not allow copying or assignment
		CharNode( const CharNode& ) :  m_value(0), m_wordMarker(false) {}
		CharNode& operator=(const CharNode&) {}
	};

private:
	unsigned long m_wordMaxSize;
	CharNode* m_rootNode;

private:
	// do not allow copying or assignment
	BoggleDictionaryTrie( const BoggleDictionaryTrie& ) {}
	BoggleDictionaryTrie& operator=(const BoggleDictionaryTrie&) {}

};

}; //namespace boggle 