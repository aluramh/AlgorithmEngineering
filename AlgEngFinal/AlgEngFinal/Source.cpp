#include <iostream>
#include <fstream>
#include "ListaLineal.h"
#include <list>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>  

#define Q_NODES 50
#define M_PI 3.14159265358979323846  /* pi */
#define Q_COLORS 200

using namespace std;

//Array of edges in dynamic memory. 
//e.g. edges[33] contains a list with all the edges of node with ID 33
list<Node> *edges = new list<Node>[Q_NODES];
list<Node> *originalEdges = new list<Node>[Q_NODES];

unsigned int *index = new unsigned int[Q_NODES];
unsigned int *degrees = new unsigned int[Q_NODES];
unsigned int *originalDegrees = new unsigned int[Q_NODES];
unsigned int *smallestLast = new unsigned int[Q_NODES];
int *coloring = new int[Q_NODES];

//Declare list of nodes
list<Node> myList;

//Degree bucket
list<unsigned int> *bucketDegrees;

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
		cout << index[i] << ": " << degrees[i] << endl;
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
void displayAdjacenecyList2() {
	int i = 0;
	for (list<Node>::iterator it = myList.begin(); it != myList.end(); it++) {
		cout << (*it).getInfo() << "-> ";
		displayList(originalEdges[i]);
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
void connectNodes3D(double r) {
	double rs = r*r;
	int i = 0;
	//O(n^2)
	for (list<Node>::iterator A = myList.begin(); A != myList.end(); A++) {
		degrees[i] = 0;
		originalDegrees[i] = 0;
		for (list<Node>::iterator B = myList.begin(); B != myList.end(); B++) {
			double distance = pow(((*A).getX() - (*B).getX()), 2) + pow(((*A).getY() - (*B).getY()), 2) + pow(((*A).getZ() - (*B).getZ()), 2);
			if ((distance <= rs) && ((*A).getInfo() != (*B).getInfo())) {
				addEdge(*A, *B);
				degrees[i]++;
				originalDegrees[i]++;
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
		originalDegrees[i] = 0;
		for (list<Node>::iterator B = myList.begin(); B != myList.end(); B++) {
			double distance = pow(((*A).getX() - (*B).getX()), 2) + pow(((*A).getY() - (*B).getY()), 2);
			if ((distance <= rs) && ((*A).getInfo() != (*B).getInfo())) {
				addEdge(*A, *B);
				degrees[i]++;
				originalDegrees[i]++;
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
	for (int i = 0; i < Q_NODES; i++) {
		myList.push_back(Node(i, random(), random(), 0));
		index[i] = i;
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

void createDegreeBucket(int buckets) {
	//Initialize array of lists
	bucketDegrees = new list<unsigned int>[buckets];

	for (int i = 0; i < buckets; i++) {
		for (int j = 0; j < Q_NODES; j++) {
			if (degrees[j] == i) {
				bucketDegrees[i].push_back(j);
			}
		}
	}

	/*
	int i = 0;
	for (list<Node>::iterator it = bucketDegrees.begin(); it != bucketDegrees.end(); it++) {
		cout << (*it).getInfo() << "-> ";
		displayList(edges[i]);
		i++;
		cout << endl;
	}
	*/
}
void displayDegreeBucket(int buckets) {
	for (int i = 0; i < buckets; i++) {
		cout << i << ": ";
		for (list<unsigned int>::iterator it = bucketDegrees[i].begin(); it != bucketDegrees[i].end(); it++) {
			cout << (*it) << ", ";
		}
		cout << endl;
	}
}
int maxDegree() {
	int max = 0;
	for (int i = 0; i < Q_NODES; i++) {
		if (degrees[i] > max) {
			max = degrees[i];
		}
	}
	return max;
}

int findNonEmptyBucket(int buckets) {
	//Returns -1 if all buckets are empty
	for (int i = 0; i < buckets; i++) {
		if (!bucketDegrees[i].empty()) {
			return i;
		}
	}
	return -1;
}
void removeEdge(int adjacentNode, int smallestNode) {
	for (list<Node>::iterator it = edges[adjacentNode].begin(); it != edges[adjacentNode].end();) {
		if ((*it).getInfo() == smallestNode) {
			it = edges[adjacentNode].erase(it);
		}
		else {
			it++;
		}
	}

	//edges[(int)a.getInfo()].push_back(b);
	//edges[adjacentNode].remove(smallestNode);
}
void smallestLastOrdering(int buckets) {
	for (int it = 0; it < Q_NODES; it++) {
		int currentList = findNonEmptyBucket(buckets);
		//Perform if not all buckets are empty:
		if (!(currentList == -1)) {
			//Find node with smallest degree in bucket sorter
			int smallestNode = bucketDegrees[currentList].front();
				//Add it to end of array
			smallestLast[Q_NODES - it - 1] = smallestNode;
			//Remove them from bucket
			bucketDegrees[currentList].pop_front();
			
			//Next: Traverse through adjacent nodes and update their degree and position in bucket sorter.
			//Traverse through adjacent nodes
			for (list<Node>::iterator it = edges[smallestNode].begin(); it != edges[smallestNode].end(); it++) {
				int adjacentNode = (*it).getInfo();
				int adjacentNodeDegree = degrees[adjacentNode];
				//Update their bucket position
					//Add them to a lower degree in the bucket
				bucketDegrees[adjacentNodeDegree - 1].push_back(adjacentNode);
					//Remove them from current degree bucket
				bucketDegrees[adjacentNodeDegree].remove(adjacentNode);
					//Remove the edges (otherwise it could be found again)
				removeEdge(adjacentNode, smallestNode);

				//Update their degree
				degrees[adjacentNode]--;
			}
		}
	}
}
void showSmallestLast() {
	cout << "Smallest last ordering: [Node ID, Act. Deg., Deg. when deleted]" << endl;
	for (int i = 0; i < Q_NODES; i++) {
		int n = smallestLast[i];
		cout << n << " " << originalDegrees[n] << " " << degrees[n] << endl;
	}
	cout << endl;
}
void coloringAlgorithm() {
	for (int i = 0; i < Q_NODES; i++) {
		//Initialize to 0
		coloring[i] = -1;
	}
	
	//Go through small last ordering
	for (int i = 0; i < Q_NODES; i++) {
		int current = smallestLast[i];

		//Possible color combinations. 1 indicates available
		bool color[Q_COLORS + 1] = {0};
		//Iterate through neighbors
		for (list<Node>::iterator it = originalEdges[current].begin(); it != originalEdges[current].end(); it++) {
			//Get an adjacent node
			int adjacentNode = (*it).getInfo();
			if (coloring[adjacentNode] > -1) {
				//Mark color with 1 for not available
				color[coloring[adjacentNode]] = 1;
			}
		}
		int j;
		for (j = 0; j < Q_COLORS; j++) {
			if (color[j] == 0) {
				break;
			}
		}
		coloring[current] = j;
	}
}
void displayColoring() {
	for (int i = 0;i < Q_NODES; i++) {
		cout << i << " " << coloring[i] << endl;
	}
}
int maxColors() {
	int max = 0;
	for (int i = 0; i < Q_NODES; i++) {
		if (coloring[i] > max) {
			max = coloring[i];
		}
	}
	return max;
}
void writeFile(char type) {
	ofstream myfile;
	myfile.open("C:/Users/Alex/Desktop/nodes.txt");
	myfile << type << " 0 0 0 0" << endl;
	myfile << "k " << maxColors() << " 0 0 0" << endl;
	int i = 0;
	for (list<Node>::iterator it = myList.begin(); it != myList.end(); it++) {
		myfile << "n " << (*it).getX() << " " << (*it).getY() << " " << (*it).getZ() << " " << coloring[(int)(*it).getInfo()] << endl;
		list<Node> edgeList = edges[i];

		for (list<Node>::iterator it2 = edgeList.begin(); it2 != edgeList.end(); it2++) {
			myfile << "e " << (*it2).getX() << " " << (*it2).getY() << " " << (*it2).getZ() << " 0" << endl;
		}
		i++;
	}
	myfile.close();
}
int main(int argc, const char * argv[])
{	
	char type;
	double radius = 0.2;
	//cin >> type;
	type = 'u';
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
	cout << endl;
	//showDegrees();
	cout << endl;

	//Perform bucket sort
	int buckets = maxDegree()+1;
	createDegreeBucket(buckets);
	//displayDegreeBucket(buckets);
	
	for (int i = 0; i < Q_NODES; i++) {
		originalEdges[i] = edges[i];
	}

	//Perform smallest last ordering
	smallestLastOrdering(buckets);
	showSmallestLast();

	//Coloring
	coloringAlgorithm();
	displayColoring();
	displayAdjacenecyList2();

	cout << "\nSuccess!\nAvg. deg.: " << averageDegree() << "\nMax deg.: " << maxDegree() << "\nColors needed: " << maxColors()<< endl;
	
	//Release memory
	writeFile(type);
	delete[] edges;
	delete[] degrees;
	delete[] index;
	delete[] bucketDegrees;
	delete[] originalDegrees;
	delete[] smallestLast;
	delete[] coloring;
	delete[] originalEdges;
	cout << "END\n";
	return 0;
}