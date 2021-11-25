//textind.cc
#define _CRT_SECURE_NO_WARNINGS
#include "textind.h"
#include <iostream>
#include <string>

TextIndex::TextIndex(int maxKeys, int unique)
	: NumKeys(0), Keys(0), RecAddrs(0)
{
	Init(maxKeys, unique);
}

TextIndex :: ~TextIndex()
{
	delete Keys; delete RecAddrs;
}

int TextIndex::Insert(const char* key, int recAddr)
{
	int i;
	int index = Find(key);
	if (Unique && index >= 0) return 0; // key already in
	if (NumKeys == MaxKeys) return 0; //no room for another key
	for (i = NumKeys - 1; i >= 0; i--)
	{
		if (strcmp(key, Keys[i]) > 0) break; // insert into location i+1
		Keys[i + 1] = Keys[i];
		RecAddrs[i + 1] = RecAddrs[i];
	}
	Keys[i + 1] = _strdup(key);
	RecAddrs[i + 1] = recAddr;
	NumKeys++;
	return 1;
}

int TextIndex::Remove(const char* key)
{
	int index = Find(key);
	if (index < 0) return 0; // key not in index
	for (int i = index; i < NumKeys; i++)
	{
		Keys[i] = Keys[i + 1];
		RecAddrs[i] = RecAddrs[i + 1];
	}
	NumKeys--;
	return 1;
}

int TextIndex::Search(const char* key) const
{
	/*int index = Find (key);
	if (index < 0) return index;
	return RecAddrs[index];
	*/
	int low = 0, mid = 0, compareFlag = 0;
	int high = NumKeys - 1;

	while (low <= high) {
		mid = (low + high) / 2;
		compareFlag = strcmp(key, Keys[mid]);

		if (compareFlag == 0)
			return RecAddrs[mid];
		else if (compareFlag < 0)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
}

void TextIndex::Print(ostream& stream) const
{
	stream << "Text Index max keys " << MaxKeys
		<< " num keys " << NumKeys << endl;
	for (int i = 0; i < NumKeys; i++)
		stream << "\tKey[" << i << "] " << Keys[i]
		<< " RecAddr " << RecAddrs[i] << endl;
}

int TextIndex::FirstRecAddr(const char* key) const
{
	int recAddr = 0;
	char* minKey = NULL;
	strcpy(minKey, key);
	for (int i = 0; i < NumKeys; i++)
	{
		if (strcmp(minKey, Keys[i]) > 0)
		{
			strcpy(minKey, Keys[i]);
			recAddr = i;
		}
	}
	return recAddr;
}

int TextIndex::NextRecAddr(int recAddr) const
{
	return (recAddr + 1);
}

int TextIndex::Find(const char* key) const
{
	for (int i = 0; i < NumKeys; i++)
		if (strcmp(Keys[i], key) == 0) return i;// key found
//		else if (strcmp(Keys[i], key)>0) return -1;// not found
	return -1;// not found
}

int TextIndex::Init(int maxKeys, int unique)
{
	Unique = unique != 0;
	if (maxKeys <= 0)
	{
		MaxKeys = 0;
		return 0;
	}
	MaxKeys = maxKeys;
	Keys = new char* [maxKeys];
	RecAddrs = new int[maxKeys];
	return 1;
}

