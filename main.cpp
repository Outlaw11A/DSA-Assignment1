#include <iostream>
#include <list>
#include "Euro.h"

using namespace std;

int main(int argc, char*argv[])
{
   if (argc == 2) {
      list<char> originalList;
      string file = argv[1];
      Euro converter;

      if (!converter.loadFile(file, originalList)) {
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