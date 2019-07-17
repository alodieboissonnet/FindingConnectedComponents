#include <cstdlib>
#include <iostream>
#include <list>

#include "node.hpp"

Node::Node () {
	this->id = -1;
	this->nbNeighbors = 0;
	this->x = 0;
	this->y = 0;
}

Node::Node (int id) {
	this->id = id;
	this->nbNeighbors = 0;
	this->x = 0;
	this->y = 0;
}

Node::Node (int id, double x, double y) {
	this->id = id;
	this->nbNeighbors = 0;
	this->x = x;
	this->y = y;
}

void Node::setId(int id) {
	this->id = id;
}

void Node::setX(double x) {
	this->x = x;
}

void Node::setY(double y) {
	this->y = y;
}

int Node::getId () {
	return this->id;
}

void Node::addNeighbor(int idNeighbor) {
	this->neighbors.push_back(idNeighbor);
}

void Node::addNeighborIn(int idNeighbor) {
	this->neighborsIn.push_back(idNeighbor);
}

double Node::getX() {
	return this->x;
}

double Node::getY() {
	return this->y;
}

std::ostream &operator<<(std::ostream &out, Node &n) {
    out << "Node's id : " << n.getId() << std::endl;
    out << "Node's Neighbors : ";
    for (std::list<int>::iterator i = n.neighbors.begin(); i != n.neighbors.end(); i++) {
    	out << *i << ", ";
    }

    out << std::endl;

    return out;
}
