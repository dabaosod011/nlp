#include "bk_tree.h"

namespace BKTree
{
	bool sortBySecond(const std::pair<std::string, int>& left, const std::pair<std::string, int>& right) 
	{
		return left.second < right.second;
	}

	bool BK_Node::insert(BK_Node *node)
	{
		if( node == NULL )
			return false;

		int distance = editDistance(this->mWord, node->mWord);
		if (distance == 0)
			return false;

		for (auto it = mChildNodes.begin(); it != mChildNodes.end(); it++)
		{
			if ( (*it)->mDistance2Parent == distance )
			{
				return (*it)->insert(node);				
			}
		}

		node->mDistance2Parent = distance;
		mChildNodes.push_back(node);
		return true;
	}

	int BK_Tree::mDistance = 4;

	void BK_Tree::createTree(string filename)
	{
		std::ifstream infile(filename);  
		if (infile.is_open())  
		{ 
			std::string tmpline;
			std::vector<std::string> tmpstrings;
			while (!infile.eof() )  
			{  
				infile >> tmpline;
				std::transform(tmpline.begin(), tmpline.end(), tmpline.begin(), ::tolower);
				split_string(tmpline, tmpstrings);

				for (auto it = tmpstrings.begin(); it != tmpstrings.end(); ++it)
				{
					BK_Node *node = new BK_Node(*it);
					this->insertNode(node);
				}
			}
		}
		else
		{
			std::cout << "Can not open the file: " <<filename << std::endl;
			infile.close();
		}
	}
	
	void BK_Tree::insertNode(BK_Node *node)
	{
		if (mRoot == NULL)
		{
			mRoot = node;
			mTotalNodes++;
			return;
		}

		if (mRoot->insert(node))
			mTotalNodes++;
		else
		{
			//	!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//	memory leak if do not delete here.
			delete node;
		}
	}

	void BK_Tree::destoryTree(BK_Node *node)
	{
		if (node == NULL)
			return;

		for (auto it = node->mChildNodes.begin(); it != node->mChildNodes.end(); it++)
		{
			destoryTree(*it);
		}

		delete node;
	}

	void BK_Tree::findDistanceK(string word, int K, BK_Node *node, std::unordered_map<std::string, int>& candidates)
	{
		if (node == NULL)
			return;

		int distance = editDistance(word, node->mWord);
		if ( distance <= K )
			candidates[node->mWord] = distance;

		for (auto it=node->mChildNodes.begin(); it!=node->mChildNodes.end(); it++)
		{
			if ( (*it)->mDistance2Parent < distance+K && (*it)->mDistance2Parent > distance-K  )
			{
				findDistanceK(word, K, *it, candidates);
			}
		}
	}

	string BK_Tree::correct(string word)
	{
		std::unordered_map<std::string, int> candidates;
		this->findDistanceK(word, mDistance, this->mRoot, candidates);
		if (candidates.size() > 0) 
			return min_element(candidates.begin(), candidates.end(), sortBySecond)->first;

		return word;
	}

	void BK_Tree::suggestion(string word, vector<string> &candidates)
	{
		std::unordered_map<std::string, int> result;
		this->findDistanceK(word, mDistance, this->mRoot, result);
		for(auto it=result.begin(); it!=result.end(); it++)
			candidates.push_back(it->first);
	}

	int editDistance(string word1, string word2) 
	{
		int len1 = word1.size();
		int len2 = word2.size();

		vector<vector<int> > matrix(len1+1,vector<int>(len2+1, 0));

		for (int i=1;i<=len1;i++)
			matrix[i][0]=i;

		for (int i=1;i<=len2;i++)
			matrix[0][i]=i;

		for(int i=0;i<len1;i++)
		{
			for (int j=0;j<len2;j++)
			{                         
				matrix[i+1][j+1] = std::min(matrix[i+1][j], matrix[i][j+1]) + 1;					
				matrix[i+1][j+1] = std::min(matrix[i+1][j+1], matrix[i][j] + (word1[i]!=word2[j] ? 1 : 0) );
			}
		}

		return matrix[len1][len2];
	}

	void split_string(string &str, vector<string> &result)
	{
		result.clear();
		size_t len = str.size();
		size_t pos = 0, pos_begin = 0;

		while (pos < len)
		{
			if (isalpha(str[pos]))
			{
				pos_begin = pos; 
				while ( pos < len && isalpha(str[pos]) )
					pos++;
				result.push_back(str.substr(pos_begin, pos-pos_begin));				
			}

			pos++;
		}
	}

};