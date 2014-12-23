#include "tinyxml.h"

#ifdef TIXML_USE_STL
  #include <iostream>
  #include <fstream>
  using namespace std ;

  int main()
  {
	  const char* demoXML =
		"<TODO>"
		"<template>"
		"  <Item name=\"zxw\", age=18></Item>"
		"</template>"
		"</TODO>" ;

		printf("TINYXML_USER_STL\n") ;
	
  TiXmlDocument xmldoc( "xmldemo.xml") ;
	xmldoc.Parse(demoXML) ;
	if( xmldoc.Error() )
	{
		printf("Error in %s: %s\n", xmldoc.Value(), xmldoc.ErrorDesc()) ;
		exit(1) ;
	}
	xmldoc.SaveFile() ;

	
	return 0 ;
}
#else
  #include <stdio.h>
int main()
{
	const char* demoXML =
		"<TODO>"
		"<template>"
		"  <Item name=\"zxw\", age=18></Item>"
		"</template>"
		"</TODO>" ;

 	
  TiXmlDocument xmldoc( "xmldemo.xml") ;
	xmldoc.Parse(demoXML) ;
	if( xmldoc.Error() )
	{
		printf("Error in %s: %s\n", xmldoc.Value(), xmldoc.ErrorDesc()) ;
		exit(1) ;
	}
	xmldoc.SaveFile() ;
	
	return 0 ;
}
#endif

