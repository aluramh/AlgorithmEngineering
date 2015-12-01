#include <iostream>
#include <fstream>
#include "ListaLineal.h"
#include <list>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>  

#define Q_NODES 900
# define M_PI 3.14159265358979323846  /* pi */

using namespace std;

//Array of edges in dynamic memory. 
//e.g. edges[33] contains a list with all the edges of node with ID 33
list<Node> *edges = new list<Node>[Q_NODES];
unsigned int *degrees = new unsigned int[Q_NODES];

//Declare list of nodes
list<Node> myList;

double random() {
	return (double)rand() / (double)RAND_MAX;
}
double distanceBetweenNodes(Node &a, Node &b) {
	return sqrt(pow((a.getX() - b.getX()), 2) + pow((a.getY() - b.getY()), 2) + pow((a.getZ() - b.getZ()), 2));
}
void addEdge(Node &a, Node &b) {
	edges[(int)a.getInfo()].push_back(b);
}
void displayList(list<Node> myList) {
	for (list<Node>::iterator it = myList.begin(); it != myList.end(); it++) {
		cout << (*it).getInfo() << ", ";
	}
}
void showDegrees() {
	for (int i = 0; i < Q_NODES; i++) {
		cout << i << ": " << degrees[i] << endl;
	}
}
double averageDegree() {
	double accum = 0;
	for (int i = 0; i < Q_NODES; i++) {
		accum += degrees[i];
	}
	return accum / Q_NODES;
}
void displayAdjacenecyList() {
	int i = 0;
	for (list<Node>::iterator it = myList.begin(); it != myList.end(); it++) {
		cout << (*it).getInfo() << "-> ";
		displayList(edges[i]);
		i++;
		cout << endl;
	}
}
Node findInList(list<Node> myList, Node a) {
	Node result = NULL;
	for (list<Node>::iterator it = myList.begin(); it != myList.end(); it++) {
		if ((*it).getInfo() == a.getInfo()) {
			result = (*it);
			break;
		}
	}
	return result;
}
void writeFile(char type) {
	ofstream myfile;
	myfile.open("C:/Users/Alex/Desktop/nodes.txt");
	myfile << type << " 0 0 0"<<endl;
	int i = 0;
	for (list<Node>::iterator it = myList.begin(); it != myList.end(); it++) {
		myfile << "n " << (*it).getX() << " " << (*it).getY() << " " << (*it).getZ() << endl;
		list<Node> edgeList = edges[i];

		for (list<Node>::iterator it2 = edgeList.begin(); it2 != edgeList.end(); it2++) {
			myfile << "e " << (*it2).getX() << " " << (*it2).getY() << " " << (*it2).getZ() << endl;
		}
		i++;
	}
	myfile.close();
}
void connectNodes3D(double r) {
	double rs = r*r;
	int i = 0;
	//O(n^2)
	for (list<Node>::iterator A = myList.begin(); A != myList.end(); A++) {
		degrees[i] = 0;
		for (list<Node>::iterator B = myList.begin(); B != myList.end(); B++) {
			double distance = pow(((*A).getX() - (*B).getX()), 2) + pow(((*A).getY() - (*B).getY()), 2) + pow(((*A).getZ() - (*B).getZ()), 2);
			if ((distance <= rs) && ((*A).getInfo() != (*B).getInfo())) {
				addEdge(*A, *B);
				degrees[i]++;
			}
		}
		i++;
	}
}

void connectNodes2D(double r) {
	double rs = r*r;
	int i = 0;
	//O(n^2)
	for (list<Node>::iterator A = myList.begin(); A != myList.end(); A++) {
		degrees[i] = 0;
		for (list<Node>::iterator B = myList.begin(); B != myList.end(); B++) {
			double distance = pow(((*A).getX() - (*B).getX()), 2) + pow(((*A).getY() - (*B).getY()), 2);
			if ((distance <= rs) && ((*A).getInfo() != (*B).getInfo())) {
				addEdge(*A, *B);
				degrees[i]++;
			}
		}
		i++;
	}
}

void displayNodes(list<Node> myList) {
	for (list<Node>::iterator it = myList.begin(); it != myList.end(); it++) {
		cout << (*it).getInfo() << ": (" << (*it).getX() << ", " << (*it).getY() << ", " << (*it).getZ() << ")" << endl;
	}
}
void createRGG() {
	srand(time(NULL));
	for (int i = 0; i<Q_NODES; i++) {
		myList.push_back(Node(i, random(), random(), 0));
	}
}
void createCircleRGG() {
	srand(time(NULL));
	for (int i = 0; i < Q_NODES; i++) {
		double x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2));
		double y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2));
		if ( ( pow((x-1),2) + pow((y-1),2) ) > 1) {
			i--;
		}
		else {
			myList.push_back(Node(i, x, y, 0));
		}
	}
}
int main(int argc, const char * argv[])
{	
	char type;
	double radius = 0.08;
	cin >> type;
	switch (type) {
		case 'u':
			createRGG();
			connectNodes2D(radius);
			break;

		case 'c':
			createCircleRGG();
			connectNodes2D(radius);
			break;

		case 's':
			//Sphere case
			break;

		default:
			break;
	}
	//displayNodes(myList);
	cout << endl;
	//displayAdjacenecyList();
	//showDegrees();

	writeFile(type);

	cout << "Success! Avg. Degree: " << averageDegree() << endl;
	//Release memory
	delete[] edges;
	delete[] degrees;
	return 0;
}