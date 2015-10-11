//
//  Utils.h
//  Bigital
//
//  Created by bigital on 10/11/15.
//
//

#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>
using namespace std;

static string& ReplaceAll(string& src, const char origin, const char replace)
{
    for (auto it = src.begin(); it != src.end(); ++it) {
        if(*it == origin) *it = replace;
    }
    return src;
}

static string& Trim(string& src)
{
    const char space = ' ';
    for (auto it = src.begin(); it != src.end(); ++it) {
        if(*it == space) src.erase(it);
    }
    return src;
}
#endif /* _UTILS_H_ */
