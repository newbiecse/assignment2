/*
 * Created by: Dinh Quang Tuan
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
	FILE* fp = fopen(DICT_FILE, "r");
	// check if file is empty
	if (fp == NULL) {
		dict.size = 0;
		return;
	}
	
	// TODO: read text file and parse text into dict structure

	fclose(fp);
}

/*
 * Executes all actions in action list
 *
 * @param reference dict: The dictionary structure
 * @param actions: list of actions
 * @param outFile: The steam output file
 */
void do_action(Dictionary &dict, ActionsList actions, ofstream &outFile) {
	for (int i = 0; i < actions.size; ++i) {
		ActionType type = actions.list[i].type; // action type
		string value = actions.list[i].value; // action parameters
		bool result = true; // response from action

		switch (type) {
		case INSERT: {
			// TODO
			Word *word = getWord(value);
			insert(dict, *word);
			break;
		}
		case REMOVE: {
			// TODO
			break;
		}
		case CRYSTAL: {
			// TODO
			break;
		}
		case SEARCH: {
			// TODO
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
	// TODO
	dict.words[0] = new_word;
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
	return false;
}

/*
*	get word from string
*/
Word* getWord(string text) {
	Word *word = new Word();
	word->size = 1;
	word->item="present";

	return word;
}

/*
*	get meaning from string
*/
Meaning* getMeaning(Word &word, string textMeaning) {
	// init meaning
	Meaning *meaning = new Meaning();
	meaning->size = 1;
	meaning->definition = "difinition meaning";
	meaning->type = NOUN;

	// append meaning
	word.meaning[0] = *meaning;
	return meaning;
}

/*
*	get example from string
*/
Instance* get(Meaning &meaning, string textExample) {
	// init example
	Instance *instance = new Instance();
	instance->sentence = "sentence instance";
	instance->translation = "translation instance";	

	// append example
	meaning.examples[0] = *instance;
	return instance;
}