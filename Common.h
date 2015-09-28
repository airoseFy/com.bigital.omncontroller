#ifndef _COMMON_H_
#define _COMMON_H_

// headers of standard C libs

/*-------------------------------------------------
|	MAGIC CODE Indentify BGT Protocol
--------------------------------------------------*/
#ifndef PROTOCOL_MAGIC
#define PROTOCOL_MAGIC	0xEA	
#endif

/*-------------------------------------------------
|	Version
--------------------------------------------------*/
#ifndef MAJOR_VERSION
#define	MAJOR_VERSION	1
#endif

#ifndef MINOR_VERSION
#define MINOR_VERSION	0
#endif

#define MAKE_VERSION(major, minor) ((major << 8)+minor)

#ifdef __cplusplus
inline int MakeVersion(int major, int minor)
{
	return ((major << 8) + minor);
}
#endif

#endif //_COMMON_H_