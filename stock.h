#ifndef _STOCK_H_
#define _STOCK_H_
#include "date.h"

class Stock
{
public:
	Stock(char const * const symbol, char const * const name, int sharePrice, Date priceDate);
		// sharePrice is given as a number of CENTS
	Stock(void);								// default constructor
	~Stock(void);								// destructor
	
  char const * const getSymbol(void) const;	// returns a pointer to the symbol string
	Stock(const Stock& s);						// copy constructor
	Stock& operator=(const Stock& s);			// operator= overload
	Stock& operator=(Stock const * const s);	// another operator= overload

	// display column headers for printout of stocks
	static void displayHeaders(std::ostream& out);
	friend std::ostream& operator<<(std::ostream& out, const Stock& s);

	friend class HashMap;

private:
	char	*stockSymbol;
	char	*stockName;
	int		stockPrice;
	Date	stockDate;

};

#endif
