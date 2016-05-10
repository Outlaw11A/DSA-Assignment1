#include <iostream>
#include <fstream>
#include <list>
#include <cstring>
#include <ctype.h>
#include "ListUtil.h"

using namespace std;

typedef bool (*Rules) (list<char> &inputList, list<char>::iterator &itr, char &currentChar, int &counter);

class EuroEnglishConverter
{

private:
   int ruleCount;
   Rules rulesFunctions[9];

public:

   EuroEnglishConverter();

   // Load the contents of the file
   bool loadFile(string file, list<char> &characterList);

   // Prints out a list, character by character
   void printList(const list<char> inputList);

   // Calculates hash for a character list (Note: this function was provided by Gordon Lingard)
   unsigned short getHash(const list<char> &charList);

   // Processes each of the rules over each character in the linked list
   void processRules(list<char> &inputList);

   // Replaces 'w' with 'v'
   static bool ruleOne(list<char> &inputList, list<char>::iterator &itr, char &currentChar, int &counter);

   // Erases repeated characters
   static bool ruleTwo(list<char> &inputList, list<char>::iterator &itr, char &currentChar, int &counter);

   // Replaces 'ph' with 'f'
   static bool ruleThree(list<char> &inputList, list<char>::iterator &itr, char &currentChar, int &counter);

   // Replaces 'th' with 'z'
   static bool ruleFour(list<char> &inputList, list<char>::iterator &itr, char &currentChar, int &counter);

   // Replaces 'ou' with 'u'
   static bool ruleFive(list<char> &inputList, list<char>::iterator &itr, char &currentChar, int &counter);

   // Replaces 'ea' with 'e'
   static bool ruleSix(list<char> &inputList, list<char>::iterator &itr, char &currentChar, int &counter);

   // Replaces 'c' with 's' if followed by 'e', 'i', 'y' otherwise replaces 'c' with 'k'
   static bool ruleSevenEight(list<char> &inputList, list<char>::iterator &itr, char &currentChar, int &counter);

   // Replaces the e at the end of every 3+ letter word
   static bool ruleNine(list<char> &inputList, list<char>::iterator &itr, char &currentChar, int &counter);

   // Replaces the 'ed' at the end of a word to 'd'
   static bool ruleTen(list<char> &inputList, list<char>::iterator &itr, char &currentChar, int &counter);

   // Checks whether the specified character is punctuation
   static bool isPunctuation(char character);

};