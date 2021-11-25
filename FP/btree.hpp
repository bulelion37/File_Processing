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

	//삭제할 key 값 갖는 leafNode를 thisNode에 할당
	thisNode = FindLeaf(key);

	largestKey1 = thisNode->LargestKey();
	
	//tree에 새로운 가장 큰 키 값이 들어온 경우, special case
	if (key == thisNode->LargestKey())
		newLargest = 1; prevKey = thisNode->LargestKey();

	//key 값이 저장된 node 삭제
	result = thisNode->Remove(key, recAddr);

	//삭제하려는 key 값이 largest 가 아닌 경우, node에 key가 최소 이상 존재. 
	if (result != -1 && newLargest == 0)
		Store(thisNode);
	//삭제하려는 key 값이 largest인 경우, node에 key가 최소 이상 존재. 
	else if (result != -1 && newLargest == 1)
	{
		for (i = 0; i < Height - 1; i++)
		{
			Nodes[i]->UpdateKey(prevKey, thisNode->LargestKey());
			if (i > 0) Store(Nodes[i]);
		}
		Store(thisNode);
	}
	//node에 key의 최소보다 적게 존재하는 경우
	else if (result == -1)
	{
		//sibling node를 merge 가능한지 확인
		for (i = 0; i < Nodes[level - 1]->NumKeys; i++)
		{
			nextNode = Fetch(Nodes[level - 1]->RecAddrs[i]);
			largestKey2 = nextNode->LargestKey();
			if (nextNode->RecAddr == thisNode->RecAddr)
				continue;
			if (nextNode->Merge(thisNode) == 1)
				break;
		}
		//parent node 저장
		parentNode = Nodes[level - 1];

		//왼쪽 sibling과 합병
		if (nextNode->LargestKey() == thisNode->Keys[0])
		{
			//parent node에서 삭제된 node의 주소값 갱신
			int temp1, temp2;
			for (i = 0; i < parentNode->NumKeys; i++)
			{
				if ((int)(parentNode->Keys[i]) == largestKey1)
					temp1 = i;
				if ((int)(parentNode->Keys[i]) == largestKey2)
					temp2 = i;
			}
			parentNode->RecAddrs[temp1] = parentNode->RecAddrs[temp2];
			
			//parent node에서  삭제
			parentNode->Remove(largestKey2, recAddr);
			Store(parentNode);
			Store(nextNode);
		}
		//오른쪽 sibling과 합병
		else
		{
			//parent node에서 삭제
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
