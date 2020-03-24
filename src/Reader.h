#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "StdInterface.h"

using namespace std;

class Reader {
private:
	ifstream *reader=NULL;
	ofstream *writer=NULL;
	gFigure *fig;
	string filename;
	void command_analysis(int argc, char* argv[]);
	void error_handle(string message, int type=-1);
public:
	Reader(int argc, char* argv[]);
	void exec();
	void dump();
	void debug();
};