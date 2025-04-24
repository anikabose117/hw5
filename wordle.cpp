#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
// #include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(
    std::string word, // current word being created
    std::string floating, // available letters to use
    const std::set<std::string>& dict, // all valid words in English language
    std::set<std::string>& final, // final list of all possible words
    int index // current letter position in the word
);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> potentialWords;
    //int wordLength = in.length();

    // start at index = 0 because starting at the beginning of the word
    wordleHelper(in, floating, dict, potentialWords, 0);

    // return final set 
    return potentialWords;
}


// Define any helper functions here

void wordleHelper(
    std::string word,
    std::string floating,
    const std::set<std::string>& dict,
    std::set<std::string>& final,
    int index
){
    // reached the end of the word, i.e. recursed through the entire word
    if (index == word.size()){
        
        // if word is found in set of all possible English words and all of the needed floating letters have been used, then this is a valid guess
        if (dict.find(word) != dict.end() && floating.empty()){
            final.insert(word);
        }

        // exit out
        return;
    }


    // int wordLength = word.length();

    // checks if letter has been placed into spot, if so, move onto next index/position in the word
    if (word[index] != '-'){
        wordleHelper(word, floating, dict, final, index + 1);
        return;
    }

    // loops through floating letters, placing it in the "-" spot starting with the first floating letter 
    for (int i = 0; i < floating.length(); i++){
        word[index] = floating[i];
        // calls loop onto next position in the word
        // decrease size of floating string as letters are used up
        wordleHelper(word, floating.substr(0, i) + floating.substr(i + 1), dict, final, index + 1);
    }

    // has gone through floating letters, now floating letter amount should be zero as for loop is not entered
    // gets how many dashes/ blanks are still left
    int numDashes = 0;
    for (int i = index; i < word.size(); i++){
        if (word[i] == '-'){
            numDashes++;
        }
    }

    // only calls this recursive statement if there are still more blanks to fill
    if (numDashes >= floating.length()){
        for (char curr = 'a'; curr <= 'z'; curr++){
            // loops through all letters, even ones that we already checked in floating, because there could be duplicates
            word[index] = curr;
            // recurse by moving onto next position in the word
            wordleHelper(word, floating, dict, final, index + 1);
        }
    }
}
