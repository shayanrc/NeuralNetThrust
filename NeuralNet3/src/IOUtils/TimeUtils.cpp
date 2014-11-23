#include "TimeUtils.h"

Time makeDate( int day, int month, int year )
{
    Time ttm = {0};
    ttm.tm_mday= day;
    ttm.tm_mon= month-1;
    ttm.tm_year= year-1900;
    return ttm;
}

Time makeDate(std::string const dateString)
{
Time date;
//TODO Parse string into struct tm date
return date;
}
