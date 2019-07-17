# FindingConnectedComponents
Finds connected components in a graph using a Kosaraju's and DBSCAN algorithms in C++

# Getting started
A digraph G = (V,E) is strongly connected if it contains a path from u to v for all nodes u,v ∈ V. A sub-digraph of G is a strongly connected component of G if it is strongly connected and maximal with this property. Any digraph has a unique decomposition into strongly connected components, which partitions the set of nodes.

# Pseudo-code of Kosaraju's alogirthm
    For each vertex u of the graph, mark u as unvisited. Let L be empty.
    For each vertex u of the graph do Visit(u), where Visit(u) is the recursive subroutine:
      If u is unvisited then:
        Mark u as visited.
        For each out-neighbour v of u, do Visit(v).
        Prepend u to L.
      Otherwise do nothing.
    For each element u of L in order, do Assign(u,u) where Assign(u,root) is the recursive subroutine:
      If u has not been assigned to a component then:
        Assign u as belonging to the component whose root is root. 
        For each in-neighbour v of u, do Assign(v,root). 
      Otherwise do nothing.


# Erdős-Rényi digraphs
Erdős-Rényi digraphs are random digraphs, in which nodes are connected with a probability of p.

# DBSCAN algorithm
DBSCAN requires two parameters: ε and the minimum number of points required to form a dense region (M). It starts with an arbitrary starting point that has not been visited. This point's ε-neighborhood is retrieved, and if it contains sufficiently many points, a cluster is started. Otherwise, the point is labeled as noise. 

If a point is found to be a dense part of a cluster, its ε-neighborhood is also part of that cluster. Hence, all points that are found within the ε-neighborhood are added, as is their own ε-neighborhood when they are also dense. This process continues until the density-connected cluster is completely found. Then, a new unvisited point is retrieved and processed, leading to the discovery of a further cluster or noise.


The DBSCAN algorithm can be described into the following steps:

- Find the points in the ε (eps) neighborhood of every point, and identify the core points with more than minPts neighbors.
- Find the connected components of core points on the neighbor graph, ignoring all non-core points.
- Assign each non-core point to a nearby cluster if the cluster is an ε (eps) neighbor, otherwise assign it to noise.

## Choice of DBCAN's parameters
Choice of ε : we should choose ε in order that a "big enough" part of points have a distance to their closest neighbor smaller than ε
Choice of M : we should choose M in order that a "big enough" part of points have more than M points in their ε-neighborhood
Here, a "big enough" part means about 90% to 95% of points.
