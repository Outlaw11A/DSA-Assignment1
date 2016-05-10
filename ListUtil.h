#include <list>
#include <ctype.h>

using namespace std;

class ListUtil
{

public:

   // Replaces a character in a linked list
   static void replaceChar(list<char> &inputList, list<char>::iterator &itr, char replacement);

   // Replaces the current char and the one following with the specified replacement
   static bool replaceFollowing(list<char> &inputList, list<char>::iterator &itr, char search, char replacement);

   // Erases the next character
   static void eraseNext(list<char> &inputList, list<char>::iterator &itr);

   // Replace two consecutive characters with a single character
   static bool replaceDoubleChar(char &inputChar, list<char> &inputList, list <char>::iterator &itr, char indexChar, char followingChar, char replacementChar);
};