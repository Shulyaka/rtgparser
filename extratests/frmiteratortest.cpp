#include <linux/limits.h>
#include <err.h>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>

#include "parser.h"

using namespace std;

#ifdef DEBUG
bool debug=true;
#else
bool debug=false;
#endif

int main(void)
try
{
	fldformat frm("../formats/fields_mast.frm");
	
	fldformat::iterator i=frm.begin();
	fldformat::const_iterator j=i;

	for(; i!=frm.end(); ++i, ++j)
	{
		if(i!=j)
			throw runtime_error("Iterator mismatch");
	}
	
	if(j!=frm.end())
		throw runtime_error("Second iterator did not reach end");

	const fldformat cfrm(frm);

	j=cfrm.begin();
	fldformat::const_iterator k=j;

	for(; j!=cfrm.end(); ++k, ++j)
	{
		if(j!=k)
			throw runtime_error("Iterator mismatch");

		if(*j!=*k)
			throw runtime_error("Iterator dereference mismatch");
	}
	
	if(i!=frm.end())
		throw runtime_error("Second iterator did not reach end");

	return 0;
}
catch(const exception& e)
{
	printf("Error: Unhandled exception: %s\n", e.what());
	return 3;
}
catch(...)
{
	printf("Error: Unhandled exception\n");
	return 3;
}
