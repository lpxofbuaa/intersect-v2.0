#include "Reader.h"
#include <regex>
#include <sstream>
#include <cstdio>
#include "GeometryCore.h"

Reader::Reader(int ac, char* av[], GeometryFactory *gg) {
	g = gg;
	// reader = new ifstream("28190067or6.txt");
	command_analysis(ac, av);
}

void Reader::command_analysis(int ac, char* av[]) {
	for (int i = 1; i < ac; ++i) {
		if (strlen(av[i]) == 2 && av[i][0] == '-' && av[i][1] == 'i') {
			if (reader == NULL) {
				if (i + 1 < ac) {
					string filename = av[i + 1];
					this->reader = new ifstream(filename);
					if (not this->reader->is_open()) {
						error_handle(string("Open file " + filename + " fail!"), 0);
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
	streambuf *cinbackup=NULL;
	int lines = 1;
	if (reader != NULL) {
		cinbackup = cin.rdbuf(reader->rdbuf());
	}
	string line;
	getline(cin, line);
	regex number("^\\d+$");
	int n = 0;
	if (regex_match(line, number)) {
		stringstream s(line);
		s >> n;
	}
	else {
		error_handle("We got the wrong message at line 1:\n\tPlease give the total of the objects");
	}
	for (int i = 0; i < n; ++i) {
		++lines;
		getline(cin, line);
		try {
			this->g->addObjectFromFile(line.c_str());
		}
		catch (exception &e) {
			error_handle("We got something wrong at line " + to_string(lines) + ":\n\t" + string(e.what()));
		}
		
	}
	if (cinbackup != NULL) {
		cin.rdbuf(cinbackup);
	}
}

void Reader::dump() {
	streambuf *coutbackup = NULL;
	if (writer != NULL) {
		coutbackup = cout.rdbuf(writer->rdbuf());
	}
	cout << this->g->getPointsCount() << endl;
	if (coutbackup != NULL) {
		cout.rdbuf(coutbackup);
	}
}

void Reader::debug() {
	double *px = new double[g->getPointsCount()];
	double *py = new double[g->getPointsCount()];
	g->getPoints(px, py, g->getPointsCount());
 	// cout << results.size() << endl;
	//cout << g->getPointsCount() << endl;
	for (auto i = 0; i != g->getPointsCount(); ++i) {
		// printf("??\n");
		printf("%.3lf,%.3lf\n", px[i], py[i]);
	}
}
