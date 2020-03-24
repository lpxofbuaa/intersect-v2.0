#include "Reader.h"
#include "StdInterface.h"
#include <regex>
#include <sstream>
#include <cstdio>
//#pragma comment(lib,"GeometryCore.lib")

Reader::Reader(int ac, char* av[]) {
	fig = addFigure();
	// reader = new ifstream("28190067or6.txt");
	command_analysis(ac, av);
}

void Reader::command_analysis(int ac, char* av[]) {
	for (int i = 1; i < ac; ++i) {
		if (strlen(av[i]) == 2 && av[i][0] == '-' && av[i][1] == 'i') {
			if (reader == NULL) {
				if (i + 1 < ac) {
					this->filename = av[i + 1];
					this->reader = new ifstream(this->filename);
					if (not this->reader->is_open()) {
						error_handle(string("Open file " + this->filename + " fail!"), 0);
					}
					++i;
				}
				else {
					error_handle("Please give the input filename after parameter -i!", 0);
				}
			}
			else {
				error_handle("-i parameter can only be given once!", 0);
			}
		}
		else if (strlen(av[i]) == 2 && av[i][0] == '-' && av[i][1] == 'o') {
			if (writer == NULL) {
				if (i + 1 < ac) {
					string filename = av[i + 1];
					this->writer = new ofstream(filename);
					if (not this->writer->is_open()) {
						error_handle("Open file " + filename + " fail!", 0);
					}
					++i;
				}
				else {
					error_handle("Please give the output filename after parameter -o!", 0);
				}
			}
			else {
				error_handle("-o parameter can only be given once!", 0);
			}
		}
		else {
			error_handle("Invalid parameter!\nPlease type command like the following format:\n\tintersect.exe [-i] <input filename> [-o] <output filename>", 0);
		}
	}
}

void Reader::error_handle(string message, int type)
{
	if (type == 0) {
		cerr << "The program has been interrupt when analyzing command line parameter, here are the error messages:" << endl << endl;
		cerr << message << endl;
		exit(0);
	}
	else {
		cerr << "The program has been interrupt when executing calculator, here are the error messages:" << endl << endl;
		cerr << message << endl;
		exit(0);
	}
}

void Reader::exec() {
	ERROR_INFO ret;
	if (reader != NULL) {
		ret = addShapesToFigureFile(fig, (char*)filename.c_str());
	}
	else {
		ret = addShapesToFigureStdin(fig);
	}
	if (ret.code != SUCCESS) {
		error_handle(string(ret.messages));
	}
}

void Reader::dump() {
	streambuf *coutbackup = NULL;
	if (writer != NULL) {
		coutbackup = cout.rdbuf(writer->rdbuf());
	}
	cout << getPointsCount(fig) << endl;
	if (coutbackup != NULL) {
		cout.rdbuf(coutbackup);
	}
}

void Reader::debug() {
	updatePoints(fig);
	// cout << results.size() << endl;
	//cout << g->getPointsCount() << endl;
	int count = getPointsCount(fig);
	for (int i = 0; i < count; ++i) {
		printf("%.3lf,%.3lf\n",fig->points[i].x, fig->points[i].y);
	}
}
