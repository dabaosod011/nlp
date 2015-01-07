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
	_spellcheker.load("D:\\Code\\cpp\\NatureLanguageProcess\\output\\Win32\\Debug\\data.txt");

	std::string word;
	std::cout << "please input a word: ";
	while (std::cin >> word)
	{		
		std::cout << _spellcheker.correct(word) << std::endl;
		std::cout << "please input a word: ";
	}

	system("pause");
}