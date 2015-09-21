/*
PlayStore header file
*/

#include<iostream>
#include<vector>
#include<string>
#include"application.h"
#include "tinyxml.h"
#include "graph.h"
#pragma once
using namespace std;


class PlayStore{
private:
	bool zAlgorithm(string pattern, string target);

public:
	BFS *bfs;
	PlayStore();
	void populateDatabase();
	void socialNetworkInstall();
	vector<Application> *appVector;
	vector<Application>* filteredList;
	
	void Sort(vector<Application>*,int,int);
	void search(string keyword);

	void updateSocialNetworkInstall(vector<Application>*, vector<BFS::user>* );
	
	
};


