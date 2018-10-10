#include<vector>
#include<iostream>
#include<string>
using namespace std;
#include "GraphGeneric.h"
#include "TestClass.h"

int main() {

	/*	string x = "x";
		string y = "y";
		string z = "z";
		string w = "w";
		string v = "v";

		GraphGeneric<string> graph = GraphGeneric<string>(x);
		//graph.addEdge(x, y);
		cout << graph;

		graph.addEdge(x, v);
		graph.addEdge(y, x);
		graph.addEdge(x, v);
		graph.addEdge(w, z);
		graph.addEdge(x, v);
		graph.addEdge(z, v);
		graph.addEdge(v, v);


		cout << graph << endl;

		vector<string> connections = graph.getConnections("u");*/

	TestClass x = TestClass("x");
	TestClass y = TestClass("y");
	TestClass z = TestClass("z");
	TestClass w = TestClass("w");
	TestClass v = TestClass("v");

	GraphGeneric<TestClass> graph = GraphGeneric<TestClass>(x);

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