//btree.tc
#include "btnode.h"
#include "indbuff.h"
#include "btree.h"
#include <iostream>

const int MaxHeight = 5;
template <class keyType>
BTree<keyType>::BTree(int order, int keySize, int unique)
: Buffer (1+2*order,sizeof(int)+order*keySize+order*sizeof(int)),
	BTreeFile (Buffer), Root (order)
{
	Height = 1;
	Order = order;
	PoolSize = MaxHeight*2;
	Nodes = new BTNode * [PoolSize];
	BTNode::InitBuffer(Buffer,order);
	Nodes[0] = &Root;
}

template <class keyType>
BTree<keyType>::~BTree()
{
	Close();
	delete Nodes;
}

template <class keyType>
int BTree<keyType>::Open (char * name, int mode)
{
	int result;
	result = BTreeFile.Open(name, mode);
	if (!result) return result;
	// load root
	BTreeFile.Read(Root);
	Height = 1; // find height from BTreeFile!
	return 1;
}

template <class keyType>
int BTree<keyType>::Create (char * name, int mode)
{
	int result;
	result = BTreeFile.Create(name, mode);
	if (!result) return result;
	// append root node
	result = BTreeFile.Write(Root);
	Root.RecAddr=result;
	return result != -1;	
}

template <class keyType>
int BTree<keyType>::Close ()
{
	int result;
	result = BTreeFile.Rewind();
	if (!result) return result;
	result = BTreeFile.Write(Root);
	if (result==-1) return 0;
	return BTreeFile.Close();
}


template <class keyType>
int BTree<keyType>::Insert (const keyType key, const int recAddr)
{
	int result; int level = Height-1; 
	int newLargest=0; keyType prevKey, largestKey; 
	BTNode * thisNode=NULL, * newNode= NULL, * parentNode=NULL;
	thisNode = FindLeaf (key);

	// test for special case of new largest key in tree
	if (key > thisNode->LargestKey())
		{newLargest = 1; prevKey=thisNode->LargestKey();}

	result = thisNode -> Insert (key, recAddr);

	// handle special case of new largest key in tree
	if (newLargest)
		for (int i = 0; i<Height-1; i++) 
		{
			Nodes[i]->UpdateKey(prevKey,key);
			if (i>0) Store (Nodes[i]);
		}

	while (result==-1) // if overflow and not root
	{
		//remember the largest key
		largestKey=thisNode->LargestKey();
		// split the node
		newNode = NewNode();
		thisNode->Split(newNode);
		Store(thisNode); Store(newNode);
		level--; // go up to parent level
		if (level < 0) break;
		// insert newNode into parent of thisNode
		parentNode = Nodes[level];
		result = parentNode->UpdateKey
			(largestKey,thisNode->LargestKey());
		result = parentNode->Insert
			(newNode->LargestKey(),newNode->RecAddr);
		thisNode=parentNode;
	}
	Store(thisNode);
	if (level >= 0) return 1;// insert complete
	// else we just split the root
	int newAddr = BTreeFile.Append(Root); // put previous root into file
	// insert 2 keys in new root node
	Root.Keys[0]=thisNode->LargestKey();
	Root.RecAddrs[0]=newAddr;
	Root.Keys[1]=newNode->LargestKey();
	Root.RecAddrs[1]=newNode->RecAddr;
	Root.NumKeys=2; 
	Height++;
	return 1;	
}

template <class keyType>
int BTree<keyType>::Remove (const keyType key, const int recAddr)
{
	int result; int level = Height - 1; 
	int i;
	keyType prevKey, largestKey1, largestKey2;
	int newLargest = 0;
	BTNode* thisNode, * newNode, * parentNode, * nextNode=NULL;

	//������ key �� ���� leafNode�� thisNode�� �Ҵ�
	thisNode = FindLeaf(key);

	largestKey1 = thisNode->LargestKey();
	
	//tree�� ���ο� ���� ū Ű ���� ���� ���, special case
	if (key == thisNode->LargestKey())
		newLargest = 1; prevKey = thisNode->LargestKey();

	//key ���� ����� node ����
	result = thisNode->Remove(key, recAddr);

	//�����Ϸ��� key ���� largest �� �ƴ� ���, node�� key�� �ּ� �̻� ����. 
	if (result != -1 && newLargest == 0)
		Store(thisNode);
	//�����Ϸ��� key ���� largest�� ���, node�� key�� �ּ� �̻� ����. 
	else if (result != -1 && newLargest == 1)
	{
		for (i = 0; i < Height - 1; i++)
		{
			Nodes[i]->UpdateKey(prevKey, thisNode->LargestKey());
			if (i > 0) Store(Nodes[i]);
		}
		Store(thisNode);
	}
	//node�� key�� �ּҺ��� ���� �����ϴ� ���
	else if (result == -1)
	{
		//sibling node�� merge �������� Ȯ��
		for (i = 0; i < Nodes[level - 1]->NumKeys; i++)
		{
			nextNode = Fetch(Nodes[level - 1]->RecAddrs[i]);
			largestKey2 = nextNode->LargestKey();
			if (nextNode->RecAddr == thisNode->RecAddr)
				continue;
			if (nextNode->Merge(thisNode) == 1)
				break;
		}
		//parent node ����
		parentNode = Nodes[level - 1];

		//���� sibling�� �պ�
		if (nextNode->LargestKey() == thisNode->Keys[0])
		{
			//parent node���� ������ node�� �ּҰ� ����
			int temp1, temp2;
			for (i = 0; i < parentNode->NumKeys; i++)
			{
				if ((int)(parentNode->Keys[i]) == largestKey1)
					temp1 = i;
				if ((int)(parentNode->Keys[i]) == largestKey2)
					temp2 = i;
			}
			parentNode->RecAddrs[temp1] = parentNode->RecAddrs[temp2];
			
			//parent node����  ����
			parentNode->Remove(largestKey2, recAddr);
			Store(parentNode);
			Store(nextNode);
		}
		//������ sibling�� �պ�
		else
		{
			//parent node���� ����
			parentNode->Remove(largestKey1, recAddr);
			Store(parentNode);
			Store(nextNode);
		}
	}
	return 1;
}

template <class keyType>
int BTree<keyType>::Search (const keyType key, const int recAddr)
{
	BTNode * leafNode;
	leafNode = FindLeaf (key); 
	return leafNode -> Search (key, recAddr);
}

template <class keyType>
void BTree<keyType>::Print (ostream & stream) 
{
	stream << "BTree of height "<<Height<<" is "<<endl;
	Root.Print(stream);
	if (Height>1)
		for (int i = 0; i<Root.numKeys(); i++)
		{
			Print(stream, Root.RecAddrs[i], 2);
		}
	stream <<"end of BTree"<<endl;
}

template <class keyType>
void BTree<keyType>::Print 
	(ostream & stream, int nodeAddr, int level) 
{
	BTNode * thisNode = Fetch(nodeAddr);
	stream<<"Node at level "<<level<<" address "<<nodeAddr<<' ';
	thisNode -> Print(stream);
	if (Height>level)
	{
		level++;
		for (int i = 0; i<thisNode->numKeys(); i++)
		{
			Print(stream, thisNode->RecAddrs[i], level);
		}
		stream <<"end of level "<<level<<endl;
	}
}

template <class keyType>
BTreeNode<keyType> * BTree<keyType>::FindLeaf (const keyType key)
// load a branch into memory down to the leaf with key
{
	int recAddr, level;
	for (level = 1; level < Height; level++)
	{
		recAddr = Nodes[level-1]->Search(key,-1,0);//inexact search
		Nodes[level]=Fetch(recAddr);
	}
	return Nodes[level-1];
}

template <class keyType>
BTreeNode<keyType> * BTree<keyType>::NewNode ()
{// create a fresh node, insert into tree and set RecAddr member
	BTNode * newNode = new BTNode(Order);
	int recAddr = BTreeFile . Append(*newNode);
	newNode -> RecAddr = recAddr;
	return newNode;
}

template <class keyType>
BTreeNode<keyType> * BTree<keyType>::Fetch(const int recaddr)
{// load this node from File into a new BTreeNode
	int result;
	BTNode * newNode = new BTNode(Order);
	result = BTreeFile.Read (*newNode, recaddr);
	if (result == -1) return NULL;
	newNode -> RecAddr = result;
	return newNode;
}

template <class keyType>
int BTree<keyType>::Store (BTreeNode<keyType> * thisNode)
{
	return BTreeFile.Write(*thisNode, thisNode->RecAddr);
}
