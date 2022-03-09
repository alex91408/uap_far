#include <windows.h>
#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>         /* For _MAX_PATH definition */
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <time.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#ifdef NON_XML
#else
	#include <util/PlatformUtils.hpp>
	#include <dom/DOM.hpp>
	#include <parsers/DOMParser.hpp>
	#include <dom/DOM_DocumentType.hpp>
	#include <dom/DOM_DOMException.hpp>
	#include <util/XMLNetAccessor.hpp>
	#include <framework/URLInputSource.hpp>
	#include <framework/LocalFileInputSource.hpp>
	#include <framework/MemBufInputSource.hpp>
#endif

#ifdef OTS_UTIL
	#define OTS_UTIL_API __declspec(dllexport)
#else
	#define OTS_UTIL_API __declspec(dllimport)
	#include <otsString.h>
	#include <otsMutex.h>
  #include <otsEvent.h>
	#include <otsTime.h>
	#include <otsStruct.h>
	#include <otsVarList.h>
	#include <otsNodeVarList.h>
	#include <otsNode.h>
	#include <otsNodeList.h>
	#include <otsParser.h>
	OTS_UTIL_API otsString& operator +(char * strbuff , otsString& str);
#endif

