#include "edge.hpp"

Edge::Edge(int from, int to) {
	this->from = from;
	this->to = to;
	this->w = 0;
}

Edge::Edge(int from, int to, double w) {
	this->from = from;
	this->to = to;
	this->w = w;
}

bool operator<(const Edge &e1, const Edge &e2) {
	return e1.w < e2.w;
}
