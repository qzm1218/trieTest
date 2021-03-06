#include "trieTest.h"

trie::trie()
{
	root = new trieNode();
}

trie::~trie()
{
}

trieNode* trie::getTrieNode()
{
	return root;
}

void trie::trieInsert(const char *word)
{
	trieNode *location = root;

	while(*word)
	{
		trieNode *tmp = NULL;
		if(location->next[*word-'a'] == NULL)
		{
			tmp = new trieNode();
			location->next[*word-'a'] = tmp;
		}
		location = location->next[*word-'a'];
		word++;
	}
	location->isStr = true;
}

bool trie::trieSearch(char *word)
{
	trieNode *location = root;
	while(*word&&location)
	{
		location = location->next[*word-'a'];
		word++;
	}
	return ((location != NULL)&&(location->isStr));
}

void trie::trieDelete(trieNode *root)
{
	trieNode *location = root;
	for(int j = 0; j < branchNum;j++)
	{
		if(location->next[j] != NULL)
		{
			trieDelete(location->next[j]);
		}
	}
	delete location;
}

bool trie::trieDeleteWord(const char *word)
{
	trieNode *current = root;
	std::stack<trieNode *> nodes;
	while(*word != '\0' && current != 0)
	{
		nodes.push(current);
		current = current->next[*word-'a'];
		word++;
	}
	
	if(current&&current->isStr)
	{
		current->isStr = false;
		while(nodes.size() != 0)
		{
			char c = *(--word);
			current = nodes.top()->next[c-'a'];

			bool isNotValid = true;
			for(int i = 0; i < 26;i++)
			{
				if(current->next[i] != 0)
				{
					isNotValid = false;
				}
			}
			if(current->isStr == 0 && isNotValid)
			{
				delete current;
			}else
			{
				break;
			}
			nodes.top()->next[c-'a'] = 0;
			nodes.pop();
		}
		return true;
	}
}
