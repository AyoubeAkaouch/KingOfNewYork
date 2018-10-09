#pragma once
#include <Vector>
using namespace std;

template <typename T>
class GraphGeneric //Directed graph implementation
{
private:
	vector<vector<T>> adjacentList;
	int findObjectPosition(T object);
	int findConnection(int position, T object);
	vector<T> allNodes;

public:
	GraphGeneric();
	GraphGeneric(T node);
	~GraphGeneric();
	int addEdge(T node1, T node2);
	vector<T> getConnections(T node);
	vector<T> getAllNodes();
	template<typename T> friend ostream& operator<<(ostream& os, const GraphGeneric<T>& graph);

};

