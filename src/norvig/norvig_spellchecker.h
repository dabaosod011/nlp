#ifndef _NORVIG_SPELLCHECKER_HEADER_H_
#define _NORVIG_SPELLCHECKER_HEADER_H_

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <boost/timer/timer.hpp>

using namespace std;
/*
*	http://norvig.com/spell-correct.html
*	http://blog.youxu.info/spell-correct.html
**/

namespace Norvig
{
	class SpellChecker
	{
	public:
		void load(const string& filename);
		string correct(const string& word);
		void suggestion(string word, vector<string> &candidates);

		size_t getDictionarySize()
		{
			return mDictionary.size();
		}

	private:
		std::unordered_map<string, int> mDictionary;

	private:
		void edits(const string& word, std::set<string>& polyWords);
		void known(const string& word, std::unordered_map<string, int>& candidates);
		void known_edits2(const string& word, std::unordered_map<string, int>& candidates);
	};

	inline void split_string(string &str, std::vector<string> &result);
};

#endif