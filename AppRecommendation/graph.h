/*
Graph.h
*/

#include<iostream>
#include <list>
#include<string>
#include<vector>
#include<map>
#include<fstream>
using namespace std;

#pragma once
// This class represents a directed graph using adjacency list representation
class BFS
{
	int V;    // No. of vertices
	list<list<int>> *adj;    // Pointer to an array containing adjacency lists
	vector<int>* vec;
	
public:
	//BFS(int noOfVertices);  // Constructor
	BFS();
	struct user{
		string name;
		vector<string>* userApp;

		bool user::operator <(const user &A) const
		{
			return ((this->name.compare(A.name))<0?1:0);
		}
	};

	map<user, int> *mymap2;
	void addEdge(int, int); // function to add an edge to graph
	void BFSfunc(int);  // prints BFS traversal from a given source s
	void createGraph();
	void getFirstConnection(user );
	user FindI(map<user, int>& , int);
	bool updateUserInstallApp(string, vector<string>*);

	vector<user> *users;
	vector<user> *appUsers;
};