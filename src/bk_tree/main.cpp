#include "bk_tree.h"
using namespace std;

int main()
{
	BKTree::BK_Tree bktree;
	bktree.createTree(".\\data.txt");

	while (!std::cin.eof()) 
	{
		std::cout << "please input a word: ";
		std::string word;
		std::cin >> word;
		if (!word.empty())
			std::cout << bktree.correct(word) << std::endl;
	}
}