#ifndef _HASHMAP_H_
#define _HASHMAP_H_
#include "stock.h"

class HashMap
{
public:
	static const char	YOUR_NAME[];	// used for printing out my name

	HashMap(int capacity);
	~HashMap(void);

	// Gets the stock associated with the provided stock symbol from the HashMap,
	// returns true if successful, false if not.
	//
	// Additional data returned:
	//		symbolHash:	result of applying hashStr() to stock symbol
	//		hashIndex:	array index produced by applying the modulo operator
	//						to the hash value produced by hashStr()
	//		usedIndex:	array index where the stock was actually found
	//		seqLength:	length of the linear probe sequence to the stock
	bool get(char const * const symbol, Stock& s,
			 unsigned int& symbolHash, unsigned int& hashIndex,
			 unsigned int& usedIndex, unsigned int& seqLength)
			 const;

	// Adds the stock to the HashMap, returns true if successful,
	// false if not (if the symbol is already present as a key or
	// if the hash table was already full).
	//
	// Additional data returned:
	//		symbolHash:	result of applying hashStr() to stock symbol
	//		hashIndex:	array index produced by applying the modulo operator
	//						to the hash value produced by hashStr()
	//		usedIndex:	array index where the stock will actually be stored
	//		seqLength:	length of the linear probe sequence to the stock
	bool put(const Stock& s,
			 unsigned int& symbolHash, unsigned int& hashIndex,
			 unsigned int& usedIndex, unsigned int& seqLength);

	// Removes the stock associated with the provided symbol from the HashMap,
	// returns true if successful, false if not (if the symbol is not present as a key).
	// Returns a copy of the stock in s.
	//
	// Additional data returned:
	//		symbolHash:	result of applying hashStr() to stock symbol
	//		hashIndex:	array index produced by applying the modulo operator
	//						to the hash value produced by hashStr()
	//		usedIndex:	array index where the stock was actually found
	//		seqLength:	length of the linear probe sequence to the stock
	bool remove(char const * const symbol, Stock &s,
				unsigned int& symbolHash, unsigned int& hashIndex,
				unsigned int& usedIndex, unsigned int& seqLength);

	// 'Prints' the contents of the HashMap into the specified output stream.
	friend std::ostream& operator<<(std::ostream& out, const HashMap &h);

private:
	static unsigned int hashStr(char const * const symbol);		// hashing function

	enum locationState { EMPTY, OCCUPIED, DELETED };

	struct Slot
	{
		Slot();
		~Slot();
		
		Stock	slotStock;
		locationState slotState;
	};

	Slot	*slots;							// array of instances of slot
	int		capacity;						// number of slots in array
	int		nStocks;						// current number of stocks stored in hash table
	int		tmpVar;
};

#endif
