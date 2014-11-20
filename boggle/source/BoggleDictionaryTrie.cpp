#include "BoggleDictionaryTrie.h"

#include <algorithm>

namespace boggle {

	// ----------------------------------------------------------------------------

BoggleDictionaryTrie::BoggleDictionaryTrie(void) : m_wordMaxSize(0) , m_rootNode(NULL)
{
	m_rootNode = new CharNode(' ', false);
}

// ----------------------------------------------------------------------------

BoggleDictionaryTrie::~BoggleDictionaryTrie(void)
{
	delete m_rootNode;
	m_rootNode = NULL;
}

// ----------------------------------------------------------------------------

unsigned long BoggleDictionaryTrie::GetMaxWordSize() const
{
	return m_wordMaxSize;
}

// ----------------------------------------------------------------------------

bool BoggleDictionaryTrie::AddWord(std::string& word)
{
	if( word.empty() )
	{
		return true;
	}

	auto currentNode = m_rootNode;

	for(size_t i = 0; i < word.size(); ++i)
	{
		// find relative letter index from a-z
		char currentChar(word[i]);
		int index = currentChar - 'a';
		if( index < 0 || index >= NUM_ALPHABET )
		{
			std::cerr << "Adding word with invalid character value:" << word << std::endl;
			return false;
		}

		if( currentNode->m_children[index] != NULL )
		{
			// traverse down character nodes
			currentNode = currentNode->m_children[index];
		}
		else
		{
			// create new character
			CharNode* newNode = new CharNode(currentChar, false);
			currentNode->m_children[index] = newNode;
			currentNode = newNode;
		}
		if( i == word.size() - 1 )
		{
			currentNode->m_wordMarker = true;
		}
	}

	if( word.length() > m_wordMaxSize )
	{
		m_wordMaxSize = word.length();
	}
	return true;
}

// ----------------------------------------------------------------------------

bool BoggleDictionaryTrie::SearchForWord(std::string& word, bool& isInvalidWord) const
{
	// be positive about the progress
	isInvalidWord = false;

	const CharNode* currentNode = m_rootNode;
	for(auto wordIt = word.begin(); wordIt != word.end(); ++wordIt )
	{
		char currentChar (*wordIt);
		int index = currentChar - 'a';
		if( index < 0 || index >= NUM_ALPHABET )
		{
			std::cerr << "Trying to index an invaild range in word:" << word << std::endl;
			isInvalidWord = true;
			return false;
		}
		if( NULL == currentNode->m_children[index] )
		{
			isInvalidWord = true;
			return false;
		}
		else
		{
			currentNode = currentNode->m_children[index];
		}
	}
	return currentNode->m_wordMarker;
}

}; // namespace boggle 