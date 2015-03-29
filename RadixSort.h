#if !defined (RADIXSORT_H)
#define RADIXSORT_H

#include "QueueLinked.h"
using CSC2110::QueueLinked;
#include "CD.h"

//had to look up ascii values for this lab.. made it interesting for sure.

template < class T >
class RadixSort
{
   private:
	   /*
		PRE:  
		POST: 
	   */
		static void binSort(QueueLinked<T>* bin, int curr_char, int num_chars, char (*getRadixChar) (T* item, int index));
		/*
		PRE: 
		POST: 
		*/
		static void radixSortAsc(T** sort, int num_to_sort, int num_chars, char(*getRadixChar) (T* item, int index));  //algorithm 1
		/*
		PRE:  
		POST: 
		*/
		static void radixSortDesc(T** sort, int num_to_sort, int num_chars, char(*getRadixChar) (T* item, int index));  //algorithm 2
		/*
		PRE:  
		POST: 
		*/
 
	public:
		/*
		PRE:  
		POST: 
		*/
		static T** radixSort(T** sort, int num_to_sort, int num_chars, bool asc, char (*getRadixChar) (T* item, int index));
		/*
		PRE:  
		POST: 
		*/
		static int ASCII(char a);
};

template < class T >
T** RadixSort<T>::radixSort(T** unsorted, int num_to_sort, int num_chars, bool asc, char (*getRadixChar) (T* item, int index))
{
	//DO THIS
	T** sort = new T*[num_to_sort];

	//copying the array over.
	for (int i = 0; i < num_to_sort; i++)
	{
		sort[i] = unsorted[i];
	}
	
	if (asc)   //if ascending.. then call the ascending function
	{
		radixSortAsc(sort, num_to_sort, num_chars, getRadixChar);
	}
	
	else  //if they dont want ascending.. then call the descending function.
	{
		radixSortDesc(sort, num_to_sort, num_chars, getRadixChar);
	}

	return sort;
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

	for (int i = 0; i < num_chars; i++)
	{
		for(int x = 0; x < num_to_sort; x++)
		{
			char radix_char = (*getRadixChar)(sort[i], 0);
			int placement = ASCII(radix_char);
			bins[placement]->enqueue(sort[i]);
		}
	}

	//not sure about this.
	for (int i = 0; i < num_queues; i++)
	{
		if (bins[i]->size() > 1)
		{
			binSort(bins[i], 1, num_chars, getRadixChar);
		}

		while (!bins[i]->isEmpty())
		{
			int tmp = 0;
			sort[tmp] = bins[i]->dequeue();
			tmp + 1;
		}
	
		delete bins[i];
	}
	delete[] bins;
}

template < class T >
void RadixSort<T>::binSort(QueueLinked<T>* bin, int curr_char, int num_chars, char (*getRadixChar) (T* st, int index))
{
   //DO THIS
	int num_queues = 37;
	QueueLinked<T>** bins = new QueueLinked<T>*[num_queues];

	for (int i = 0; i < num_queues; i++)
	{
		bins[i] = new QueueLinked<T>();
	}

	while (!bin->isEmpty())
	{
		T* item = bin->dequeue();

		char radix_char = (*getRadixChar)(item, curr_char);
		int index = ASCII(radix_char);
		bins[index]->enqueue(item);
	}

	for (int i = 0; i < num_queues; i++)
	{
		if (bins[i]->size() > 1)
		{
			binSort(bins[i], curr_char + 1, num_chars, getRadixChar);
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
void RadixSort<T>::radixSortDesc(T** sort, int num_to_sort, int num_chars, char (*getRadixChar)(T* st, int index))
{
	int num_queues = 37;  //covers letters and digits
	QueueLinked<T>** bins = new QueueLinked<T>*[num_queues];  

	//must instantiate each of the
		//DO THIS queues
	for (int i = 0; i < num_queues; i++)
	{
		bins[i] = new QueueLinked<T>();
	}

	for (int i = num_chars; i > 0; i--)  //number of times to bin stuff
	{
		//DO THIS
		for (int x = 0; x < num_to_sort; x++)
		{
			char the_char = (*getRadixSort(sort[x], i));
			int placement = ASCII(the_char);
			bins[placement]->enqueue(sort[x]);
		}

		for (int x = 0; x < num_queues; x++)
		{
			while (!bins[x]->isEmpty())
			{
				int tmp;
				//not sure if i need this if statment or not..
				if (bins[x] == NULL)
				{
					sort[tmp] = bins[x]->dequeue();
			    }

				tmp + 1;
			}
			delete bins[x];
	   }
   }

   delete[] bins;
}

//THIS IS TO HELP ME CONVERT ASCII TO REGULAR WORDS/LETTERS...
template < class T >
int RadixSort<T>::ASCII(char a)
{
	//index 0 = symbols.. index 1 = 0, index 2 = 1.... index 10 = 9, index 11 = a ..... index 37 = z.

	if (a <= 48 && a >= 57)		//if 'a' is a number.. return index to be placed at ('a' - 47) ( because if 'a' is 5.. its ascii value is 53.. so 53-47 = 6.. which is the correct index)
		return a - 47;

	else if (a <= 65 && a >= 90)		//if 'a' is a character.. return index to be placed at.. ('a' - 54).. because if 'a' is 'b' then its ascii value is 66... 66 - 54 = 11..)
		return a - 54;

	else if (a <= 97 && a >= 122)		//same as above except this time is is accounting for the lower case values.. and then placing them in the same index.
		return a - 86;

	else								//else 'a' is a special character or a space..
		return 0;
}

#endif
