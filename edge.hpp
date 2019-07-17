#pragma once

class Edge
{
    public:
    	int from, to;
    	int w; // weight
    	
    	Edge (int from, int to);
		Edge(int from, int to, double w);
    

    private:


};

bool operator<(const Edge &e1, const Edge &e2);

