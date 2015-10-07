#ifndef _LOG_H_
#define _LOG_H_

#include <stdarg.h>

#ifdef __ANDROID__
#include <string>
#include <string.h>
#include "android/log.h"
#else
#include <stdio.h>
#include <stdlib.h>	
#endif

#define DEBUG 1

inline void debug(const char* tag, const char* format, ...)
{
	if(!DEBUG) return ;
	va_list args;
	va_start(args, format);
	
	#ifdef __ANDROID__
		std::string _tag("|@@bigital@@|##");
		_tag += tag;
		_tag += "##| = ";
		__android_log_vprint(ANDROID_LOG_DEBUG, _tag.c_str(), format, args);	
	#else
		fprintf(stdout, "|@@bigital@@|");
		fprintf(stdout, "|##%s##| = ", tag);
		vfprintf(stdout, format, args);
        fprintf(stdout, "\n");
	#endif
	
	va_end(args);
}

inline void error(const char* tag, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	
	#ifdef __ANDROID__
		std::string _tag(tag);
		_tag = "|@@bigital@@|##" + _tag + "##| = ";
		__android_log_print(ANDROID_LOG_ERROR, _tag.c_str(), format, args);
	#else
		fprintf(stderr, "|@@bigital@@|");
		fprintf(stderr, "|##%s##| = ", tag);
		vfprintf(stderr, format, args);
        fprintf(stderr, "\n");
	#endif
	
	va_end(args);
}
#endif /*_LOG_H_*/
