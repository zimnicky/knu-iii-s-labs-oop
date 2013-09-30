#include <iostream>
#include <cstdio>
#include "graphtask17.h"

using namespace std;

void read(istream &in, GraphTask17 &g)
{
	uint u, v, t;

	while (in >> v)
	{
		in >> t;
		for (uint i = 0; i < t; i++)
		{
			in >> u;
			g.addEdge(v, u);
		}
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
	freopen("input.txt", "r", stdin);
	GraphTask17 g;
	read(cin, g);

	auto components = g.bicomponents();

	write(cout, components);

	return 0;
}

