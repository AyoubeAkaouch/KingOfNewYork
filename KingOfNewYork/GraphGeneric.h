#pragma once
#include <Vector>
using namespace std;

template <typename T>
class GraphGeneric
{
private:
	vector<vector<T>> adjacentList;
	int findObjectPosition(T object);
	int findConnection(int position, T object);

public:
	GraphGeneric();
	GraphGeneric(T node);
	~GraphGeneric();
	void addEdge(T node1, T node2);
	void displayGraph();
	template<typename T> friend ostream& operator<<(ostream& os, const GraphGeneric<T>& graph);

};

