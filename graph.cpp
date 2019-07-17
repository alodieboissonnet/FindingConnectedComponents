#include <cstdio>
#include <list>
#include <cstdlib>
#include <fstream>
#include <cassert>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>

#include "graph.hpp"
#include "node.hpp"
#include "edge.hpp"

// creates a new graph with nbNodes nodes and no edge
Graph::Graph(int nbNodes) {
	this->nbNodes = nbNodes;

	this->nodes = new Node[nbNodes];

	for (int i = 0; i < nbNodes; i ++)
		this->nodes[i].setId(i);

	this->adj = new int*[nbNodes];
	for (int i = 0; i < nbNodes; i++)
		this->adj[i] = new int[nbNodes];

	for (int i = 0; i < nbNodes; i++)
		for (int j = 0; j < nbNodes; j++)
			this->adj[i][j] = 0;

	this->seen = new int[nbNodes];
}

// creates a new graph with nbNodes nodes with random coordinates
//comprised between 0 and d_max and no edge
Graph::Graph(int nbNodes, double d_max){
	srand (time(NULL));

	this->nbNodes = nbNodes;

	this->nodes = new Node[nbNodes];

	for (int i = 0; i < nbNodes; i ++) {
		double x = (double) rand()*d_max/RAND_MAX;
		double y = (double) rand()*d_max/RAND_MAX;
		this->nodes[i].setId(i);
		this->nodes[i].setX(x);
		this->nodes[i].setY(y);

	}

	this->adj = new int*[nbNodes];
	for (int i = 0; i < nbNodes; i++)
		this->adj[i] = new int[nbNodes];

	for (int i = 0; i < nbNodes; i++)
		for (int j = 0; j < nbNodes; j++)
			this->adj[i][j] = 0;

	this->seen = new int[nbNodes]();

	for (int i=0; i<nbNodes; i++){
		for (int j=0; j<nbNodes; j++){
			double proba = (double) rand()/RAND_MAX;
			if (i!=j && proba < 0.2) {
				this->addEdge(i,j);
			}
		}
	}
}

// creates a new graph from a text file
Graph::Graph(const char* file) {
		std::ifstream is1(file);

		if (is1.fail()) {
			std::cout<<"Cannot read from file "<<file<<" !"<<std::endl;
			exit(1);
		}

		this->nbNodes = 0;
		std::string line1;
		while (getline(is1, line1))
			this->nbNodes ++;

		is1.close();

		this->nodes = new Node[nbNodes];

		std::ifstream is2(file);

		int id = 0;
		double x, y;
		while (is2 >> x >> y){
			this->nodes[id].setId(id);
			this->nodes[id].setX(x);
			this->nodes[id].setY(y);
			id++;
		}

		is2.close();

		this->adj = new int*[nbNodes];
		for (int i = 0; i < nbNodes; i++)
			this->adj[i] = new int[nbNodes];

		for (int i = 0; i < nbNodes; i++)
			for (int j = 0; j < nbNodes; j++)
				this->adj[i][j] = 0;

		this->seen = new int[nbNodes];

		// we create random edges with a probability of 0.2
		srand (time(NULL));
		for (int i=0; i<nbNodes; i++){
			for (int j=0; j<nbNodes; j++){
				double proba = (double) rand()/RAND_MAX;
				if (i!=j && proba < 0.2 && dist(i, j) != 0) {
					this->addEdge(i,j);
				}
			}
		}
}


int Graph::getNbNodes () {
	return this->nbNodes;
}


void Graph::addEdge(int from, int to) {
	Edge *e = (Edge *) malloc (sizeof(Edge)); // Otherwise, object doesn't exist at the end of the function and can be erased
	e = new Edge(from, to, this->dist(from, to));

	this->edges.push_back(e);

	this->nodes[from].addNeighbor(to);
	this->nodes[to].addNeighborIn(from);

	this->adj[from][to] = 1;
}

std::ostream &operator<<(std::ostream &out, Graph &g) {
	out << "Displaying graph : " << std::endl << std::endl;

	out << "There are " << g.getNbNodes() << " nodes." << std::endl;
	for (int i = 0; i < g.getNbNodes(); i++)
		out << g.nodes[i];

	out << std::endl;

	return out;
}

// returns all strongly connected components of a graph
void Graph::stronglyConnectedComponents () {
	std::cout << "Displaying strongly connected components : " << std::endl;

	clock_t start = clock();

	for (int i = 0; i < this->nbNodes; i++)
		this->seen[i] = 0;

	this->listOfNodes.clear();

	for (int i = 0; i < this->nbNodes; i++)
		this->dfs(i);

    	for (int i = 0; i < this->nbNodes; i++)
		this->seen[i] = 0;

	int nbComponent = 1;

	for (std::list<int>::reverse_iterator i = listOfNodes.rbegin(); i != listOfNodes.rend(); i++) {
    	if (seen[*i] == 0) {
    		std::cout << "Component " << nbComponent << " : ";
    		reverse_dfs(*i);
    		std::cout << std::endl;

    		nbComponent++;
    	}
    }

	clock_t end = clock();
	double delta_t = (double) ((end-start)*1000/CLOCKS_PER_SEC);

	std::cout << "stronglyConnectedComponents tourne en " << delta_t << " ms."<< std::endl;

}


// runs depth-fisrt search
void Graph::dfs (int curNode) {
	if (seen[curNode] == 1)
		return;

	seen[curNode] = 1;

	for (std::list<int>::iterator i = this->nodes[curNode].neighbors.begin(); i != this->nodes[curNode].neighbors.end(); i++) {
    	dfs(*i);
    }

	listOfNodes.push_back(curNode);
}

// returns the reverse of depth-fisrt search
void Graph::reverse_dfs (int curNode) {
	if (seen[curNode] == 1)
		return;

	seen[curNode] = 1;

	std::cout << curNode << ", ";

	for (std::list<int>::iterator i = this->nodes[curNode].neighborsIn.begin(); i != this->nodes[curNode].neighborsIn.end(); i++) {
    	reverse_dfs(*i);
    }

}

// creates random ER digraph
void Graph::ErDigraphs(double p){
	srand (time(NULL));

	int n = this->nbNodes;

	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			double proba = (double) rand()/RAND_MAX;
			if (i!=j && proba < p) {
				this->addEdge(i,j);
			}
		}
	}
	return;
}

// runs DBSCAN
void Graph::DBSCAN(double eps, int M) {

	clock_t start = clock();

	for (int i = 0; i < this->nbNodes; i++)
		this->seen[i] = 0;

	int C = 1;
	this->nodeByC.clear();


	for (int i = 0; i < this->nbNodes; i++)
		nodeByC.push_back(std::vector<int>());


	for (int i = 0; i < this->nbNodes; i++){
		if (this->seen[i] == 0) {

			this->seen[i] = C;
			nodeByC[C].push_back(i);

			this->listOfNodes.clear();

			neighborsEps(i,eps, this->listOfNodes);

			if (this->listOfNodes.size() >= M){
				setCluster(i,listOfNodes,C,eps, M);
				C++;
			}
			else {
				this->seen[i] = NOISE;
				this->nodeByC[NOISE].push_back(i);
				this->nodeByC[C].pop_back();
			}

		}
	}

	clock_t end = clock();
	double delta_t = (double) ((end-start)*1000/CLOCKS_PER_SEC);

	for (int i = 1; i < this->nbNodes; i++) {
		if (nodeByC[i].empty())
			break;

		std::cout << "Cluster " << i << " contains node : ";

		for (int j = 0; j < this->nodeByC[i].size(); j++)
			std::cout << this->nodeByC[i][j] << ", ";
		std::cout << std::endl;
	}

	std::cout << "Noise : ";
	for (int j = 0; j < this->nodeByC[0].size(); j++)
		std::cout << this->nodeByC[0][j] << ", ";
	std::cout << std::endl;


	std::cout << "DBSCAN tourne en " << delta_t << " ms."<< std::endl;

}

// computes the number of nodes in an epsilon-neighborhood
void Graph::neighborsEps(int i, double eps, std::list<int>& l){
	for (int j = 0; j < this->nbNodes; j++){
		if (j != i && this->dist(i,j) <= eps)
			l.push_back(j);
	}
}

// computes the Euclidian distance between two nodes
double Graph::dist (int i, int j) {
	return std::sqrt(std::pow(this->nodes[i].getX() - this->nodes[j].getX(), 2) + std::pow(this->nodes[i].getY() - this->nodes[j].getY(),2));
}

// expands clusters according to DBSCAN algoritm
void Graph::setCluster(int curNode, std::list<int> mainNeighbors, int C, double eps, int M) {
	for (std::list<int>::iterator i = mainNeighbors.begin(); i != mainNeighbors.end(); i++) {
		if (this->seen[*i] == 0) {
			this->seen[*i] = C;
			this->nodeByC[C].push_back(*i);

			std::list<int> neighborhood;
			this->neighborsEps(*i, eps, neighborhood);

			if (neighborhood.size() >= M)
				mainNeighbors.insert(mainNeighbors.end(), neighborhood.begin(), neighborhood.end());

		}
	}
}

// finds the optimal epsilon for DBSCAN algoritm
double Graph::find_epsilon() {
	std::list<double> min_neighbor;

	for (int i = 0; i < this->nbNodes; i++) {
		double m = 1000000000;

		for (std::list<int>::iterator j = this->nodes[i].neighbors.begin(); j != this->nodes[i].neighbors.end(); j++)
			m = std::min(m, dist(i, *j));

		min_neighbor.push_back(m);
	}

	min_neighbor.sort();
	std::list<double>::iterator it = min_neighbor.begin();
	std::advance(it, (int)(min_neighbor.size()*0.9));

	return *it;

}

// finds the optimal M for DBSCAN algoritm
int Graph::find_M (double epsilon) {

	std::list<int> sizeOfNeighborEps;

	for (int i = 0; i < nbNodes; i++) {
		std::list<int> l;
		this->neighborsEps(i, epsilon, l);
		sizeOfNeighborEps.push_back(l.size());
	}

	sizeOfNeighborEps.sort();

	std::list<int>::iterator it = sizeOfNeighborEps.begin();
	std::advance(it, (int)(sizeOfNeighborEps.size()*0.9));

	return *it;

}
