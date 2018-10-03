#include "GraphGeneric.h"
#include<vector>
#include<iostream>
#include<string>

using namespace std;


template<typename T>
GraphGeneric<T>::GraphGeneric()
{

}

template<typename T>
GraphGeneric<T>::GraphGeneric(T node)//Initialize with only one node
{
	adjacentList.push_back({ node });
}

template<typename T>
GraphGeneric<T>::~GraphGeneric()
{
}

template<typename T>
void GraphGeneric<T>::addEdge(T node1, T node2)
{
	int positionNode1 = findObjectPosition(node1);


	if (node1==node2) 
	{
		cout << "Can't add a connection to itself"<<endl;
	}
	else if (positionNode1 == -1) //If node1 is not first position in any vector object, it doesnt have any connections to a node yet (Might have from a node tho)
	{
		adjacentList.push_back({ node1, node2});
	}
	else if (positionNode1 != -1 && findConnection(positionNode1,node2)!=-1) //Check that this connection doesn't already exist. If exist do not add it again.
	{
		cout << "This connection already exists, can't add it again." << endl;
	}
	else // Add the connection if everything passes
	{
		adjacentList[positionNode1].push_back(node2);
	}
	
}


template<typename T>
int GraphGeneric<T>::findObjectPosition(T ptr)
{
	
	for (size_t i = 0; i < adjacentList.size(); i++) {
		if (adjacentList[i][0]== ptr) return i;
	}
	
	return -1;
}

template<typename T>
int GraphGeneric<T>::findConnection(int position, T object)
{
	for (size_t i = 0; i < adjacentList[position].size(); i++) {
		if (adjacentList[position][i] == object) return i;
	}
	return -1;
}

template<typename T>
ostream& operator<<(ostream & os, const GraphGeneric<T>& graph)
{
	for (size_t i = 0; i < graph.adjacentList.size(); i++) {
		for (size_t j = 0; j < graph.adjacentList[i].size(); j++) {
			os << graph.adjacentList[i][j]<<"->";
		}
		os << endl;
	}

	return os;
}

template<typename T>
void GraphGeneric<T>::displayGraph()
{
	
	for (size_t i = 0; i < adjacentList.size();i++ ) {
		for (size_t j = 0; j < adjacentList[i].size();j++) {
			cout << adjacentList[i][j];
		}
		cout << endl;
	}
	
}
int main() {

	string x = "x";
	string y = "y";
	string z = "z";
	string w = "w";
	string v = "v";

	GraphGeneric<string> graph=GraphGeneric<string>(x);
	//Was coding addEdge and wondering if I should make it directed or not.(Leaning towards directed)
	//graph.addEdge(x, y);
	cout << graph;

	graph.addEdge(x, v);
	graph.addEdge(y, x);
	graph.addEdge(x, v);
	graph.addEdge(w, z);
	graph.addEdge(x, v);
	graph.addEdge(z, v);
	graph.addEdge(v, v);


	cout << graph;
	//graph.findObjectPosition(x);
	
}


