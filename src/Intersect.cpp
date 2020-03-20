#include <iostream>
#include <cstdio>
#include "GeometryCalculator.h"
#include "Reader.h"
//#pragma comment(lib,"GeometryCore.lib")

using namespace std;

int main(int argc, char* argv[])
{
	Reader r(argc, argv, new GeometryFactory());
	r.exec();
	r.dump();
}




