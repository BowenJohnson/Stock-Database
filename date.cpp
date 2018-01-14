#include "date.h"

using namespace std;

Date::Date(Month month, int day, int year) :

	month{month},
	day{day},
	year{year}
{
}

Date::Date() :

	month{INVALID},
	day{0},
	year{0}
{
}

Date::~Date(void)
{
}

ostream& operator<<(ostream& out, const Date& d)
{
	//changed from const char* const MonthNames[]

	 const char* const MonthNames[] = { "", "January", "February", "March", "April", "May",
										"June", "July", "August", "September", "October",
										"November", "December"};

	out << MonthNames[d.month - 1] << ' ' << d.day << ", " << d.year; 
	//added -1 to get rid of the empty sting at the begining

	return out;
}
