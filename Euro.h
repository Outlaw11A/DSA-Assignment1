#include <iostream>
#include <fstream>
#include <list>
#include <cstring>
#include <ctype.h>
#include "ListUtil.h"

using namespace std;

class Euro
{

private:
   int ruleCount;

public:

   Euro();

   // Load the contents of the file
   bool loadFile(string file, list<char> &characterList);

   // Prints out a list, character by character
   void printList(const list<char> inList);

   // Calculates hash for a character list (Note: this function was provided by Gordon Lingard)
   unsigned short getHash(const list<char> &charList);

   // Processes each of the rules over each character in the linked list
   void processRules(list<char> &inList);

   // Replaces 'w' with 'v'
   static bool ruleOne(list<char> &inList, list<char>::iterator &itr, char &current);

   // Erases repeated characters
   static bool ruleTwo(list<char> &inList, list<char>::iterator &itr, char &current);

   // Replaces 'ph' with 'f'
   static bool ruleThree(list<char> &inList, list<char>::iterator &itr, char &current);

   // Replaces 'th' with 'z'
   static bool ruleFour(list<char> &inList, list<char>::iterator &itr, char &current);

   // Replaces 'ou' with 'u'
   static bool ruleFive(list<char> &inList, list<char>::iterator &itr, char &current);

   // Replaces 'ea' with 'e'
   static bool ruleSix(list<char> &inList, list<char>::iterator &itr, char &current);

   // Replaces 'c' with 's' if followed by 'e', 'i', 'y' otherwise replaces 'c' with 'k'
   static bool ruleSeven(list<char> &inList, list<char>::iterator &itr, char &current);

   // Replaces the e at the end of every 3+ letter word
   static bool ruleNine(list<char> &inList, list<char>::iterator &itr, char &current, int &count);

   // Replaces the 'ed' at the end of a word to 'd'
   static bool ruleTen(list<char> &inList, list<char>::iterator &itr, char &current);

   // Checks whether the specified character is punctuation
   static bool isPunctuation(char character);

   // Runs the specified rule
   bool runRule(int rule, list<char> &inputList, list<char>::iterator &itr, char &current,
                  int &count);

};