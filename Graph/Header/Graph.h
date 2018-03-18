/******************************************************************************
|Author: Julio Rosario
|Purpose: The purpose of this file is to create a header class file of a graph.
|Last Update: 12/12/2017
********************************************************************************/
#ifndef GRAPH_H_
#define GRAPH_H_
#include<queue>

template<class T>
class Graph {

private:
	int numberOfVertices;
	int maxNumberOfVertices;
	T* vertices;                         //The vertices of the graph
	double* edges;                        //The edges between vertices
	bool* visited;                       //The verteces that has been visit

public:
	Graph(int);                          //Constructor
	~Graph();                            //Destructor
	Graph(const Graph&);                 //Copy Constructor
	void operator=(const Graph&);        //Assignment operator
	void copy(const Graph&);             //Copy a graph
	bool isEmpty();                      //Determine if graph is empty
	bool isFull();                       //Determine if graph is full
	void erasedGraph();                  //Erase graph

	void addVertex(T);                    //Append a vertex to the graph
	void addEdge(T, T,double);           //Add an edge between two verteces and the weight 
	void eraseEdge(T, T);                //Erase an edge between two verteces
	void eraseVertex(T);                 // Erase Vertex 

	void getVertices(std::queue<T>&, T); //Return a queue with all the vertices
	bool hasBeenVisit(T);                //Determine if a vertex has been visit
	void visit(T);                       //Visit a vertex

	void printAllVertices();              //Print all the vertices
	void printVerticesWithEdges();       //Print the vertices that has edges
	int findIndex(T);                    //Find the index of a given vertex

	void clearVisit();                   // Clear the visited verteces

	double getCost(int, int);            //Return the cost from  a give vertex to another
	int getNumberOfVertices();           //Return the number of vertices 
	void getVertex(int,T&);              //Return the vertex of a given index

	void getAllCostFrom(T,double*&);
};
#endif /*GRAPH_H_ */