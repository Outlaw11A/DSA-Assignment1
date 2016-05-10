#include "ListUtil.h"

void ListUtil::replaceChar(list<char> &inputList, list<char>::iterator &itr, char replacement)
{
   if (isupper(*itr)) {
      replacement = (char)toupper(replacement);
   }
   inputList.insert(itr, replacement);
   inputList.erase(itr);
}

bool ListUtil::replaceFollowing(list<char> &inputList, list<char>::iterator &itr, char search, char replacement)
{
   list<char>::iterator tempItr = itr;
   if (*++tempItr == search) {
      replaceChar(inputList, itr, replacement);
      eraseNext(inputList, itr);
      return true;
   }
   return false;
}

void ListUtil::eraseNext(list<char> &inputList, list<char>::iterator &itr)
{
   inputList.erase(++itr);
   --itr;
}

bool ListUtil::replaceDoubleChar(char &inputChar, list<char> &inputList, list <char>::iterator &itr, char indexChar, char followingChar, char replacementChar)
{
   if (inputChar == indexChar) {
      bool result = replaceFollowing(inputList, itr, followingChar, replacementChar);
      if (result) {
         inputChar = replacementChar;
      }
      return result;
   }
   return false;
}