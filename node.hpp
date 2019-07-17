#pragma once

#include <list>

class Node
{
    public:
    	Node();
		Node (int id);
		Node (int id, double x, double y);
		void setId (int id);
    void setX (double x);
    void setY (double y);
		int getId();
		void addNeighbor(int idNeighbor);
		void addNeighborIn(int idNeighbor);
		std::list<int> neighbors;
		std::list<int> neighborsIn;

		double getX();
		double getY();

	private:
		int id;
		int nbNeighbors;
		double x, y;

};

std::ostream &operator<<(std::ostream &out, Node &n);
