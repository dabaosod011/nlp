#include "bk_tree.h"

namespace BKTree
{
	std::regex BK_Tree::mWordPattern = std::regex("\\b[a-zA-Z]\\w+\\b");
	
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

	void BK_Tree::createTree(string filename)
	{
		std::ifstream infile(filename);  
		if (infile.is_open())  
		{ 
			std::string content;
			content.assign(std::istreambuf_iterator<char>(infile),std::istreambuf_iterator<char>());
			infile.close();

			std::smatch matchedWords;
			string tmpword;
			while(std::regex_search(content, matchedWords, mWordPattern))
			{
				for (auto aWord : matchedWords)
				{
					tmpword = matchedWords.str();
					std::transform(tmpword.begin(), tmpword.end(), tmpword.begin(), ::tolower);
					BK_Node *node = new BK_Node(tmpword);
					this->insertNode(node);
				}
				content = matchedWords.suffix().str();				
			}
		}
		else
		{
			std::cout << "Can not open the file: " <<filename << std::endl;
			infile.close();
			return ;
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
		this->findDistanceK(word, 2, this->mRoot, candidates);
		if (candidates.size() > 0) 
			return min_element(candidates.begin(), candidates.end(), sortBySecond)->first;

		return word;
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

};