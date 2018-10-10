#include<vector>
#include<iostream>
#include<string>
using namespace std;
#include "GraphGeneric.h"
#include "SubRegion.h"
#include "Region.h"
#include "TestClass.h"

int main() {

	GraphGeneric<SubRegion> manhattanSubRegions;
	GraphGeneric<Region> newYork;
	SubRegion lowerManhattan = SubRegion("Lower Manhattan",&manhattanSubRegions);
	SubRegion midtownManhattan = SubRegion("Midtown Manhattan", &manhattanSubRegions);
	SubRegion upperManhattan = SubRegion("Upper Manhattan", &manhattanSubRegions);

	manhattanSubRegions.addEdge(lowerManhattan,midtownManhattan);
	manhattanSubRegions.addEdge(midtownManhattan,upperManhattan);

	Region manhattan = Region("Manhattan", manhattanSubRegions);
	Region bronx = Region("Bronx");
	Region brooklyn = Region("Brooklyn");
	Region queens = Region("Queens");

	newYork.addEdge(manhattan, bronx);
	newYork.addEdge(manhattan, brooklyn);
	newYork.addEdge(manhattan, queens);
	newYork.addEdge(bronx, manhattan);
	newYork.addEdge(bronx, brooklyn);
	newYork.addEdge(bronx, queens);
	newYork.addEdge(brooklyn, bronx);
	newYork.addEdge(brooklyn, manhattan);
	newYork.addEdge(brooklyn, queens);
	newYork.addEdge(queens, bronx);
	newYork.addEdge(queens, brooklyn);
	newYork.addEdge(queens, manhattan);

	cout << newYork;

	/*TestClass x = TestClass("x");
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

	//graph.findObjectPosition(x);*/


}