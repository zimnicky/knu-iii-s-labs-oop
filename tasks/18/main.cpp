#include <iostream>
#include <fstream>
#include "graphtask18.h"

using namespace std;

void read(istream &in, GraphTask18 &g)
{
	uint e, v, t;
	in >> v >> e;
	for (uint i = 0; i < e; i++)
		for (uint j = 0; j < v; j++)
		{
			in >> t;
			if (t > 0)
				g.addIncedenceRelation(i, j);
		}

}

void write(ostream &out, const vector<vector<uint>> &data)
{
	for (auto i: data)
	{
		for (uint j: i)
			out << j << " ";
		out << endl;
	}
}

int main()
{
	GraphTask18 g;
	ifstream in("input.txt");
	read(in, g);
	in.close();

	auto cycles = g.fundamentalCycles();

	write(cout, cycles);

	return 0;
}

