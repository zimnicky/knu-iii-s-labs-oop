#include "graphtask27.h"



vector<uint> GraphTask27::topsort()
{
	vector<uint> res;
	vector<bool> visited(vertices.size(), false);
    MNumber.resize(vertices.size(), 0);
	stack<uint> st;

    uint number = 1;        // M-number of current vertex

	for (uint v = 0; v < vertices.size(); v++)
		if (!visited[v])
		{
			st.push(v);
			visited[v] = true;
            MNumber[v] = number++; // set M-number

			while (!st.empty())
			{
				uint top = st.top();

				for(uint e: vertices[top])
				{
					if (!visited[edges[e].to])
					{
						visited[edges[e].to] = true; // use edge
						st.push(edges[e].to);
                        MNumber[edges[e].to] = number++; // set M-number
						break;
					}
				}

				if (top == st.top()) // no more edges
				{
					res.push_back(top);
					st.pop();
				}
			}
		}

	vector<uint> order;
    for (int i = res.size() - 1; i >= 0; i--)		//reverse result
        order.push_back(res[i]);

    return order;
}

void GraphTask27::getNumering(vector<uint> &M, vector<uint> &T) // returns M-numbering & T-numbering
{
    vector<vector<uint>> components = bicomponents(); // bicomponents were built using N-numbering, it's right order

    uint currentTNumber = 1;

    T.resize(vertices.size());
    for (uint i = 0; i < components.size(); i++)
    {
        T[components[i][components[i].size() - 1]] = currentTNumber++; // first vertex in bicomponent
        for (uint j = 0; j < components[i].size() - 1; j++)
            T[components[i][j]] = currentTNumber++;
    }

    M = MNumber;
}
