#include <iostream>
#include <list>
#include "EuroEnglishConverter.h"

using namespace std;

int main(int argc, char*argv[])
{
   if (argc == 2) {
      list<char> originalList;
      EuroEnglishConverter converter;

      if (!converter.loadFile(argv[1], originalList)) {
         cout << "Error - Can't open file." << "\n";
         return 0;
      }

      converter.printList(originalList);
      cout << "\n" << "Hash = " << converter.getHash(originalList) << "\n";

      converter.processRules(originalList);
      converter.printList(originalList);
      cout << "\n" << "Hash = " << converter.getHash(originalList) << "\n";
   } else {
      cout << "Error - Invalid command line arguments." << "\n";
   }

   return 0;
}