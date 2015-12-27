#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>

using namespace std;

const int branchNum = 26;

struct trieNode
{
	bool isStr;
	trieNode *next[branchNum];
	trieNode():isStr(false)
	{
		memset(next, NULL, sizeof(next));
	}
};


class trie
{
public:
	trie();
	~trie();
	void trieInsert(const char *word);
	bool trieSearch(char *word);
	void trieDelete(trieNode *root);
	trieNode* getTrieNode();
	bool trieDeleteWord(const char *word);
private:
	trieNode *root;
};

