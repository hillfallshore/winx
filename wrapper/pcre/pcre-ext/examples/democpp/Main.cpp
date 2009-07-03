/* -------------------------------------------------------------------------
// CppModel: C++ DOM Model
// 
// Module: pp/Main.cpp
// Creator: xushiwei
// Email: xushiweizh@gmail.com
// Date: 2009-3-26 19:41:58
// 
// $Id: Main.cpp 619 2008-06-01 16:00:35Z xushiweizh $
// -----------------------------------------------------------------------*/

#include <wrapper/pcrecpp.h>
#include <wrapper/pcrecpp.cpp>

// =========================================================================

int main(int argc, const char* argv[])
{
	int i;
	string s;
	pcrecpp::RE re("(\\w+):(\\d+)");
	re.FullMatch("ruby:1234", &s, &i);
	std::cout << s << "\n" << i << "\n";
	return 0;
}

// =========================================================================
