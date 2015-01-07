#ifndef _NORVIG_SPELLCHECKER_HEADER_H_
#define _NORVIG_SPELLCHECKER_HEADER_H_

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <regex>

namespace Norvig
{
	class SpellChecker
	{
	public:
		void load(const std::string& filename);
		std::string correct(const std::string& word);

	private:
		static std::regex mWordPattern;
		std::unordered_map<std::string, int> mDictionary;

	private:
		void edits(const std::string& word, std::set<std::string>& polyWords);
		void known(const std::string& word, std::unordered_map<std::string, int>& candidates);
		void known_edits2(const std::string& word, std::unordered_map<std::string, int>& candidates);
	};

};

#endif