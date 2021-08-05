#ifndef MAIN_CPP
#define MAIN_CPP

#include <string>
#include <iostream>
#include <vector>
#include "basic.cpp"

struct wordOccurences
{
	std::string word;
	int occurences;
}

struct previousWords
{
	std::string word;
	std::vector <wordOccurences> previousWords;
};

struct wordProbabiliy
{
	std::string previousWord;
	std::string nextWord;
	float probability;
}

bool validInput(const std::string userInput)
{
	if(stringContainsNumbers(userInput)) return 0;
	return 1;
}

std::vector <std::string> divideIntoWords(const std::string userInput)
{
	std::vector <std::string> words;
	int inputLength = userInput.length();
	int wordLength = 0;
	for(int i = 0; i < inputLength; i++)
	{
		if(userInput.at(i) == ' ')
		{
			words.push_back(userInput.substr(i - wordLength, wordLength));
			wordLength = 0;
		}else wordLength++;
		
		if(i + 1 == inputLength)
		{
			words.push_back(userInput.substr(i - wordLength + 1, wordLength + 1));
			wordLength = 0;
		}
	}
	return words;
}

int wordRepeats(const std::vector <previousWords> wordsList, const std::string word)
{
	int wordsSize = wordsList.size();
	for(int i = 0; i < wordsSize; i++)
	{
		if(wordsList.at(i).word == word) return i;
	}
	return -1;
}

bool alreadyExists(const std::vector <previousWords> wordsList, const std::string s)
{
	for(unsigned int i = 0; i < wordsList.size(); i++)
	{
		if(s == wordsList.previousWOrds
	}
}

std::vector <previousWords> getWordsAndTheirPrevious(const std::vector <std::string> words)
{
	std::vector <previousWords> wordsList;
	int wordsSize = words.size();
	for(int i = 1; i < wordsSize; i++)
	{
		previousWords temp;
		temp.word = words.at(i);
		wordOccurences tempTwo;
		tempTwo.word = words.at(i - 1));
		tempTwo.occurences = 1;
		temp.previousWords.push_back(tempTwo);
		int position = wordRepeats(wordsList, temp.word);
		if(position == -1)
		{
			wordsList.push_back(temp);
		}else
		{
			
			wordsList.at(position).previousWords.push_back(temp.previousWords.at(0));
		}
	}
	return wordsList;
}

void printPreviousWord(const previousWords word)
{
	std::cout << "The word is \"" << word.word << "\" Words before it are: " << std::endl;
	for(unsigned int i = 0; i < word.previousWords.size(); i++)
	{
		print(word.previousWords.at(i));
	}
}


void printPreviousWordsVector(const std::vector <previousWords> v)
{
	for(unsigned int i = 0; i < v.size(); i++)
	{
		printPreviousWord(v.at(i));		
	}
}

std::vector <wordProbability> getWordProbability(const std::vector <previousWords> wordsList)
{
	std::vector <wordProbability> probalityVector;
	for(unsigned int i = 0; i - 1 < wordsList.size(); i++)
	{
		pro
	}
}

int main()
{
	std::string userInput;
	do{
		getline(std::cin, userInput);
	}while(!validInput(userInput));
	std::vector <std::string> words = divideIntoWords(userInput);
	std::vector <previousWords> prev = getWordsAndTheirPrevious(words);
	printPreviousWordsVector(prev);
	return 0;
}

#endif
