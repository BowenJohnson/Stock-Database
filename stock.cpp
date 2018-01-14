#include <iomanip>
#include <iostream>
#include "stock.h"
#include <string.h>

using namespace std;

Stock::Stock(char const * const symbol, char const * const name, int sharePrice, Date priceDate) : 
	stockSymbol{NULL},
	stockName{NULL},
	stockPrice{0},
	stockDate{Date()}   
{
	
	if (this->stockName)
		delete [] this->stockName;
	this->stockName = new char[strlen(name) +1];
	strcpy(this->stockName, name);
	if (this->stockSymbol)
		delete [] this->stockSymbol;
	this->stockSymbol = new char[strlen(symbol) +1];
	strcpy(this->stockSymbol, symbol);

	stockPrice = sharePrice;
	stockDate = priceDate;

}

Stock::Stock(void) :
	stockSymbol{NULL},
	stockName{NULL},
	stockPrice{0},
	stockDate{Date()}
{
}

Stock::~Stock(void)
{
}

char const * const Stock::getSymbol(void) const
{
	return stockSymbol;
}

Stock::Stock(const Stock& s)
{
	stockSymbol = NULL;
	stockName = NULL;

	if (this->stockName)
		delete [] this->stockName;
	this->stockName = new char[strlen(s.stockName) +1];
	strcpy(this->stockName, s.stockName);
	
	if (this->stockSymbol)
		delete [] this->stockSymbol;
	this->stockSymbol = new char[strlen(s.stockSymbol) +1];
	strcpy(this->stockSymbol, s.stockSymbol);

	stockPrice = s.stockPrice;
	stockDate = s.stockDate;
	
}
/*
Stock& Stock::operator=(const Stock& s)
{
	return *this;
}

Stock& Stock::operator=(Stock const * const s)
{
	return *this;
}
*/

// display column headers for printout of stocks
void Stock::displayHeaders(ostream& out)
{
	// print something like this:
	//
	// symbol  name                                      price   date;
	// ------  ----                                      -----   ----;

}

// print share price as DOLLARS
ostream& operator<<(ostream& out, const Stock& s)
{

	out << setw(8) << s.stockSymbol
		<< setw(41) << s.stockName 
		<< right << setw(3) << s.stockPrice / 100 << ".";

		if ( s.stockPrice % 100 < 10 )
		{
			out << "0";
		}

		out << s.stockPrice % 100 << "   "
			<< left << s.stockDate
			<< endl;


	return out;
}
