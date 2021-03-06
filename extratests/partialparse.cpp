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
	const char data[] = "../tests/mast_moneysend";
	field message("../formats/fields_mast.frm", "");

	if(debug)
		message.print_format();

	std::ifstream infile(data);
	if(!infile)
		err(4, "Cannot open file %s", data);

	std::string msgbuf((std::istreambuf_iterator<char>(infile)), (std::istreambuf_iterator<char>()));

	infile.close();

	size_t msglen1=msgbuf.length();

	try
	{
		for(size_t msglen=0; msglen<msglen1; msglen++)
			try
			{
				if(debug)
					printf("Parsing message with length %lu...\n", (unsigned long)msglen);

				message.parse(msgbuf.c_str(), msglen);
				message.print_message();
				throw length_error("Successfully parsed the message but only part of the buffer was provided");
			}
			catch(const need_more_data& e)
			{
				if(debug)
					printf("Requested %lu bytes. Actual length: %lu.\n", (unsigned long)e.howmuch(), (unsigned long)msglen1);

				if(e.howmuch()<=msglen || e.howmuch() > msglen1)
					throw out_of_range("Requested length is out of allowed range");
			}
	}
	catch(const exception& e)
	{
		printf("Error: %s\n", e.what());
		return 2;
	}

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
