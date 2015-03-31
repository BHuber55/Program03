#if !defined (RADIXSORT_H)
#define RADIXSORT_H

#include "QueueLinked.h"
using CSC2110::QueueLinked;
#include "CD.h"

#include <iostream>
using namespace std;

template < class T >
class RadixSort
{
	/*
		
	*/
   private:
	   /*
		PRE:  Must pass a 'bin' that is expected to be altared, and parameters cannot be null.
		POST: Will sort and return the 'bin' that was passed to the function.
	   */
		static void binSort(QueueLinked<T>* bin, int curr_char, int num_chars, char (*getRadixChar) (T* item, int index));
		/*
		PRE:  Must pass 'sort', a pointer to an array of pointers that is to be sorted and returned, parameters cannot be null.
		POST: Returns an ascending sorted version of the 'sort' that was passed to the function.
		*/
		static void radixSortAsc(T** sort, int num_to_sort, int num_chars, char(*getRadixChar) (T* item, int index));  //algorithm 1
		/*
		PRE:  Must pass 'sort', a pointer to an array of pointers that is to be sorted and returned, parameters cannot be null.
		POST: Returns a descending version of the 'sort' that was originally passed to the function.
		*/
		static void radixSortDesc(T** sort, int num_to_sort, int num_chars, char(*getRadixChar) (T* item, int index));  //algorithm 2
 
	public:
		/*
		PRE:  Must pass 'sort', a pointer to an array of pointers that is to be sorted and returned. Will be sorted either ascending or descending depending
					on the users choice (bool asc).
		POST: Function will return the original 'sort' (a pointer to an array of pointers) that is sorted depending on the users choice.
		*/
		static T** radixSort(T** sort, int num_to_sort, int num_chars, bool ascending, char (*getRadixChar) (T* item, int index));
		/*
		PRE:  
		POST: Will return the index of the bin that the character passed in should be placed. Places lower case and upper case letters in the same bin.
		*/
		static int ASCII(char a);
		/*
		PRE:  
		POST: Will return the index of the bin that the character passed in should be placed if doing descending sort. Lower case and upper case letters are placed in the same bin.
		*/
		static int DescASCII(char a);
};

template < class T >
T** RadixSort<T>::radixSort(T** unsorted, int num_to_sort, int num_chars, bool ascending, char (*getRadixChar) (T* item, int index))
{	
	//DO THIS
	T** sort = new T*[num_to_sort];
	//copying the array over.
	for (int i = 0; i < num_to_sort; i++)
	{
		sort[i] = unsorted[i];
	}
	
	if (ascending)   //if ascending.. then call the ascending function
	{
		radixSortAsc(sort, num_to_sort, num_chars, getRadixChar);
	}
	
	else  //if they dont want ascending.. then call the descending function.
	{
		radixSortDesc(sort, num_to_sort, num_chars, getRadixChar);
	}

	//returns the now sorted array of titles.
	return sort;
}

template < class T >
void RadixSort<T>::binSort(QueueLinked<T>* bin, int curr_char, int num_chars, char(*getRadixChar)(T* st, int index))
{
	//DO THIS
	int num_queues = 37;
	QueueLinked<T>** bins = new QueueLinked<T>*[num_queues];

	for (int i = 0; i < num_queues; i++)
	{
		//creating a queue for each spot.
		bins[i] = new QueueLinked<T>();
	}

	while (!bin->isEmpty())
	{
		//while loop that removes the item, compares it, then finds the location it should go, then places the item there.
		T* item = bin->dequeue();
		char radix_char = (*getRadixChar)(item, curr_char);
		int index = ASCII(radix_char);		
		bins[index]->enqueue(item);		//adds the item that was dequeue'd, at the correct location depending on sort.
	}

	for (int i = 0; i < num_queues; i++)
	{
		if (bins[i]->size() > 1)
		{
			if (curr_char < num_chars)
			{
				//recurrsion call!!
				binSort(bins[i], curr_char + 1, num_chars, getRadixChar);
			}
		}

		while (!bins[i]->isEmpty())
		{
			T* item = bins[i]->dequeue();
			bin->enqueue(item);
		}
		delete bins[i];
	}

	delete[] bins;
}

template < class T >
void RadixSort<T>::radixSortAsc(T** sort, int num_to_sort, int num_chars, char(*getRadixChar) (T* st, int index))
{
   //DO THIS
	int num_queues = 37;		//1 for symbols, 10 for digits, 26 for letters.
	QueueLinked<T>** bins = new QueueLinked<T>*[num_queues];

	for (int i = 0; i < num_queues; i++)
	{
		bins[i] = new QueueLinked<T>();
	}

	for (int i = 0; i < num_to_sort; i++)
	{
		char radix_char = (*getRadixChar)(sort[i], 0);
		int placement = ASCII(radix_char);
		bins[placement]->enqueue(sort[i]);
	}

	//not sure about this.
	int count = 0;
	for (int i = 0; i < num_queues; i++)
	{
		if (bins[i]->size() > 1)
		{
			binSort(bins[i], 1, num_chars, getRadixChar);
		}
		while (!bins[i]->isEmpty())
		{
			sort[count] = bins[i]->dequeue();
			count = count + 1;
		}

		delete bins[i];
	}
	delete[] bins;

}

template < class T >
void RadixSort<T>::radixSortDesc(T** sort, int num_to_sort, int num_chars, char(*getRadixChar)(T* st, int index))
{
	//honestly this is the exact same as the ascending method except this time, the descAscii function is called which tells it a different location to be put in.
	int num_queues = 37;  //covers letters and digits
	QueueLinked<T>** bins = new QueueLinked<T>*[num_queues];  

	//must instantiate each of the
	for (int i = 0; i < num_queues; i++)
	{
		bins[i] = new QueueLinked<T>();
	}

	for (int i = num_chars; i > 0; i--)  //number of times to bin stuff
	{
		for (int x = 0; x < num_to_sort; x++)
		{
			char radix_char = (*getRadixChar)(sort[x], i);
			int placement = DescASCII(radix_char);
			bins[placement]->enqueue(sort[x]);
		}

		int count = 0;
		for (int x = 0; x < num_queues; x++)
		{
			while (!bins[x]->isEmpty())
			{
				sort[count] = bins[x]->dequeue();
				count = count + 1;
			}
		}
	}

	for (int i = 0; i < num_queues; i++)
	{
		delete bins[i];
	}

   delete[] bins;
}

//THIS IS TO HELP ME CONVERT ASCII TO REGULAR WORDS/LETTERS...
template < class T >
int RadixSort<T>::ASCII(char a)
{
	//index 0 = symbols.. index 1 = 0, index 2 = 1.... index 10 = 9, index 11 = a ..... index 37 = z.

	if (a >= 48 && a <= 57)				//if 'a' is a number.. return index to be placed at ('a' - 47) ( because if 'a' is 5.. its ascii value is 53.. so 53-47 = 6.. which is the correct index)
		return a - 47;

	else if (a >= 65 && a <= 90)		//if 'a' is a character.. return index to be placed at.. ('a' - 54).. because if 'a' is 'b' then its ascii value is 66... 66 - 54 = 11..)
		return a - 54;

	else if (a >= 97 && a <= 122)		//same as above except this time is is accounting for the lower case values.. and then placing them in the same index.
		return a - 86;

	else								//else 'a' is a special character or a space..
		return 0;
}


template < class T >
int RadixSort<T>::DescASCII(char a)
{
	//this is hard coded in.. not reusable.. might change that tomorrow..
	//index 0 = z, index 1 = y.... index 25 = a, index 35 = 0, index 36 = symbols.
	if (a >= 48 && a <= 57)			//numbers
	{
		int test = (-1 * a) + 84;
		return test;
 	}
	else if (a >= 65 && a <= 90)	//upper case letters
	{
		int test = (-1 * a) + 90;
		return test;
	}
	else if (a >= 97 && a <= 122)	//lower case letters.
	{
		int test = (-1 * a) + 122;
	}
	else
		return 36;

}

#endif
