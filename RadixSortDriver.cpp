#include "RadixSort.h"
#include "CD.h"
using CSC2110::CD;
#include "ListArray.h"
using CSC2110::ListArray;
#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;
#include "Text.h"
using CSC2110::String;

#include <iostream>
using namespace std;

void deleteCDs(ListArray<CD>* list)
{
   ListArrayIterator<CD>* iter = list->iterator();

   while(iter->hasNext())
   {
      CD* cd = iter->next();
      delete cd;
   }
   delete iter;
}

int main()
{
   ListArray<CD>* list = CD::readCDs("cds.txt");
   int size = list->size();

   CD** cds = new CD*[size];

   ListArrayIterator<CD>* iter = list->iterator();
   int count = 0;
   while(iter->hasNext())
   {
      CD* cd = iter->next();
      cds[count] = cd;
      count++;
   }
   delete iter;

	//DO THIS
	//test both radix sort methods using the cds array

	//ascending first.
	bool asc = true;
	CD** cds_asc = RadixSort<CD>::radixSort(cds, count, 50, asc, &CD::getRadixChar);

	cout << "This is ascending order......" << endl;
	for (int i = 0; i < count; i++)
	{
		String* title = cds_asc[i]->getKey();
		title->displayString();
	}

	cout << "Press enter to test Descending." << endl;
	cin.get();
	cout << endl << endl << endl;

	asc = false;
	CD** cds_desc = RadixSort<CD>::radixSort(cds, count, 50, asc, &CD::getRadixChar);

	cout << "This is descending order........." << endl;

	for (int i = 0; i < count; i++)
	{
		String* title = cds_desc[i]->getKey();
		title->displayString();
	}

   delete[] cds;
   delete[] cds_asc;
   delete[] cds_desc;

   deleteCDs(list);
   delete list;

   return 0;
}
