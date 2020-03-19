#include "stdafx.h"
#include "Reader.h"

Reader::Reader(string in_file, string out_file, GeometryFactory *gg) {
	reader = ifstream(in_file);
	writer = ofstream(out_file);
	g = gg;
}

void Reader::read() {
	int n;
	reader >> n;
	for (int i = 0; i < n; ++i) {
		char type;
		reader >> type;
		if (type == 'L') {
			long long x1, y1, x2, y2;
			reader >> x1 >> y1 >> x2 >> y2;
			g->addLine(DOUBLE_INFINITE_LINE, x1, x2, y1, y2);
			//lines.push_back(Line(x1, y1, x2, y2));
		}
		else if (type == 'R') {
			long long x1, y1, x2, y2;
			reader >> x1 >> y1 >> x2 >> y2;
			g->addLine(SINGLE_INFINITE_LINE, x1, x2, y1, y2);
		}
		else if (type == 'S') {
			long long x1, y1, x2, y2;
			reader >> x1 >> y1 >> x2 >> y2;
			g->addLine(LIMITED_LINE, x1, x2, y1, y2);
		}
		else if (type == 'C') {
			long long a, b, r;
			reader >> a >> b >> r;
			g->addCircle(a, b, r);
			//circles.push_back(Circle(a, b, r));
		}
	}
}

void Reader::write(int m) {
	writer << to_string(m) << endl;
}