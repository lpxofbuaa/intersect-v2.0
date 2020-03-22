#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "GeometryShape.h"
#include "GeometryStatistic.h"

using namespace std;

class Reader {
private:
	ifstream *reader=NULL;
	ofstream *writer=NULL;
	GeometryFactory *g;
	void command_analysis(int argc, char* argv[]);
	void error_handle(string message, int type=-1);
public:
	Reader(int argc, char* argv[], GeometryFactory *g);
	void exec();
	void dump();
	void debug();
};