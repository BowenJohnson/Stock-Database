#include "hashmap.h"
#include <iomanip>
#include <string.h>

using namespace std;

const char	HashMap::YOUR_NAME[] = "Bowen Johnson";

HashMap::HashMap(int capacity) :
	slots{new Slot[capacity]},
	capacity{capacity},
	nStocks{0}
{
}

HashMap::~HashMap(void)
{
	if (slots)
		delete[] slots;
}

HashMap::Slot::Slot() :
	slotStock(Stock()),
	slotState(EMPTY)
{
}

HashMap::Slot::~Slot()
{
}

bool HashMap::get(char const * const symbol, Stock& s,
				  unsigned int& symbolHash, unsigned int& hashIndex,
				  unsigned int& usedIndex, unsigned int& seqLength)
	 const
{
	// If the symbol is not found, this function is required
	// to set usedIndex to -1 before it returns false.

	bool slotFound = false; 
	int uIndex;

	symbolHash = hashStr(symbol);
	uIndex = symbolHash % capacity ;

	hashIndex = uIndex;
	int j = 0;

	while (j < capacity && slotFound == false)
	{
		if ( slots[uIndex].slotState == OCCUPIED )
		{
			if ( strcmp(slots[uIndex].slotStock.stockSymbol, symbol) == 0 )
			{
				slotFound = true;
				usedIndex = uIndex;
				seqLength = j + 1;
			}
			else 
			{
				uIndex = (uIndex +1) % capacity;
				j++;
			}
		}
		else if ( slots[uIndex].slotState == DELETED )
		{
			uIndex = (uIndex +1) % capacity;
			j++;
		}
		else
		{
			seqLength = j + 1;
			usedIndex = -1;
			j = capacity;
		}
	}
	return slotFound;

}

bool HashMap::put(const Stock& s,
				  unsigned int& symbolHash, unsigned int& hashIndex,
				  unsigned int& usedIndex, unsigned int& seqLength)
{

	bool stockFound = false;
	bool stockAdded = false;
	int uIndex;

	symbolHash = hashStr(s.stockSymbol);
	uIndex = symbolHash % capacity ;

	hashIndex = uIndex;
	seqLength = 1;

	if ( nStocks >= capacity )
	{
		return stockAdded;
	}
	else
	{
		hashIndex = ( symbolHash % capacity);

		while (!stockFound)
		{
			if ( slots[uIndex].slotState == OCCUPIED )
			{
				if ( strcmp(slots[uIndex].slotStock.stockSymbol, s.stockSymbol) == 0 )
				{
					return stockAdded;
				}
			}
			else
			{
				slots[uIndex].slotStock.stockSymbol = s.stockSymbol;
				slots[uIndex].slotStock.stockName = s.stockName;
				slots[uIndex].slotStock.stockPrice = s.stockPrice;
				slots[uIndex].slotStock.stockDate = s.stockDate;
				slots[uIndex].slotState = OCCUPIED;

				stockAdded = true;
				usedIndex = uIndex;
				nStocks++;
				return stockAdded;
			}

			uIndex = (uIndex +1) % capacity;
			seqLength++;
		}
	}

	return false;
}

bool HashMap::remove(char const * const symbol, Stock& s,
					 unsigned int& symbolHash, unsigned int& hashIndex,
					 unsigned int& usedIndex, unsigned int& seqLength)
{
	bool stockFound = false;
	bool stockRemoved = false;
	int uIndex;

	symbolHash = hashStr(symbol);
	uIndex = symbolHash % capacity ;
	int j = 0;

	hashIndex = uIndex;
	seqLength = 1;

	if ( nStocks == 0 )
	{
		return stockRemoved;
	}
	else
	{
		hashIndex = ( symbolHash % capacity);

		while (!stockFound && j < capacity)
		{
			if ( slots[uIndex].slotState == OCCUPIED )
			{
				if ( strcmp(slots[uIndex].slotStock.stockSymbol, symbol) == 0 )
				{
					delete slots[uIndex].slotStock.stockSymbol;
					delete slots[uIndex].slotStock.stockName;

					slots[uIndex].slotStock.stockSymbol = NULL;
					slots[uIndex].slotStock.stockName = NULL;
					slots[uIndex].slotStock.stockPrice = 0;
					slots[uIndex].slotStock.stockDate = Date();
					slots[uIndex].slotState = DELETED;

					stockRemoved = true;
					usedIndex = uIndex;
					nStocks--;
					return stockRemoved;
				}
			}

			uIndex = (uIndex +1) % capacity;
			j = seqLength++;
		}
	}


	return false;
}

unsigned int HashMap::hashStr(char const * const s)
{
	// Hash C string argument using the formula in java.lang.String.hashCode():
	//
	//   s[0]*(31^(n-1)) + s[1]*(31^(n-2)) + ... + s[n-1]
	//
	// s is the array of characters, n is the number of characters in the string,
	// and 31^n means 31 to the nth power.
	//
	// This function is declared static because its result depends
	// only on the characters in the string. Apply the modulo 
	// operator to the result of this function to generate
	// the required table index. Do this is in the functions
	// that call this function.

	int strlength = strlen(s);
	int hash = 0;

	for (int idx = 0; idx < strlength; idx++)
	{
		hash = 31 * hash + s[idx];
	}

	return hash;

}

ostream& operator<<(ostream& out, const HashMap &h)
{
	if (h.nStocks != 0)
	{
		out << "symbol  name                                      price   date" << endl
		<< "------  ----                                      -----   ----" << endl;

		for ( int i = 0; i < h.capacity ; i ++ )
		{
			if ( h.slots[i].slotState == 1)
			{
				out << h.slots[i].slotStock;
			}
		}
	}
	else
	{
		out << "no stocks" << endl;
	}

	return out;
}
