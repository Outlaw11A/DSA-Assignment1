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
   this->rulesFunctions[6] = ruleSevenEight;
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


bool EuroEnglishConverter::ruleOne(list<char> &inputList, list<char>::iterator &itr, char &currentChar, int &counter)
{
   if (currentChar == 'w') {
      currentChar = 'v';
      ListUtil::replaceChar(inputList, itr, 'v');
      return true;
   }
   return false;
}

bool EuroEnglishConverter::ruleTwo(list<char> &inputList, list<char>::iterator &itr, char &currentChar, int &counter)
{
   if (!isPunctuation(currentChar)) {
      return ListUtil::replaceFollowing(inputList, itr, currentChar, currentChar);
   }
   return false;
}

bool EuroEnglishConverter::ruleThree(list<char> &inputList, list<char>::iterator &itr, char &currentChar, int &counter)
{
   return ListUtil::replaceDoubleChar(currentChar, inputList, itr, 'p', 'h', 'f');
}

bool EuroEnglishConverter::ruleFour(list<char> &inputList, list<char>::iterator &itr, char &currentChar, int &counter)
{
   return ListUtil::replaceDoubleChar(currentChar, inputList, itr, 't', 'h', 'z');
}

bool EuroEnglishConverter::ruleFive(list<char> &inputList, list<char>::iterator &itr, char &currentChar, int &counter)
{
   return ListUtil::replaceDoubleChar(currentChar, inputList, itr, 'o', 'u', 'u');
}

bool EuroEnglishConverter::ruleSix(list<char> &inputList, list<char>::iterator &itr, char &currentChar, int &counter)
{
   return ListUtil::replaceDoubleChar(currentChar, inputList, itr, 'e', 'a', 'e');
}

bool EuroEnglishConverter::ruleSevenEight(list<char> &inputList, list<char>::iterator &itr, char &currentChar, int &counter)
{
   if (currentChar == 'c') {
      list<char>::iterator tempItr = itr;
      switch (*++tempItr) {
         case 'e':
         case 'i':
         case 'y':
            currentChar = 's';
            ListUtil::replaceChar(inputList, itr, 's');
            break;
         default:
            currentChar = 'k';
            ListUtil::replaceChar(inputList, itr, 'k');
            break;
      }
      return true;
   }
   return false;
}

bool EuroEnglishConverter::ruleNine(list<char> &inputList, list<char>::iterator &itr, char &currentChar, int &counter)
{
   list<char>::iterator tempItr = itr;
   if (counter >= 3 && currentChar == 'e' && isPunctuation(*++tempItr)) {
      inputList.erase(itr);
      counter = 0;
      return true;
   }
   return false;
}

bool EuroEnglishConverter::ruleTen(list<char> &inputList, list<char>::iterator &itr, char &currentChar, int &counter)
{
   list<char>::iterator tempItr = itr;
   if (currentChar == 'e' && *++tempItr == 'd' && isPunctuation(*++tempItr)) {
      currentChar = 'd';
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
   int counter = 0;
   for (itr = inputList.begin(); itr != inputList.end(); itr++) {
      bool successfulRule;
      char currentChar = (char) tolower(*itr);
      if (!isPunctuation(currentChar)) {
         do {
            successfulRule = false;
            for (int i = 0; i < this->ruleCount; i++) {
               if (this->rulesFunctions[i](inputList, itr, currentChar, counter)) {
                  successfulRule = true;
               }
            }
         } while (successfulRule);
         counter++;
      } else {
         counter = 0;
      }
   }
}

bool EuroEnglishConverter::isPunctuation(char character) {
   return (ispunct(character) || character == ' ' || character == '\n');
}