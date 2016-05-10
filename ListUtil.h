#include <list>
#include <ctype.h>

using namespace std;

class ListUtil
{

public:

   // Replaces a character in a linked list
   static void replaceChar(list<char> &inList, list<char>::iterator &itr, char replacement);

   // Replaces the current char and the one following with the specified replacement
   static bool replaceFollowing(list<char> &inList, list<char>::iterator &itr, char search,
                                 char replacement);

   // Erases the next character
   static void eraseNext(list<char> &inList, list<char>::iterator &itr);

   // Replace two consecutive characters with a single character
   static bool replaceDouble(char &inChar, list<char> &inList, list <char>::iterator &itr,
                              char index, char following, char replacement);
};