#include "ListUtil.h"

void ListUtil::replaceChar(list<char> &inList, list<char>::iterator &itr, char replacement)
{
   if (isupper(*itr)) {
      replacement = (char)toupper(replacement);
   }
   inList.insert(itr, replacement);
   inList.erase(itr);
}

bool ListUtil::replaceFollowing(list<char> &inList, list<char>::iterator &itr, char search, char replacement)
{
   list<char>::iterator tempItr = itr;
   if (*++tempItr == search) {
      replaceChar(inList, itr, replacement);
      eraseNext(inList, itr);
      return true;
   }
   return false;
}

void ListUtil::eraseNext(list<char> &inList, list<char>::iterator &itr)
{
   inList.erase(++itr);
   --itr;
}

bool ListUtil::replaceDoubleChar(char &inputChar, list<char> &inList, list <char>::iterator &itr, char indexChar, char followingChar, char replacementChar)
{
   if (inputChar == indexChar) {
      bool result = replaceFollowing(inList, itr, followingChar, replacementChar);
      if (result) {
         inputChar = replacementChar;
      }
      return result;
   }
   return false;
}