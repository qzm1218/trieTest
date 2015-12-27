#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>
#include "trieTest.h"

int main(int argc, char *argv[])
{
	trie t;
	t.trieInsert("abefgdgihgdigidhgidhgjkfgh");
	t.trieInsert("bcd");
	t.trieInsert("def");
	t.trieInsert("cdef");
	t.trieInsert("befg");
	t.trieInsert("fghi");
	t.trieInsert("bcd");
	t.trieInsert("abcd");

	if(argc != 2)
	{
		printf("Please input Find word.\n");
		return -1;
	}
	if(t.trieSearch(argv[1]))
	{
		printf("find it \n");
		t.trieDeleteWord(argv[1]);
		if(!t.trieSearch(argv[1]))
		{
			printf("delete word successful.\n");
		}
	}
	t.trieDelete(t.getTrieNode());
	return 0;
}
