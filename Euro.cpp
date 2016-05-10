#include "EuroEnglishConverter.h"

EuroEnglishConverter::EuroEnglishConverter()
{
   this->ruleCount = 9;
   this->rulesFunctions[0] = ruleOne;
   this->rulesFunctions[1] = ruleTwo;
   this->rulesFunctions[2] = ruleThree;
   this->rulesFunctions[3] = ruleFour;
   this->rulesFunctions[4] = ruleFive;
   this->rulesFunctions[5] = ruleSix;
   this->rulesFunctions[6] = ruleSeven;
   this->rulesFunctions[7] = ruleNine;
   this->rulesFunctions[8] = ruleTen;
}

bool EuroEnglishConverter::loadFile(string file, list<char> &characterList)
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

void EuroEnglishConverter::printList(const list<char> inputList)
{
   list<char>::const_iterator itr;
   for (itr = inputList.begin(); itr != inputList.end(); itr++) {
      cout << *itr;
   }
}

unsigned short EuroEnglishConverter::getHash(const list<char> &charList)
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


bool EuroEnglishConverter::ruleOne(list<char> &inputList, list<char>::iterator &itr, char &current, int &count)
{
   if (current == 'w') {
      current = 'v';
      ListUtil::replaceChar(inputList, itr, 'v');
      return true;
   }
   return false;
}

bool EuroEnglishConverter::ruleTwo(list<char> &inputList, list<char>::iterator &itr, char &current, int &count)
{
   if (!isPunctuation(current)) {
      return ListUtil::replaceFollowing(inputList, itr, current, current);
   }
   return false;
}

bool EuroEnglishConverter::ruleThree(list<char> &inputList, list<char>::iterator &itr, char &current, int &count)
{
   return ListUtil::replaceDoubleChar(current, inputList, itr, 'p', 'h', 'f');
}

bool EuroEnglishConverter::ruleFour(list<char> &inputList, list<char>::iterator &itr, char &current, int &count)
{
   return ListUtil::replaceDoubleChar(current, inputList, itr, 't', 'h', 'z');
}

bool EuroEnglishConverter::ruleFive(list<char> &inputList, list<char>::iterator &itr, char &current, int &count)
{
   return ListUtil::replaceDoubleChar(current, inputList, itr, 'o', 'u', 'u');
}

bool EuroEnglishConverter::ruleSix(list<char> &inputList, list<char>::iterator &itr, char &current, int &count)
{
   return ListUtil::replaceDoubleChar(current, inputList, itr, 'e', 'a', 'e');
}

bool EuroEnglishConverter::ruleSeven(list<char> &inputList, list<char>::iterator &itr, char &current, int &count)
{
   if (current == 'c') {
      list<char>::iterator tempItr = itr;
      switch (*++tempItr) {
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

bool EuroEnglishConverter::ruleNine(list<char> &inputList, list<char>::iterator &itr, char &current, int &count)
{
   list<char>::iterator tempItr = itr;
   if (count >= 3 && current == 'e' && isPunctuation(*++tempItr)) {
      inputList.erase(itr);
      count = 0;
      return true;
   }
   return false;
}

bool EuroEnglishConverter::ruleTen(list<char> &inputList, list<char>::iterator &itr, char &current, int &count)
{
   list<char>::iterator tempItr = itr;
   if (current == 'e' && *++tempItr == 'd' && isPunctuation(*++tempItr)) {
      current = 'd';
      ListUtil::replaceChar(inputList, itr, 'd');
      ListUtil::eraseNext(inputList, itr);
      return true;
   }
   return false;
}

void EuroEnglishConverter::processRules(list<char> &inputList)
{
   // For each character
   list<char>::iterator itr;
   int count = 0;
   for (itr = inputList.begin(); itr != inputList.end(); itr++) {
      bool successfulRule;
      char current = (char) tolower(*itr);
      if (!isPunctuation(current)) {
         do {
            successfulRule = false;
            for (int i = 0; i < this->ruleCount; i++) {
               if (this->rulesFunctions[i](inputList, itr, current, count)) {
                  successfulRule = true;
               }
            }
         } while (successfulRule);
         count++;
      } else {
         count = 0;
      }
   }
}

bool EuroEnglishConverter::isPunctuation(char character) {
   return (ispunct(character) || character == ' ' || character == '\n');
}