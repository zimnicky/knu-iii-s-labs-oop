#include "graph.h"

void Graph::addIncedenceRelation(uint edgeNum, uint vertexNum)
{
    if (edges.size() <= edgeNum)
        edges.resize(edgeNum + 1);
	if (vertices.size() <= vertexNum)
		vertices.resize(vertexNum + 1);

    if (edges[edgeNum].from < 0)
        edges[edgeNum].from = vertexNum;
    else
        edges[edgeNum].to = vertexNum;

	vertices[vertexNum].push_back(edgeNum);

}

vector<uint> Graph::eulerianPath()
{
    int startV = -1;

	vector<list<uint>> vertexCopies = vertices;

	for (uint i = 0; i < vertices.size() && startV == -1; i++)
		if ((vertices[i].size() & 1) == 0)
            startV = i;

    stack<int> st;
    st.push(startV);

    vector<uint> res;

    while (!st.empty())
    {
        uint top = st.top();
        if (vertexCopies[top].size() == 0) // there no more edges
        {
            res.push_back(st.top()); // add vertex to the path
            st.pop(); // remove it from the stack
        }
        else
        {
            Edge *e = &edges[*vertexCopies[top].begin()];
            if (!e->deleted) // if edge isn't deleted
            {
                uint v = ((uint)e->from == top)? e->to: e->from;

                st.push(v);         // use edge
                e->deleted = true;   // & delete it
            }
            vertexCopies[top].pop_front(); // the front edge is deleted, remove it from the list
        }
    }
    return res;
}
