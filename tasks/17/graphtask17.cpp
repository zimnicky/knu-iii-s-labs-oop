#include "graphtask17.h"



vector<uint> GraphTask17::topsort()
{
	vector<uint> res;
	vector<bool> visited(vertices.size(), false);
	stack<uint> st;

	for (uint v = 0; v < vertices.size(); v++)
		if (!visited[v])
		{
			st.push(v);
			visited[v] = true;

			while (!st.empty())
			{
				uint top = st.top();
				for(uint e: vertices[top])
				{
					if (!visited[edges[e].to])
					{
						visited[edges[e].to] = true; // use edge
						st.push(edges[e].to);
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
	for (uint v: res)		//reverse result
		order.push_back(v);

	return order;
}

vector<vector<uint>> GraphTask17::bicomponents()
{
	vector<vector<uint>> res;

	vector<uint> order = topsort(); // get order of vertices

	vector<bool> visited(vertices.size(), false);

	stack<uint> st;

	for (uint v = 0; v < vertices.size(); v++) // look on vertices in order of topsort
		if (!visited[order[v]])
		{
			st.push(order[v]);
			visited[order[v]] = true;

			vector<uint> component; // current bicomponent

			while (!st.empty())
			{
				uint top = st.top();
				for(uint e: vertices[top])
				{
					if (!visited[edges[e].to])
					{
						visited[edges[e].to] = true; // use edge
						st.push(edges[e].to);
						break;
					}
				}

				if (top == st.top()) // no more edges
				{
					component.push_back(top);
					st.pop();
				}
			}

			res.push_back(component);
		}

	return res;
}


void GraphTask17::addEdge(uint v1, uint v2)
{
	if (v1 >= vertices.size())
		vertices.resize(v1+1);
	if (v2 >= vertices.size())
		vertices.resize(v2+1);

	Edge e(v1,v2);

	edges.push_back(e);

	vertices[v1].push_back(edges.size() - 1);
}
