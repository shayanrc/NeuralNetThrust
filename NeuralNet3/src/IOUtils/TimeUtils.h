/*
 * TimeUtils.h
 *
 *  Created on: 01-Feb-2014
 *      Author: xion
 */

#include <ctime>
#include <string>
#ifndef TIMEUTILS_H_
#define TIMEUTILS_H_

typedef struct tm Time;
/*
time_t makeDate( int day, int month, int year )
{
    struct tm ttm = {0};
    ttm.tm_mday= day;
    ttm.tm_mon= month-1;
    ttm.tm_year= year-1900;
    return mktime(&ttm);
}
*/

Time makeDate( int day, int month, int year );
Time makeDate(std::string);


#endif /* TIMEUTILS_H_ */
