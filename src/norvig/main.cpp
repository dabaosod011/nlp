/*
*	http://norvig.com/spell-correct.html
*	http://blog.youxu.info/spell-correct.html
**/

#include <iostream>
#include "norvig_spellchecker.h"

using namespace std;

int main()
{
	Norvig::SpellChecker _spellcheker;
	_spellcheker.load(".\\data.txt");
	
	while (!std::cin.eof()) 
	{
		std::cout << "please input a word: ";
		std::string word;
		std::cin >> word;
		if (!word.empty())
			std::cout << _spellcheker.correct(word) << std::endl;
	}

	system("pause");
}