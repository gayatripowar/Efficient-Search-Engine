/*
Application class
*/

#include<iostream>
#include<string>
#include<vector>
using namespace std;
#include"graph.h"

#pragma once

class Application{
private:
	string name;
	float averageRating;
	int noOfDownload;
	int socialNetworkInstall;
	int noOfComment;
	float totalWeight;
	vector<string> friendList;
	float price;
public:
	void setName(string);
	string getName();
	Application();
	void setAverageRating(float);
	float getAverageRating();

	void setNoOfDownload(int);
	int getNoOfDownload();

	void setSocialNetworkInstall(int);
	int getSocialNetworkInstall();

	void setNoOfComment(int);
	int getNoOfComment();

	void setPrice(float);
	float getPrice();

	float getTotalWeight();

};