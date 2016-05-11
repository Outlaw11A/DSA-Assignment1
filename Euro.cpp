#include "Euro.h"

Euro::Euro()
{
   this->ruleCount = 10;
}

bool Euro::loadFile(string file, list<char> &characterList)
{
   ifstream fileIn;
   char ch;

   fileIn.open(file.c_str());
   if (!fileIn) {
      return false;
   }

   while (!fileIn.eof()) {
      fileIn.get(ch);
      characterList.push_back(ch);
   }
   fileIn.close();
   characterList.pop_back(); // remove last added character because it is added twice
   return true;
}

void Euro::printList(const list<char> inputList)
{
   list<char>::const_iterator itr;
   for (itr = inputList.begin(); itr != inputList.end(); itr++) {
      cout << *itr;
   }
   cout << "\n" << "Hash = " << getHash(inputList) << "\n";
}

unsigned short Euro::getHash(const list<char> &charList)
{
   unsigned short shift, hash = 0;
   list<char>::const_iterator itr;
   for (itr = charList.begin(); itr != charList.end(); itr++) {
      hash ^= *itr;
      shift = (hash & 15);
      hash = (hash << shift) | (hash >> (16 - shift));
   }
   return hash;
}


bool Euro::ruleOne(list<char> &inputList, list<char>::iterator &itr, char &current)
{
   if (current == 'w') {
      current = 'v';
      ListUtil::replaceChar(inputList, itr, 'v');
      return true;
   }
   return false;
}

bool Euro::ruleTwo(list<char> &inputList, list<char>::iterator &itr, char &current)
{
   list<char>::iterator tempItr = itr;
   ++tempItr;
   if (*tempItr == current) {
      ListUtil::eraseNext(inputList, itr);
      return true;
   }
   return false;
}

bool Euro::ruleThree(list<char> &inputList, list<char>::iterator &itr, char &current)
{
   return ListUtil::replaceDouble(current, inputList, itr, 'p', 'h', 'f');
}

bool Euro::ruleFour(list<char> &inputList, list<char>::iterator &itr, char &current)
{
   return ListUtil::replaceDouble(current, inputList, itr, 't', 'h', 'z');
}

bool Euro::ruleFive(list<char> &inputList, list<char>::iterator &itr, char &current)
{
   return ListUtil::replaceDouble(current, inputList, itr, 'o', 'u', 'u');
}

bool Euro::ruleSix(list<char> &inputList, list<char>::iterator &itr, char &current)
{
   return ListUtil::replaceDouble(current, inputList, itr, 'e', 'a', 'e');
}

bool Euro::ruleSeven(list<char> &inputList, list<char>::iterator &itr, char &current)
{
   if (current == 'c') {
      list<char>::iterator tempItr = itr;
      ++tempItr;
      switch (*tempItr) {
         case 'e':
         case 'i':
         case 'y':
            current = 's';
            ListUtil::replaceChar(inputList, itr, 's');
            break;
         default:
            current = 'k';
            ListUtil::replaceChar(inputList, itr, 'k');
            break;
      }
      return true;
   }
   return false;
}

bool Euro::ruleNine(list<char> &inputList, list<char>::iterator &itr, char &current, int &count)
{
   list<char>::iterator tempItr = itr;
   ++tempItr;
   if (count >= 3 && current == 'e' && isPunctuation(*tempItr)) {
      itr = inputList.erase(itr);
      count = 0;
      return true;
   }
   return false;
}

bool Euro::ruleTen(list<char> &inputList, list<char>::iterator &itr, char &current)
{
   list<char>::iterator tempItr = itr;
   ++tempItr;
   if (current == 'e' && *tempItr == 'd') {
      ++tempItr;
      if (isPunctuation(*tempItr)) {
         current = 'd';
         ListUtil::replaceChar(inputList, itr, 'd');
         ListUtil::eraseNext(inputList, itr);
         return true;
      }
   }
   return false;
}

void Euro::processRules(list<char> &inputList)
{
   // For each character
   list<char>::iterator itr;
   int count = 0;
   for (itr = inputList.begin(); itr != inputList.end(); itr++) {
      bool successfulRule;
      char current = (char) tolower(*itr);
      // Don't apply the rules to punctuation characters
      if (!isPunctuation(current)) {
         // Apply each rule whilst they are successful
         do {
            successfulRule = false;
            for (int i = 1; i < this->ruleCount; i++) {
               if (runRule(i, inputList, itr, current, count)) {
                  successfulRule = true;
               }
            }
         } while (successfulRule);
         count++;
      } else {
         // Reset the character count
         count = 0;
      }
   }
}

bool Euro::isPunctuation(char character) {
   return (ispunct(character) || isspace(character) || character == '\n');
}

bool Euro::runRule(int rule, list<char> &inputList, list<char>::iterator &itr, char &current,
                     int &count)
{
   switch(rule) {
      case 1:
         return ruleOne(inputList, itr, current);
      case 2:
         return ruleTwo(inputList, itr, current);
      case 3:
         return ruleThree(inputList, itr, current);
      case 4:
         return ruleFour(inputList, itr, current);
      case 5:
         return ruleFive(inputList, itr, current);
      case 6:
         return ruleSix(inputList, itr, current);
      case 7:
         return ruleSeven(inputList, itr, current);
      case 8:
         return ruleNine(inputList, itr, current, count);
      case 9:
         return ruleTen(inputList, itr, current);
      default:
         return false;
   }
}