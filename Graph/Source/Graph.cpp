/***************************************************************************
|Author: Julio Rosario
|Purpose: The purpose of this class is to implement the class Graph.h
|Last Update: 12/12/17
****************************************************************************/

#include "Graph.h"
#include <iostream>
#include <stdlib.h> 
#include <float.h>
#include <cmath>  

template<class T>
Graph<T>::Graph(int max) {
	numberOfVertices = -1;
	maxNumberOfVertices = max;
	vertices = new T[max];
	edges = new double[max*max];
	visited = new bool[max];

	//initialize visited to false
	for (int i = 0; i < max; i++)
		visited[i] = false;
	
	//Initialize edges to 0
	for (int i = 0; i < max; i++) {
		for (int j = 0; j < max; j++) {
			int index = i*maxNumberOfVertices + j;
			edges[index] = std::abs(DBL_MAX);
		}
	}
}

template<class T>
Graph<T>::~Graph() {
	erasedGraph();
}

template<class T>
Graph<T>::Graph(const Graph& graph) {
	copy(graph);
}

template<class T>
void Graph<T>::operator=(const Graph& graph) {
	copy(graph);
}


template<class T>
bool Graph<T>::isEmpty() {
	return numberOfVertices == -1;
}

template<class T>
bool Graph<T>::isFull() {
	return numberOfVertices - 1 == maxNumberOfVertices;
}

template<class T>
void Graph<T>::erasedGraph() {

	if (vertices != 0)
		delete[] vertices;
	if (edges != 0)
		delete[] edges;
	if (visited != 0)
		delete[] visited;

	vertices = 0;
	edges = 0;
	visited = 0;
	numberOfVertices = 0;
	maxNumberOfVertices = 0;
}

template<class T>
void Graph<T>::copy(const Graph& graph) {

	erasedGraph();
	numberOfVertices = graph.numberOfVertices;
	maxNumberOfVertices = graph.maxNumberOfVertices;

	vertices = new T[maxNumberOfVertices];
	edges = new T[maxNumberOfVertices*maxNumberOfVertices];

	//Copy vertices
	for (int i = 0; i <= numberOfVertices; i++) {
		vertices[i] = graph.vertices[i];
	}

	//Copy edges
	for (int i = 0; i < maxNumberOfVertices; i++) {
		for (int j = 0; j < maxNumberOfVertices; j++) {
			int index = i*maxNumberOfVertices + j;
			edges[index] = graph.edges[index];
		}
	}

	//copy visited
	for (int i = 0; i < maxNumberOfVertices; i++) {
		visited[i] = graph.visited[i]; 
	}
}

template<class T>
void Graph<T>::addVertex(T place) {

	if (!isFull()) {

		if (vertices != 0) {
			numberOfVertices++;
			vertices[numberOfVertices] = place;
		}
		else {
			std::cout << "Vertices is NULL";
		}
	}
	else
		std::cout << "CANNOT ADD MORE VERTICES";

}

template<class T>
void Graph<T>::addEdge(T place1, T place2,double weight) {

	if (isEmpty()) {
		std::cout << "Graph is empty\n";
		return;
	}

	int i, j;

	//Get the indeces 
	i = findIndex(place1);
	j = findIndex(place2);

	//Check that place 1 and place 2 exists 
	if (i != -1 && j != -1) {
		int index = i*maxNumberOfVertices + j;
		edges[index] = weight;

		index = j*maxNumberOfVertices + i;
		edges[index] = weight;
	}
	else {
		if (i < 0)
			std::cout << place1 << " Does not exist\n";
		if (j < 0)
			std::cout << place2 << " Does not exist\n";
	}
}

template<class T>
void Graph<T>::getVertices(std::queue<T>& q, T place) {

	if (isEmpty()) {
		std::cout << "Graph is empty\n";
		return;
	}

	int i = findIndex(place); //Find index of place

	//Check that the place exist
	if (i != -1) {
		//Get the vertices that ajacent to the place
		for (int j = 0; j <= numberOfVertices; j++) {

			int index = i*maxNumberOfVertices + j;
			if (edges[index] < std::abs(DBL_MAX))
				q.push(vertices[j]);
		}
	}
	else{
		std::cout << place << " this place does not exist\n";
	}
}

template<class T>
bool Graph<T>::hasBeenVisit(T place) {
	int i = findIndex(place);

	if (i != -1) {
		return visited[i];
	}
	else {
		std::cout << place << " does not exist\n";
		return false;
	}

}

template<class T>
void Graph<T>::visit(T place) {

	if (isEmpty()) {
		std::cout << "Graph is empty\n";
		return;
	}

	int i = findIndex(place);

	if (i != -1)
		visited[i] = true;
	else
		std::cout << place << " does not exist\n";
}

template<class T>
void Graph<T>::eraseEdge(T place1, T place2) {
	
	if (isEmpty()) {
		std::cout << "Graph is empty\n";
		return;
	}

	int i, j;
	 i = findIndex(place1);
	 j = findIndex(place2);

	 if (i >= 0 && j >= 0) {
		 int index = i*maxNumberOfVertices +j;
		 edges[index] = std::abs(DBL_MAX);
	 }
	 else {
		
		  if (i < 0)
			 std::cout << place1 << " DO NOT EXIST\n";
		  if(j < 0)
			 std::cout << place2 << " DO NOT EXIST\n";
	 }
}

template<class T>
void Graph<T>::eraseVertex(T place) {

	if (isEmpty()) 
		std::cout << "Graph is empty, cannot erase vertex\n";
	else {
		int index = findIndex(place); 

		//Erase vertex
		if (index != -1) {
			visited[index] = false;

			if (index == numberOfVertices)
				numberOfVertices--;
			else {

				//Erase vertex from vertices array
				for (int i = index; i < numberOfVertices + 1; i++) {
					vertices[i] = vertices[i + 1];
				}

				//Erase  edges from that vertex
				int y = 0;
				int z = 0;
				for (int i = 0; i <= numberOfVertices; i++) {
					y = i*maxNumberOfVertices + index;
					edges[y] = std::abs(DBL_MAX);
				}

				//Shift the matrix up
				for (int i = index; i < numberOfVertices + 1; i++) {
					for (int j = 0; j <= numberOfVertices; j++) {
						 y = i*maxNumberOfVertices + j;
						 z = (i + 1)*maxNumberOfVertices + j;
						edges[y] = edges[z];
					}
				}

				numberOfVertices--;
			}
		}
		else {
			std::cout << place << " is not found\n";
		}
	}
}

template<class T>
void Graph<T>::printAllVertices() {

	if (isEmpty()) {
		std::cout << "Graph is empty\n";
		return;
	}
	for (int i = 0; i <= numberOfVertices; i++) {
		std::cout << vertices[i] << " ";
	}
	std::cout << "\n";
}
template<class T>
void Graph<T>:: printVerticesWithEdges() {

	if (isEmpty()) {
		std::cout << "Graph is empty\n";
		return;
	}
	for (int i = 0; i <= numberOfVertices; i++) {
		
		//Display the place 
		std::cout << vertices[i] << "->";
		for (int j = 0; j <= numberOfVertices; j++) {
			int index = i*maxNumberOfVertices + j;
			 
			//Display place's edges
			if (edges[index] < std::abs(DBL_MAX)) {
				std::cout << vertices[j] << " ";
			}
		}
		std::cout << "\n";
	}
}

template<class T>
int Graph<T>::findIndex(T item){

	int index = -1;
	for (int i = 0; i <= numberOfVertices; i++) {
		if (vertices[i] == item) {
			index = i;
			break;
		}
	}
	return index;
}

template<class T>
void Graph<T>::clearVisit() {

	for (int i = 0; i <=numberOfVertices; i++) {
		visited[i] = false;
	}
}

template<class T>
double Graph<T>::getCost(int i, int j) {
	int index = i*maxNumberOfVertices + j;
	return edges[index];
}

template<class T>
int Graph<T>::getNumberOfVertices() {
	return numberOfVertices+1;
}

template<class T>
void  Graph<T>::getAllCostFrom(T src, double*& smallest) {
	int i = findIndex(src);

	if (i != -1) {
		for (int j = 0; j <= numberOfVertices; j++) {
			int index = i*maxNumberOfVertices + j;
			smallest[j] = edges[index];
		}
	}
	else {
		std::cout << src << "IS NOT FOUND!\n";
	}
}

template<class T>
void Graph<T>::getVertex(int i, T& item) {
	if (i >= 0 && i <= numberOfVertices)
		item = vertices[i];
}