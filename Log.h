#ifndef _LOG_H_
#define _LOG_H_

#include <stdarg.h>

#ifdef __ANDROID__
#include <string>
#include "android/log.h"
#else
#include <stdio.h>
#include <stdlib.h>	
#endif

#define DEBUG 1

inline void debug(const char* tag, const char* format, ...)
{
	if(!DEBUG) return ;
	va_list arg;
	va_start(arg, format);
	
	#ifdef __ANDROID__
		std::string _tag(tag);
		_tag = "|@@bigital@@|##" + _tag + "##| = ";
		__android_log_print(ANDROID_LOG_DEBUG, _tag.c_str(), format, arg);		
	#else
		fprintf(stdout, "|@@bigital@@|");
		fprintf(stdout, "|##%s##| = ", tag);
		fprintf(stdout, format, arg);
	#endif
	
	va_end(arg);
}

inline void error(const char* tag, const char* format, ...)
{
	va_list arg;
	va_start(arg, format);
	
	#ifdef __ANDROID__
		std::string _tag(tag);
		_tag = "|@@bigital@@|##" + _tag + "##| = ";
		__android_log_print(ANDROID_LOG_ERROR, _tag.c_str(), format, arg);
		va_end(arg);
	#else
		fprintf(stderr, "|@@bigital@@|");
		fprintf(stderr, "|##%s##| = ", tag);
		fprintf(stderr, format, arg);
	#endif	
	
	va_end(arg);
}
#endif /*_LOG_H_*/