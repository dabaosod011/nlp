#include "norvig_spellchecker.h"

namespace Norvig
{
	bool sortBySecond(const std::pair<std::string, int>& left, const std::pair<std::string, int>& right) 
	{
		return left.second < right.second;
	}

	std::regex SpellChecker::mWordPattern = std::regex("\\b[a-zA-Z]\\w+\\b");

	void SpellChecker::load(const std::string& filename)
	{
		std::cout << "Loading " <<filename << "..." << std::endl;

		std::ifstream infile(filename);  
		if (infile.is_open())  
		{ 
			std::string content;
			content.assign(std::istreambuf_iterator<char>(infile),std::istreambuf_iterator<char>());
			infile.close();

			std::smatch matchedWords;			
			while(std::regex_search(content, matchedWords, mWordPattern))
			{
				for (auto aWord : matchedWords)
					mDictionary[aWord] +=1;
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

	void SpellChecker::edits(const std::string& word, std::set<std::string>& polyWords)
	{

		//	delete
		for (auto i=0; i<word.size(); i++) 
			polyWords.insert(word.substr(0,i)+word.substr(i+1));

		//	transposition
		for (auto i=0;i<word.size()-1; i++) 
			polyWords.insert(word.substr(0, i) + word[i+1] + word[i] + word.substr(i+2));

		//	replace and insert
		for (char c='a'; c<='z'; c++)
		{
			for (auto i=0; i<word.size(); i++) 
			{
				polyWords.insert(word.substr(0, i) + c + word.substr(i+1));				
				polyWords.insert(word.substr(0, i) + c + word.substr(i));
			}
		}
	}

	void SpellChecker::known(const std::string& word, std::unordered_map<std::string, int>& candidates)
	{
		std::set<std::string>  polyWords;
		this->edits(word, polyWords);
		for (auto it = polyWords.begin(); it != polyWords.end(); ++it )
		{
			for (auto it2 = mDictionary.begin(); it2 != mDictionary.end(); ++it2 )
			{
				if ( it2->first == *it)
				{
					candidates.insert(*it2);
				}
			}
		}
	}

	void SpellChecker::known_edits2(const std::string& word, std::unordered_map<std::string, int>& candidates)
	{
		std::set<std::string>  polyWords;
		this->edits(word, polyWords);

		std::set<std::string>  polyWords_2;
		for (auto it = polyWords.begin(); it != polyWords.end(); ++it )
		{
			polyWords_2.clear();
			this->edits(*it, polyWords_2);

			for (auto it2 = polyWords_2.begin(); it2 != polyWords_2.end(); ++it2)
			{
				for (auto it3 = mDictionary.begin(); it3 != mDictionary.end(); ++it3 )
				{
					if ( it3->first == *it2)
					{
						candidates.insert(*it3);
					}
				}		
			}
		}
	}

	std::string SpellChecker::correct(const std::string& word)
	{
		std::unordered_map<std::string, int> candidates;
		this->known(word, candidates);

		if (mDictionary.count(word) != 0)
			candidates[word] = mDictionary[word];

		if (candidates.size() > 0) 
			return max_element(candidates.begin(), candidates.end(), sortBySecond)->first;

		std::unordered_map<std::string, int> candidates_edit2;
		this->known_edits2(word, candidates_edit2);
		if (candidates_edit2.size() > 0) 
			return max_element(candidates_edit2.begin(), candidates_edit2.end(), sortBySecond)->first;

		return word;
	}

}