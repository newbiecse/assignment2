/*
 * Modified by: NGUYEN VAN TAN
 * Created date: May 4 2015
 * Project: assignment 2 - programming fundamental
 * Description: this file implements for basic functions on Dictionary 
 * structure
 */

/*
 *  Instructions
 *  ------------
 *  This file contains code that helps you get started on the c plus plus 
 *	programming.
 *  You will need to complete the following functions in this exericse:
 *   	dictionary.h 	(contains essential structures and methods interface)
 *   	dictionary.cpp 	(implementation of dictionary methods)
 *   	action.cpp* 	(the only file you should change code and submit)
 *   	main.cpp 		(entry point)
 *
 *  For this exercise, you will need to change any code in this file.
 *  	You should write your own code for 6 methods: load_dictionary, do_action, insert, remove,
 *  	remove by crystal condition and search.
 *   	You could implement other methods in this file (action.cpp).
 *
 *  We implemented load and store methods in dictionary.cpp, let use them.
 */

#ifndef __ACTION__CPP__
#define __ACTION__CPP__
#endif //__ACTION__CPP__

#include "dictionary.h"

/*
*	define methods
*/

Word* getWord(string text);
Meaning set_meaning(string line);

string getWordItem(string text);
WordType set_word_type(string line);
void doSelectionSort(Dictionary &dict);
void removeByIndex(Dictionary &dict, int index);
bool isTangGiamTuanHoan(string item);
void export_error_message(ofstream &outFile, string msg);

/*
*	string utility
*/
string utilityGetSubString(string s, char cStart, char cEnd);


/**
	Global variables
*/
int nIndexSearch = 0;
string error_messages = "";

/*
 *  Function Implementation
 *	You need to write your own code in //TO DO 
 *	You could change or write any code in this file. However, you should not 
 *	change function prototypes
 */

/*
 * Loads dictionary into structure from Dictionary file
 *
 * @param reference dict: The dictionary structure
 * @return word type
 */
void load_dictionary(Dictionary &dict) {
	// open text file
	// FILE* fp = fopen(DICT_FILE, "r");
	// check if file is empty
	//if (fp == NULL) {
	//	dict.size = 0;
	//	return;
	//}
	//fclose(fp);

	ifstream dictFile(DICT_FILE);
	string str;

	int i = 0;
	string value = "";
	while (std::getline(dictFile, str))
    {     
		if(str.substr(0, 2) == "<i") {		
			if(i > 0) {
				Word *word = getWord(value);
				insert(dict, *word);
				value = "";
			}		
		}
		value.append(str);
		value.append("\n");
		i++;
    }

	if(i > 0) {
		Word *word = getWord(value);
		insert(dict, *word);
		value = "";
	}

	if(i == 0) {
		dict.size = 0;
		return;
	}

	dictFile.close();


	
}

/*
 * Executes all actions in action list
 *
 * @param reference dict: The dictionary structure
 * @param actions: list of actions
 * @param outFile: The steam output file
 */
void do_action(Dictionary &dict, ActionsList actions, ofstream &outFile) {

	// load word from dictionary
	//load_dictionary(dict);

	for (int i = 0; i < actions.size; ++i) {
		ActionType type = actions.list[i].type; // action type
		string value = actions.list[i].value; // action parameters
		bool result = true; // response from action

		switch (type) {
		case INSERT: {
			// TODO
			Word *word = getWord(value);

			// word hasn't meaning or example
			// hasn't implement yet

			// word already exists
			bool isExists = search(dict, word->item, *word);

			// insert
			if(isExists) {
				export_error_message(outFile, ERROR_MESSAGE_1_1);
			} else {
				insert(dict, *word);
			}
			
			break;
		}
		case REMOVE: {
			// TODO
			Word *word = getWord(value);

			// word already exists
			bool isExists = search(dict, word->item, *word);
			if(!isExists) {
				export_error_message(outFile, ERROR_MESSAGE_2_1);
			} else {
				remove(dict, word->item);
			}

			break;
		}
		case CRYSTAL: {
			// TODO
			remove_by_crystal(dict);
			break;
		}
		case SEARCH: {
			// TODO
			Word *word = getWord(value);

			// word already exists
			bool isExists = search(dict, word->item, *word);

			// insert
			if(!isExists) {
				export_error_message(outFile, ERROR_MESSAGE_3_1);
			} else {
				write_word(outFile, *word);
			}
			break;
		}
		case EXPORT: {
			export_dictionary(outFile, dict);
			break;
		}
		default:
			break;
		}
	}
}

/*
 * Inserts a word into dictionary
 *
 * @param reference dict: The dictionary structure
 * @param new_word: The word structure
 * @return true if success, otherwise return false
 */
bool insert(Dictionary &dict, Word new_word) {

	if(dict.size < 0) {
		dict.size = 0;
	}

	// add new word
	dict.words[dict.size] = new_word;

	// update size
	dict.size ++;

	// sort
	doSelectionSort(dict);

	return false;
}

/*
 * Removes a word from dictionry based on its name
 *
 * @param reference dict: The dictionary structure
 * @param name: the name of word
 * @return true if success, otherwise return false
 */
bool remove(Dictionary &dict, string item) {
	// TODO
	Word *word = new Word();
	bool isFound = search(dict, item, *word);
	removeByIndex(dict, nIndexSearch);
	return false;
}

/*
 * Removes all words which satisfies crystal condition
 *
 * @param reference dict: The dictionary structure
 * @return true if success, otherwise return false
 */
bool remove_by_crystal(Dictionary &dict) {
	// TODO
	for(int i = 0; i < dict.size; i++) {
		if(isTangGiamTuanHoan(dict.words[i].item)) {
			removeByIndex(dict, i);
		}
	}
	
	return false;
}

/*
 * Searches a word in dictionary based on its name
 *
 * @param reference dict: The dictionary structure
 * @param name: the name of word
 * @param reference word: updating word by target if searching gets success
 * @return true if success, otherwise return false
 */
bool search(Dictionary &dict, string name, Word &word) {

	// TODO
	for(int i = 0; i < dict.size; i++) {
		if(dict.words[i].item == name) {

			// update index search
			nIndexSearch = i;

			// found word
			word = dict.words[i];
			return true;
		}
	}
	return false;
}

/*
*	get word from string
*/
Word* getWord(string text) {

	// init
	Word *word = new Word();
	
	// temp variables
	istringstream f(text);
    string line;

	// item
	getline(f, line);
	word->item = getWordItem(line);

	// meaning
	int i = 0;
    while (getline(f, line)) {
		word->meaning[i] = set_meaning(line);
		i++;
    }

	// word number meaning
	word->size = i;	

	return word;
}


WordType set_word_type(string line) {
	// get text
	string textWordType = utilityGetSubString(line, '<', '>');

	// process text
	if(textWordType == "noun") {
		return NOUN;
	} else if(textWordType == "adjective") {
		return ADJECTIVE;
	} else {
		return VERB;
	}
}


/*
*	get meaning from string
*/
Meaning set_meaning(string line) {

	// init
	Meaning *meaning = new Meaning();

	// word type
	meaning->type = set_word_type(line);

	bool isBegin = true;
	bool isHasDefition = false;
	bool isCompleteExample = true;
	int nExamples = 0;

	int nStart = 0;
	int nEnd = 0;

	string sText = "";


	for(int i = 0; i < line.length(); i++) {
		// special charater: "
		if(line[i] == '"') {
			if(isBegin) {
				// begin
				isBegin = false;
				nStart = i + 1;
			} else {
				// end
				isBegin = true;
				nEnd = i - nStart;
				sText = line.substr(nStart, nEnd);
				if(!isHasDefition) {
					// definition
					isHasDefition = true;
					 meaning->definition = sText;
				} else {
					// examples
					if( isCompleteExample ) {
						// sentence
						meaning->examples[nExamples].sentence = sText;
						isCompleteExample = false;
					} else {
						// translation						
						meaning->examples[nExamples].translation = sText;
						isCompleteExample = true;
						nExamples ++;
					}					
				}
			}
		} // end if
	} // end for

	// number examples
	meaning->size = nExamples;

	return *meaning;
}

string getWordItem(string textWordItem) {
	string item = utilityGetSubString(textWordItem, '"', '"');
	return item;
}


string utilityGetSubString(string s, char cStart, char cEnd) {
	int start = 0;
	int end = 0;
	for(int i = 0; i < s.length(); i++) {
		if(start == 0 && s[i] == cStart) {
			start = i + 1;
		} else if (s[i] == cEnd) {
			end = i - start;
			break;
		}
	}
	return s.substr(start, end);
}


void doSelectionSort(Dictionary &dict) {
	for (int i = 0; i < dict.size - 1; i++)
        {
            int index = i;
			for (int j = i + 1; j < dict.size; j++)
				if (dict.words[j].item < dict.words[index].item)
                    index = j;
      
            Word wordSmaller = dict.words[index]; 
            dict.words[index] = dict.words[i];
            dict.words[i] = wordSmaller;
        }
}

void removeByIndex(Dictionary &dict, int index) {
	for (int i = index; i < dict.size - 1; i++) {
		//int tmpIndex = i;
		//Word wTemp = dict.words[i + 1];
		dict.words[i] = dict.words[i + 1];
    }
	// update Dictionary size
	dict.size --;
}

bool isTangGiamTuanHoan(string item) {

	int len = item.length();
	if(len == 0 || len == 1) {
		return true;
	} else if(len == 2) {
		if(item[0] != item[1]) {
			return true;
		}
	}

	if(item[0] < item[1]) {
		for(int i = 1; i < len - 1; i++) {
			// Ai-1 < Ai -> Ai > Ai+1 
			if( ! (item[i-1] < item[i] && item[i] > item[i+1]) ) {
				return false;
			}
		}
	} else {
		for(int i = 1; i < len - 1; i++) {
			// Ai-1 < Ai -> Ai > Ai+1 
			if( ! (item[i-1] > item[i] && item[i] < item[i+1]) ) {
				return false;
			}
		}
	}
	
	return true;
}

void export_error_message(ofstream &outFile, string msg) {
	outFile << msg + "\n";
}