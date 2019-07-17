#pragma once

#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "node.hpp"
#include "edge.hpp"

class Graph
{
    public:
    	Graph(int nbNodes);
    	Graph(int nbNodes, double d_max);
      Graph(const char* file);
    	void addEdge(int from, int dest);
    	int getNbNodes();
    	Node *nodes;
    	void stronglyConnectedComponents();
		  void ErDigraphs(double p);

		void DBSCAN(double eps, int M);
		void setCluster(int curNode, std::list<int> list, int C, double eps, int M);

		void neighborsEps(int i, double eps, std::list<int>& l);
		double dist (int i, int j);

		double find_epsilon();
		int find_M(double epsilon);
    private:
        int nbNodes;
        int **adj;


		std::list<Edge*> edges;

		std::list<int> listOfNodes;
		int *seen;
		void dfs(int curNode);
		void reverse_dfs (int curNode);

		int nbCluster;
		std::vector<std::vector<int> > nodeByC;




};

const int NOISE = 0;

std::ostream &operator<<(std::ostream &out, Graph &n);
