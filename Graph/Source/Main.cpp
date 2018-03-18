/************************************************************************
|Author: Julio Rosario
|Purpose:The purpose of this program is to test the Graph class
|Last Update: 12/12/17
************************************************************************/

#include "Graph.h"
#include "Graph.cpp"
#include <iostream>
#include <string>
#include <queue>
#include<stack>
#include <float.h>


void displayMenu(int&);                                          //Display menu to the user
void addVertex(Graph<std::string>&);                             //Add vertex to the graph
void addEdge(Graph<std::string>&);                               //Add edges between two verteces
void eraseEdge(Graph<std::string>&);                             //Erased edge between two vertics
void eraseVertex(Graph<std::string>&);                           //Erase a vertex
void printAdjacent(Graph<std::string>&);                         //Display adjacent vertices of a given place
void BFS(Graph<std::string>&, std::string);                      //Perform Breath for search on the graph from a given vertex
void DFS(Graph<std::string>&, std::string);                      //Perform DFS on the graph from a given vertex
void minimumCost(Graph<std::string>&, std::string);              //Perform shortest path on the graph from src to a destination vertex

void performBFS(Graph<std::string>&);                            //Prompt the user for input and perform BFS
void performDFS(Graph<std::string>&);                            //Prompt the user for input and perform DFS
void performMinimumCost(Graph<std::string>&);                    //Prompt the user for two inputs and perform shortest path

int main() {
	int input;
	bool exit = false;
	Graph<std::string> graph(100);
	do {
		displayMenu(input);
		system("CLS");		//Clear screen

		switch (input) {
		case 1:
			addVertex(graph); 
			break;
		case 2:
			addEdge(graph);  
			break;
		case 3:
			eraseVertex(graph); 
			break;
		case 4:
			eraseEdge(graph);  
			break;
		case 5:
			graph.printAllVertices();  
			break;
		case 6:
			printAdjacent(graph);      
			break;
		case 7:
			graph.printVerticesWithEdges(); 
			break;
		case 8:
			performDFS(graph);             
			break;
		case 9:
			performBFS(graph);             
			break;
		case 10:
			performMinimumCost(graph);
			break;
		case 11:
			exit = true;
			break;
		default:
			std::cout << "There is no option: " << input << "\n";
			break;
		}
		std::cout << "\n\n";
	} while (!exit);

	return 0;
}

void displayMenu(int& input) {
	std::cout << "Select one of the followings\n";
	std::cout << "----------------------------\n";
	std::cout << "1)Add a Vertex\n";
	std::cout << "2)Add an Edge\n";
	std::cout << "3)Erase a Vertex\n";
	std::cout << "4)Erase an Edge\n";
	std::cout << "5)Display all vertices\n";
	std::cout << "6)Display adjacent vertices\n";
	std::cout << "7)Display all vertices with edges\n";
	std::cout << "8)Perform DFS\n";
	std::cout << "9)Perform BFS\n";
	std::cout << "10)Find Shorterst path\n";
	std::cout << "11)Exit Program\n";

	std::cin >> input;
}

void addVertex(Graph<std::string>& graph) {
	std::string vertex;
	std::cout << "Enter vertex: ";
	std::cin >> vertex;
	graph.addVertex(vertex);
}

void addEdge(Graph<std::string>& graph) {
	std::string vertex1, vertex2;
	double cost;
	std::cout << "Enter starting place: ";
	std::cin >> vertex1;

	std::cout << "Enter destination: ";
	std::cin >> vertex2;

	std::cout << "Enter cost: ";
	std::cin >> cost;

	graph.addEdge(vertex1, vertex2,cost);
}
void eraseEdge(Graph<std::string>& graph) {
	std::string vertex1, vertex2;

	std::cout << "Enter starting place: ";
	std::cin >> vertex1;

	std::cout << "Enter destination: ";
	std::cin >> vertex2;

	graph.eraseEdge(vertex1, vertex2);
}


void printAdjacent(Graph<std::string>& graph) {
	std::queue<std::string> queue;
	
	std::string place;
	std::cout << "Enter a place: ";
	std::cin >> place;

	graph.getVertices(queue,place);

	if (queue.empty()) {
		std::cout << "This place has no adjacent vertices\n";
	}
	else {
		//Display the adjacent vertices
		while (!queue.empty()) {
			std::cout << queue.front() << " ";
			queue.pop();
		}
	}
}
void eraseVertex(Graph<std::string>& graph) {
	std::string place;
	std::cout << "Enter a place to delete: ";
	std::cin >> place;
	graph.eraseVertex(place);
}
void performBFS(Graph<std::string>& graph) {
	std::string input;
	std::cout << "Enter place for BFS: ";
	std::cin >> input;
	BFS(graph, input);
}

void performDFS(Graph<std::string>& graph) {
	std::string input;
	std::cout << "Enter place for DFS: ";
	std::cin >> input;
	DFS(graph, input);
}

void performMinimumCost(Graph<std::string>& g) {
	std::string input1, input2;

	std::cout << "Enter Starting place: ";
	std::cin >> input1;

	minimumCost(g, input1);
	
}
void BFS(Graph<std::string>& graph, std::string place) {

	//clear the visits 
	graph.clearVisit();

	std::queue<std::string> queue1;
	std::queue<std::string>queue2;

	std::string v1;
	std::string v2;

	// enqueue the given vertex
	queue2.push(place);
	
	while (!queue2.empty())
	{
		// Dequeue a vertex from queue 
		v1 = queue2.front();
		queue2.pop();

		//Check that vertex has not been visit
		if (!graph.hasBeenVisit(v1)) {

			//Mark the vertex as visited
			graph.visit(v1);

			//Display vertex
			std::cout << v1 << " ";

			//Get vertices adjacent to v1
			graph.getVertices(queue1, v1);

			//As long as queue2 is not empty 
			while (!queue1.empty()) {

				//Get vertex and pop it
				v2 = queue1.front();
				queue1.pop();

				//If it has not been visit push it to queue1
				if (!graph.hasBeenVisit(v2))
					queue2.push(v2);
			}
		}
	}
}

void DFS(Graph<std::string>& graph, std::string place) {

	//Clear all visited vertices
	graph.clearVisit();
	std::stack<std::string> LIFO;
	std::queue<std::string>FILO;

	std::string v1;
	std::string v2;

	//Enqueue the given vertex
	LIFO.push(place);

	while (!LIFO.empty()) {

		//Get vertex
		v1 = LIFO.top();
		LIFO.pop();

		//Check that it hasn't been visit
		if (!graph.hasBeenVisit(v1)) {

			//Visit vertex and print
			graph.visit(v1);
			std::cout << v1 << " ";

			//Get vertices adjacent to v1
			graph.getVertices(FILO, v1);

			while (!FILO.empty()) {

				v2 = FILO.front();
				FILO.pop();

				//If that v2 hasn't been visit go push it into LIFO
				if (!graph.hasBeenVisit(v2)) 
					LIFO.push(v2);
			}
		}
	}
}

void minimumCost(Graph<std::string>&graph, std::string src) {

	/*************************************************************
	|Create a smallest array, that will contain the minimum cost 
	**************************************************************/
	double*smallest = new double[graph.getNumberOfVertices()];
	
	//Clear visited vertices
	graph.clearVisit();

	//Initialize smallest from the src to all the edges
	graph.getAllCostFrom(src, smallest); 
	
	/****************************************************
	|Initialize the cost from the given vertex to 0 
	|because from i to i is 0 and mark that spot to visited
	|because that's the smallest distance from i to i.
	******************************************************/
	int i = graph.findIndex(src);
	smallest[i] = 0;
	graph.visit(src);
	std::string vertex = "";

	for (i = 1; i < graph.getNumberOfVertices()-1; i++) {

		double minWeight = DBL_MAX;
		int index;

		//Find the smallest cost from v that has not been visit
		for (int j = 0; j < graph.getNumberOfVertices(); j++) {
			graph.getVertex(j, vertex);
			if (!graph.hasBeenVisit(vertex)) {
				if (smallest[j] < minWeight) {
					index = j;
					minWeight = smallest[index];
				}
			}
		}
		graph.getVertex(index, vertex);
		graph.visit(vertex);

		for (int k = 0; k < graph.getNumberOfVertices(); k++) {
			graph.getVertex(k, vertex);

			if (!graph.hasBeenVisit(vertex)) {

				if (minWeight + graph.getCost(index, k) < smallest[k]) {
					smallest[k] = minWeight + graph.getCost(index, k);
				}
			}
		}
	}

	//print the shortest path from a given vertex v to any other vertex 
	for (int i = 0; i < graph.getNumberOfVertices(); i++) {
		graph.getVertex(i, vertex);
		std::cout << "From " << src << " to " << vertex;
		std::cout << " is " << smallest[i] << "\n";
	}

	graph.clearVisit();
	delete[] smallest;
}
