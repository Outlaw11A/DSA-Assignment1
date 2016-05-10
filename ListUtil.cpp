#include "ListUtil.h"

void ListUtil::replaceChar(list<char> &inList, list<char>::iterator &itr, char replacement)
{
   if (isupper(*itr)) {
      replacement = (char)toupper(replacement);
   }
   inList.insert(itr, replacement);
   inList.erase(itr);
}

bool ListUtil::replaceFollowing(list<char> &inList, list<char>::iterator &itr, char search,
                                 char replacement)
{
   list<char>::iterator tempItr = itr;
   ++tempItr;
   if (*tempItr == search) {
      replaceChar(inList, itr, replacement);
      eraseNext(inList, itr);
      return true;
   }
   return false;
}

void ListUtil::eraseNext(list<char> &inList, list<char>::iterator &itr)
{
   ++itr;
   inList.erase(itr);
   --itr;
}

bool ListUtil::replaceDouble(char &inChar, list<char> &inList, list<char>::iterator &itr,
                              char index, char following, char replacement)
{
   if (inChar == index) {
      bool result = replaceFollowing(inList, itr, following, replacement);
      if (result) {
         inChar = replacement;
      }
      return result;
   }
   return false;
}