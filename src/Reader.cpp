#include "Reader.h"
#include <regex>
#include <sstream>
//#pragma comment(lib,"GeometryCore.lib")

Reader::Reader(int argc, char* argv[], GeometryFactory *gg) {
	g = gg;
	command_analysis(argc, argv);
}

void Reader::command_analysis(int argc, char* argv[]) {
	for (int i = 1; i < argc; ++i) {
		if (strlen(argv[i]) == 2 && argv[i][0] == '-' && argv[i][1] == 'i') {
			if (reader == NULL) {
				if (i + 1 < argc) {
					string filename = argv[i + 1];
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
		else if (strlen(argv[i]) == 2 && argv[i][0] == '-' && argv[i][1] == 'o') {
			if (writer == NULL) {
				if (i + 1 < argc) {
					string filename = argv[i + 1];
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
		cout << "The program has been interrupt when analyzing command line parameter, here are the error messages:" << endl << endl;
		cout << message << endl;
		exit(0);
	}
	else {
		cout << "The program has been interrupt when executing calculator, here are the error messages:" << endl << endl;
		cout << message << endl;
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
	int n;
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
			this->g->addObjectFromFile(line);
		}
		catch (CoordinateRangeException e) {
			error_handle("We got something wrong at line " + to_string(lines) + ":\n\t" + string(e.what()));
		}
		catch (CoordinateCoincidenceException e) {
			error_handle("We got something wrong at line " + to_string(lines) + ":\n\t" + string(e.what()));
		}
		catch (LineCoincidenceException e) {
			error_handle("We got something wrong at line " + to_string(lines) + ":\n\t" + string(e.what()));
		}
		catch (CircleCoincidenceException e) {
			error_handle("We got something wrong at line " + to_string(lines) + ":\n\t" + string(e.what()));
		}
		catch (NegativeRadiusException e) {
			error_handle("We got something wrong at line " + to_string(lines) + ":\n\t" + string(e.what()));
		}
		catch (UndefinedLineException e) {
			error_handle("We got something wrong at line " + to_string(lines) + ":\n\t" + string(e.what()));
		}
		catch (ObjectNotFoundException e) {
			error_handle("We got something wrong at line " + to_string(lines) + ":\n\t" + string(e.what()));
		}
		catch (WrongFormatException e) {
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