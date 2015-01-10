#ifndef _BKTREE_SPELLCHECKER_HEADER_H_
#define _BKTREE_SPELLCHECKER_HEADER_H_

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <regex>
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
		size_t getTotalNodes()
		{
			return mTotalNodes;
		}

	private:
		BK_Node *mRoot;
		size_t mTotalNodes;
		static std::regex mWordPattern;

	private:
		void insertNode(BK_Node *node);
		void findDistanceK(string word, int K, BK_Node *node, std::unordered_map<std::string, int>& candidates);		
		void destoryTree(BK_Node *node);
	};

	inline int editDistance(string word1, string word2);
};

#endif