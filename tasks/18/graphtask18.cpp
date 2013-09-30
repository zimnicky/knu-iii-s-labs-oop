#include "graphtask18.h"
#include <stack>

vector<vector<uint>> GraphTask18::fundamentalCycles()
{
	vector<vector<uint>> res;
	vector<list<uint>> vertexCopies = vertices;
	vector<bool> visited(vertices.size(), false);

	list<int> st; // it is a stack, but it uses a list to be able to read it
	st.push_back(0);
	visited[0] = true;

	while (!st.empty())
	{
		uint top = st.back();
		if (vertexCopies[top].size() == 0) // there no more edges
		{
			st.pop_back(); // remove the top of the stack
		}
		else
		{
			Edge *e = &edges[*vertexCopies[top].begin()];

			if (!e->deleted) // if the edge isn't deleted
			{
				uint v = ((uint)e->from == top)? e->to: e->from;
				e->deleted = true;   // delete the edge

				if (!visited[v])
				{
					st.push_back(v);
					visited[v] = true;
				}
				else // it is cycle
				{
					vector<uint> cycle;
					cycle.push_back(v);

					auto it = st.rbegin();
					while ((uint)*it != v) // looking for v in the stack
					{
						cycle.push_back(*it);
						it++;
					}
					cycle.push_back(v);

					res.push_back(cycle); // add cycle to the result
				}
			}

			vertexCopies[top].pop_front(); // the front edge is deleted, remove it from the list
		}
	}

	return res;
}

