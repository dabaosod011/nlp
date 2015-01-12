#include "norvig_spellchecker.h"

#define DATA_TRAIN ".\\data_train.txt"
#define DATA_TEST ".\\data_test.txt"

int main()
{
	Norvig::SpellChecker norvig_spellcheker;
	int numTotal = 0;
	int numCorrect = 0;
	boost::timer::cpu_timer timer; 
	boost::timer::cpu_times time;
	
	std::cout<<"Loading train data..." << std::endl;
	timer.start();		
	norvig_spellcheker.load(DATA_TRAIN);
	time = timer.elapsed();
	std::cout << "Used time: " << time.wall/1000000000.0L << "s" << std::endl;
	std::cout << "The size of mDictionary is: " << norvig_spellcheker.getDictionarySize() << std::endl;

	timer.stop();
	timer.start();
	std::cout << "Running the test" << std::endl;
	std::ifstream infile(DATA_TEST);  
	if (infile.is_open())
	{ 
		std::string tmpline;
		std::string word, expect/*, predict*/;
		std::vector<std::string> candidates;
		while (!infile.eof() )  
		{ 
			infile >> tmpline;
			std::transform(tmpline.begin(), tmpline.end(), tmpline.begin(), ::tolower);
			size_t pos = tmpline.find("->");
			if(pos != std::string::npos)
			{
				word = tmpline.substr(0, pos);
				expect = tmpline.substr(pos+2);
				//predict = norvig_spellcheker.correct(word);
				//std::cout << "Checking " << word << ", expect: " << expect << ", result: " << predict << std::endl;
				candidates.clear();
				norvig_spellcheker.suggestion(word, candidates);
				numTotal++;
				if( std::find(candidates.begin(), candidates.end(), expect) != candidates.end() )
					numCorrect++;
				else
					std::cout << "Can not find " << expect << " for " <<  word << std::endl;
			}
		}
	}
	time = timer.elapsed();
	std::cout << "Used time: " << time.wall/1000000000.0L << "s" <<std::endl;
	std::cout << "Correct ratio of norvig = " << numCorrect << "/" << numTotal <<std::endl;

	system("pause");
	return 0;
}