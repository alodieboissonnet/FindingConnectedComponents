#include <cstdlib>
#include <cstdio>

#include "graph.hpp"

int main () {


	// Identifies strongly connected components of a random ER digraph
	// with 0.14 < p < 0.38, we get multiple strongly connected components, but not only isolated nodes
	Graph *g = new Graph(6);
	g->ErDigraphs(0.14);

	std::cout << *g;
	g->stronglyConnectedComponents();

	return 0;


	// Question 3
	// runs the strongly connected components algorithm and the DBSCAN algorithm on the dataset of the file "villes.txt"
	Graph *g = new Graph("villes.txt");

	// finds the optimal value for espilon
	double eps = g->find_epsilon();
	std::cout << "epsilon " << eps << std::endl;

	// finds the optimal value for M
	int M = g->find_M(eps);
	std::cout << "M " << M << std::endl;

	g->stronglyConnectedComponents();
	g->DBSCAN(eps,M);
}
