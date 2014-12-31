#ifndef H1266941D_BD17_4A9E_AA65_CA9DBB5F4B11
#define H1266941D_BD17_4A9E_AA65_CA9DBB5F4B11

#include <stdio.h>

#ifdef _MSC_VER
# define VSNPRINTF _vsnprintf
# define SNPRINTF  _snprintf
# define SEPERATOR '\\'
#else
# define VSNPRINTF vsnprintf
# define SNPRINTF  snprintf
# define SEPERATOR '/'
#endif

#endif
