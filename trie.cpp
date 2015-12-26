#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

const int branchNum = 26;

#define MAX_RECORD_NUM  100
#define MAX_RECOED_SIZE 256

static char buf[MAX_RECORD_NUM][MAX_RECOED_SIZE] = {0};
struct trieNode
{
	bool isStr;
	struct trieNode *next[branchNum];
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
	int loadFile(const char *filename);

public:
	trieNode *root;
};

trie::trie()
{
	root = new trieNode();
}

trie::~trie()
{
}

void trie::trieInsert(const char *word)
{
	trieNode *location = root;
	while(*word)
	{
		if(location->next[*word-'a'] == NULL)
		{
			trieNode *tmp = new trieNode();
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
	while(*word && location)
	{
		location = location->next[*word-'a'];
		word++;
	}
	return (location != NULL && location->isStr );
}

void trie::trieDelete(trieNode *root)
{
	for(int i = 0; i < branchNum; i++)
	{
		if(root->next[i] != NULL)
		{
			trieDelete(root->next[i]);
		}
	}
	delete root;
}

int trie::loadFile(const char *filename)
{
	FILE *fp = fopen(filename, "r");
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	
	if(!fp)
	{
		printf("Open file[%s] failed.\n",filename);
		return -1;	
	}

	int index = 0;
	while(((read = getline(&line, &len, fp)) != -1) && line)
	{
		line[read-1] = '\0';
	//	printf("line : %s \n",line);
		if(index > MAX_RECORD_NUM)
		{
			printf("array is full.\n");
			break;
		}
		//*ppBuf = (char *)malloc(100);
	//	printf("before insert : %s(%d) \n", line, read-1);
		memcpy(buf[index++], line, read-1);
	}

	if(line)
	{
		free(line);
	}

	return index;
}

int main(int argc, char *argv[])
{
#if 1
	trie t;
	if(!argv[1])
	{
		printf("Please input files...\n");
		return 0;
	}
	int num = t.loadFile(argv[1]);
	for(int j = 0; j < num ; j++)
	{
		t.trieInsert(buf[j]);
	}
//	printf("sizeof trieNode %d \n",sizeof(trieNode));
//	printf("bool sizeof : %d \n",sizeof(bool));
//	printf("sizeof struct trieNode * : %d \n",sizeof(struct trieNode *));
//	printf("int %d int * %d char * %d long %d long * %d void %d\n",sizeof(int), sizeof(int *),sizeof(char *),sizeof(long),sizeof(long *), sizeof(void *));
//	printf("class trie %d \n", sizeof(trie));
#endif
#if 0
	trie t;
	t.trieInsert("a");
	t.trieInsert("abandon");
	char *c = "abandoned";
	t.trieInsert(c);
	t.trieInsert("abashed");
#endif
	if(!argv[2])
	{
		printf("Search Word is Null.\n");
		t.trieDelete(t.root);
		return 0;
	}
	if(t.trieSearch(argv[2]))
	{
		printf("find it.\n");
	}
	t.trieDelete(t.root);
	return 0;
}
