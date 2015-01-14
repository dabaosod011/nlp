#ifndef _BKTREE_SPELLCHECKER_HEADER_H_
#define _BKTREE_SPELLCHECKER_HEADER_H_

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <boost/timer/timer.hpp>

using namespace std;

namespace BKTree
{
	class BK_Node
	{
	public:
		string mWord;
		int mDistance2Parent;
		std::list<BK_Node* > mChildNodes;

	public:
		BK_Node(string word_):mWord(word_), mDistance2Parent(-1)
		{
			mChildNodes.clear();
		}
	public:
		bool insert(BK_Node *node);
	};

	class BK_Tree
	{
	public:
		BK_Tree() : mRoot(NULL), mTotalNodes(0) {};
		~BK_Tree()
		{
			this->destoryTree(mRoot);
		}
	public:
		void createTree(string filename);
		string correct(string word);
		void suggestion(string word, vector<string> &candidates);

		size_t getTotalNodes()
		{
			return mTotalNodes;
		}

	public:
		static int mDistance;

	private:
		BK_Node *mRoot;
		size_t mTotalNodes;

	private:
		bool insertNode(BK_Node *node);
		void findDistanceK(string word, int K, BK_Node *node, unordered_map<string, int>& candidates);		
		void destoryTree(BK_Node *node);
	};

	inline int editDistance(string word1, string word2);
	inline void split_string(string &str, vector<string> &result);
};

#endif