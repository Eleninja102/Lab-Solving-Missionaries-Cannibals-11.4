#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <stack>
using namespace std;


template <typename Type>
class Graph;


template <typename Type>
ostream& operator << (ostream & out, const Graph<Type> &g);

template <typename Type>
class Graph {
private:
    vector <Type> verticies;
    vector <vector<Type>> edges;

public:
	Graph();
	void addVertex(Type vertex);
	void addEdge(Type, Type);
	int getVertexPos(Type item);
	long getNumVertices()const;
	bool isEdge(Type, Type);
	friend ostream& operator << <>(ostream & out, const Graph<Type> &g);
	vector<Type>getPath(Type, Type);
    void GetPath(Type, Type,  vector<Type> solution, vector <vector<Type>> &solutionExtra);

};



/*********************************************
* Constructs an empty graph
*
*********************************************/
template<typename Type>
Graph<Type>::Graph() {

}




/*********************************************
* Adds a Vertex to the Graphs. Note that the vertex may not be an int value
*********************************************/
template <typename Type>
void Graph<Type>::addVertex(Type vertex) {
    verticies.push_back(vertex);
    vector<Type>lst;
    edges.push_back(lst);

}

/*********************************************
* Returns the current number of vertices
*
*********************************************/
template<typename Type>
long Graph<Type>::getNumVertices()const {
	return verticies.size();
}



/*********************************************
* Returns the position in the verticies list where the given vertex is located, -1 if not found.
*
*********************************************/
template <typename Type>
int Graph<Type>::getVertexPos(Type item) {
    for( int i = 0; i < verticies.size(); i++){
        if(item == verticies[i]){
            return i;
        }
    }
	return -1; //return negative one
}//End findVertexPos

/*********************************************
* Adds an edge going in the direction of source going to target
*
*********************************************/
template <typename Type>
void Graph<Type>::addEdge(Type source, Type target) {
    int srcPos = getVertexPos(source);
    if(srcPos < 0){
        throw runtime_error("Vertex not found");
    }
    edges[srcPos].push_back(target);
}

template <typename Type>
bool Graph<Type>::isEdge(Type source, Type dest) {
    int srcPos = getVertexPos(source);
    if(srcPos < 0){
        throw runtime_error("Vertex not found");
    }
    for(int i = 0; i < edges[i].size(); i++){
        if(edges[srcPos][i] == dest){
            //std::cout << "test point";
            return true;
        }
    }
	return false;
}



/*********************************************
* Returns a display of the graph in the format
* vertex: edge edge
* Note: This is not a traversal, just output
*********************************************/
template <typename Type>
ostream& operator << (ostream & out, const Graph<Type> &g) {
    for(int i = 0; i < g.verticies.size(); i++){
        out << g.verticies[i] << ": ";
        for(int j = 0; j < g.edges[i].size(); j++){
            out << g.edges[i][j] << " ";
        }
        out << endl;
    }

	return out;
}

/*
  getPath will return the shortest path from source to dest.
  You are welcome to use any solution not limited to the following, depth first search to traverse
  graph to find the solution, breadth first, shortest path first, or any
  other graph algorithm.

  You will return a vector with the solution from the source to the destination.
  IE: The source will be in position 1 the destination is in the last position of the solution, and each node in between
  are the verticies it will travel to get to the destination.  There will not be any
  other verticies in the list.
*/
template <typename Type>
vector<Type> Graph<Type>::getPath(Type source, Type dest) {
    vector<Type> solution;
    vector <vector<Type>> solutionExtra;

    int start = getVertexPos(source);
    if(isEdge(source, dest)){
        solution.push_back(source);
        solution.push_back(dest);
    }
    for(int i = 0; i < edges[start].size(); i++){
      
        GetPath(source, dest, solution, solutionExtra);
  
    }
    
    for(int i = 0; i < solutionExtra.size(); i++){
        if(solution.size() == 0){
            solution = solutionExtra[i];
        }else if(solution.size() > solutionExtra[i].size()){
            solution = solutionExtra[i];

        }
    }
    
	return solution;
}



template <typename Type>
void Graph<Type>::GetPath(Type x, Type dest, vector<Type> solution, vector <vector<Type>> &solutionExtra){
    int start = getVertexPos(x);
    solution.push_back(x);

    for(int i = 0; i < edges[start].size(); i++){
        
        if(edges[start][i] == dest){
            solution.push_back(edges[start][i]);
            solutionExtra.push_back(solution);
            return;
        }
        if(find(begin(solution), end(solution), edges[start][i]) == end(solution)){
            //cout << edges[start][i];
           GetPath(edges[start][i], dest, solution, solutionExtra);
        }
    }
}
