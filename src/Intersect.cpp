#include <iostream>
#include <cstdio>
#include "Reader.h"
//#pragma comment(lib,"GeometryCore.lib")

using namespace std;

int main(int argc, char* argv[])
{
	Reader r(argc, argv);
	r.exec();
	r.dump();
	// r.debug();
}




