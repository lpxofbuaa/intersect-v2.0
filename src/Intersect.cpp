#include <iostream>
#include <cstdio>
#include "GeometryCore.h"
#include "Reader.h"


using namespace std;

int main(int argc, char* argv[])
{
	Reader r(argc, argv, new GeometryFactory());
	r.exec();
	r.dump();
	// r.debug();
}




