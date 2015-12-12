#include <iostream>
#include <fstream>
#include "ListaLineal.h"
#include <list>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include <vector>

#define Q_NODES 1200
#define M_PI 3.14159265358979323846  /* pi */
#define Q_COLORS 100

using namespace std;

struct Sensors {
	int id;
	double x;
	double y;
	double z;
};

//Array of edges in dynamic memory. 
//e.g. edges[33] contains a list with all the edges of node with ID 33
list<Node> *edges = new list<Node>[Q_NODES];
list<Node> *originalEdges = new list<Node>[Q_NODES];

unsigned int *index = new unsigned int[Q_NODES];
unsigned int *degrees = new unsigned int[Q_NODES];
unsigned int *originalDegrees = new unsigned int[Q_NODES];
unsigned int *smallestLast = new unsigned int[Q_NODES];
int *coloring = new int[Q_NODES];
Sensors *nodeInfo = new Sensors[Q_NODES];

//Declare list of nodes
list<Node> myList;

//List of terminal clique
list<int> terminalClique;

//Degree bucket
list<unsigned int> *bucketDegrees;

int colorsNeeded = 1;
char type;

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
		accum += originalDegrees[i];
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
		double x = random();
		double y = random();
		nodeInfo[i].id = i;
		nodeInfo[i].x = x;
		nodeInfo[i].y = y;
		nodeInfo[i].z = 0;

		myList.push_back(Node(i, x, y, 0));
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
			nodeInfo[i].id = i;
			nodeInfo[i].x = x;
			nodeInfo[i].y = y;
			nodeInfo[i].z = 0;
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
		if (originalDegrees[i] > max) {
			max = originalDegrees[i];
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

	int prev = 0;

	for (int i = 0; i < Q_NODES; i++) {
		int n = smallestLast[i];
		if (prev > degrees[n]) {
			break;
		}
		terminalClique.push_front(n);
		prev = degrees[n];
	}
}
void showSmallestLast() {
	cout << "Smallest last ordering: [Node ID, Act. Deg., Deg. when deleted]" << endl;
	for (int i = 0; i < Q_NODES; i++) {
		int n = smallestLast[i];
		cout << n << " " << originalDegrees[n] << " " << degrees[n] << endl;
	}
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
	return max+1;
}
void showTerminalClique() {
	cout << "Terminal clique: ";
	for (std::list<int>::const_iterator iterator = terminalClique.begin(), end = terminalClique.end(); iterator != end; ++iterator) {
		cout << *iterator << " ";
	}
	cout << endl;
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
	i = 0;

	while (!terminalClique.empty()) {
		int node = terminalClique.front();
		myfile << "l " << nodeInfo[node].x << " " << nodeInfo[node].y << " " << nodeInfo[node].z << " " << 0 << endl;
		terminalClique.pop_front();
	}
	myfile.close();
}
void writeGraphData(double radius) {
	ofstream myfile;
	myfile.open("C:/Users/Alex/Desktop/graphData.txt");
	myfile << "avgdeg " << averageDegree() << endl;
	myfile << "maxdeg " << maxDegree() << endl;
	myfile << "colors " << maxColors() << endl;
	myfile << "radius " << radius << endl;
	myfile.close();
	
}
void createSphereRGG() {
	srand(time(NULL));
	for (int i = 0; i < Q_NODES; i++) {
		double x = 2 * random() - 1;
		double y = 2 * random() - 1;
		double z = 2 * random() - 1;
		double squares = x*x + y*y + z*z;
		if ( squares > 1) {
			i--;
		}
		else {
			double reciprocal = sqrt(squares);
			nodeInfo[i].id = i;
			nodeInfo[i].x = x / reciprocal;
			nodeInfo[i].y = y / reciprocal;
			nodeInfo[i].z = z / reciprocal;
			myList.push_back(Node(i, x/reciprocal, y/ reciprocal, z/ reciprocal));
		}
	}
}
void showNodeInfo() {
	for (int i = 0; i < Q_NODES; i++) {
		cout << nodeInfo[i].id << ": " << nodeInfo[i].x << " " << nodeInfo[i].y << " " << nodeInfo[i].z << endl;
	}
}
int findMaxSet(vector<int> &colorEdges){
	int max = 0;
	int maxColor = 0;
	for (int i = 0; i < colorsNeeded; i++) {
		if (colorEdges[i] > max) {
			max = colorEdges[i];
			maxColor = i;
		}
	}
	colorEdges[maxColor] = 0;
	return maxColor;
}
int calculateConnectedness(int i, int j, vector<list<int>> &colorNodes, list<Node> *originalEdges){
	int connectedness = 0;
	list<int> colorSet1 = colorNodes[i];
	list<int> colorSet2 = colorNodes[j];

	for (list<int>::iterator it = colorSet1.begin(); it != colorSet1.end(); it++) {
		for (list<Node>::iterator it2 = originalEdges[(*it)].begin(); it2 != originalEdges[(*it)].end(); it2++) {
			for (list<int>::iterator it3 = colorSet2.begin(); it3 != colorSet2.end(); it3++) {
				if ( (*it2).getInfo() == (*it3) ) {
					connectedness++;
					break;
				}
			}
		}
	}
	return connectedness;
}
void writeBipartite(list<int> setA, list<int> setB, list<Node> *edgeList, string version) {
	ofstream myfile;
	myfile.open("C:/Users/Alex/Desktop/bipartite" + version + ".txt");

	myfile << type << " 0 0 0 0" << endl;
	myfile << "k " << colorsNeeded << " 0 0 0" << endl;
	for (list<int>::iterator it = setA.begin(); it != setA.end(); it++) {
		myfile << "n " << nodeInfo[(*it)].x << " " << nodeInfo[(*it)].y << " " << nodeInfo[(*it)].z << " " << coloring[nodeInfo[(*it)].id] << endl;
		for (list<Node>::iterator it2 = originalEdges[(*it)].begin(); it2 != originalEdges[(*it)].end(); it2++) {
			for (list<int>::iterator it3 = setB.begin(); it3 != setB.end(); it3++) {
				if ((*it2).getInfo() == (*it3)) {
					myfile << "e " << (*it2).getX() << " " << (*it2).getY() << " " << (*it2).getZ() << " 0" << endl;
					break;
				}
			}
		}
	}
	for (list<int>::iterator it = setB.begin(); it != setB.end(); it++) {
		myfile << "n " << nodeInfo[(*it)].x << " " << nodeInfo[(*it)].y << " " << nodeInfo[(*it)].z << " " << coloring[nodeInfo[(*it)].id] << endl;
	}
	myfile.close();
}
void findBipartite(vector<list<int>> &colorNodes, vector<int> colorEdges, int &i1, int &j1, int &i2, int &j2) {
	int setsQ = 4;
	vector<int> largestColors(setsQ);
	//Find sets with maximum edges
	if (colorsNeeded >= 4) {
		for (int i = 0; i < 4; i++) {
			int color = findMaxSet(colorEdges);
			cout << i << " is " << color << endl;
			largestColors[i] = color;
		}
	}	
	else {
		setsQ = colorsNeeded;
		for (int i = 0; i < colorsNeeded; i++) {
			int color = findMaxSet(colorEdges);
			cout << i << " is " << color << endl;
			largestColors[i] = color;
		}
	}

	//Check all combinations
	int maxi = 0;
	int maxj = 0;
	int maxConnect = 0;

	int maxi2 = 0;
	int maxj2 = 0;
	int maxConnect2 = 0;
	for (int i = 0; i < setsQ; i++) {
		for (int j = i; j < setsQ; j++) {
			if (i != j) {
				int quantity = calculateConnectedness(i, j, colorNodes, originalEdges);
				if (quantity > maxConnect2) {
					maxi2 = i;
					maxj2 = j;
					maxConnect2 = quantity;
					if (quantity > maxConnect) {
						maxi2 = maxi;
						maxj2 = maxj;
						maxConnect2 = maxConnect;
						maxi = i;
						maxj = j;
						maxConnect = quantity;
					}
				}
				cout << "Sets (" << i << ", " << j << ") have " << quantity << endl;
			}
		}
	}

	i1 = maxi;
	j1 = maxj;
	i2 = maxi2;
	j2 = maxj2;
}
void calculateBiData(vector<int> &colorInfo, vector<list<int>> &colorSets, vector<int> &colorEdgeCount) {
	//Initialize
	for (int i = 0; i < colorsNeeded; i++) {
		colorInfo[i] = 0;
	}
	//Count how many for each node
	for (int i = 0; i < Q_NODES; i++){
		colorInfo[coloring[i]]++;
		colorSets[coloring[i]].push_back(i);
		for (list<Node>::iterator it2 = originalEdges[i].begin(); it2 != originalEdges[i].end(); it2++) {
			colorEdgeCount[coloring[i]]++;
		}
	}
}
void displayBiData(vector<int> &colorInfo, vector<list<int>> &colorSets, vector<int> &colorEdgeCount) {
	for (int i = 0; i < colorsNeeded; i++) {
		cout << "Color: " << i << " -> There are " << colorInfo[i] << endl;
		cout << "# of edges = " << colorEdgeCount[i] << endl;
		for (list<int>::iterator it2 = colorSets[i].begin(); it2 != colorSets[i].end(); it2++) {
			cout << (*it2) << " ";
		}
		cout << endl << endl;
	}
}
void writeSensorsUsed() {

}
int main(int argc, const char * argv[]){	
	double radius = 0.6;
	//cin >> type;
	type = 's';

	//Degree approximation
	/*
	int degree = 30;
	radius = sqrt(degree / (Q_NODES*M_PI));
	*/
	cout << "Radius: " << radius << endl;

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
			createSphereRGG();
			connectNodes3D(radius);
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
	cout << "\nDEGREE: "<< averageDegree() << endl;

	//Perform smallest last ordering
	smallestLastOrdering(buckets);
	//showSmallestLast();

	//Coloring
	coloringAlgorithm();
	colorsNeeded = maxColors();
	//displayColoring();

	//Find bipartite subgraph
		//Find how many and which nodes, in each color
	vector<int> colorInfo(colorsNeeded);
	vector<list<int>> colorSets(colorsNeeded);
	vector<int> colorEdgeCount(colorsNeeded);
	calculateBiData(colorInfo, colorSets, colorEdgeCount);
	//displayBiData(colorInfo, colorSets, colorEdgeCount);
		//Find max independent set
	int i1, j1, i2, j2;
	findBipartite(colorSets, colorEdgeCount, i1, j1, i2, j2);

	writeBipartite(colorSets[i1], colorSets[j1], originalEdges, "1");
	writeBipartite(colorSets[i2], colorSets[j2], originalEdges, "2");
	writeSensorsUsed();

	cout << "List of nodes per color set:\n";
	for (int i = 0; i < colorsNeeded; i++) {
		cout << i << " has " << colorEdgeCount[i] << endl;
	}

	//displayColoring();
	//displayAdjacenecyList2();

	//Find terminal clique
	//showTerminalClique();

	cout << "\nSuccess!\nAvg. deg.: " << averageDegree() << "\nMax deg.: " << maxDegree() << "\nColors needed: " << colorsNeeded << endl;
	
	//Release memory
	writeFile(type);
	writeGraphData(radius);

	delete[] edges;
	delete[] degrees;
	delete[] index;
	delete[] bucketDegrees;
	delete[] originalDegrees;
	delete[] smallestLast;
	delete[] coloring;
	delete[] originalEdges;
	delete[] nodeInfo;
	cout << "END\n";
	return 0;
}