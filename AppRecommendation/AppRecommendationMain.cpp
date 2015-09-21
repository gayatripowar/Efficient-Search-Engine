/*
App Recommendation Project to suggest the best list of user search for app. This project replicates some of the
functionalities of Google Play or Apple iTunes.

Written by Ankit Shah, Gayatri Powar, Suvigya Tripathi
towards the fulfilment of the credits for Data Structures and Algorithms Course
*/

#include"playStore.h"
#include"graph.h"
#include<iostream>
#include<vector>
#include<iterator>
#include<iomanip>
#include<chrono>
using namespace std;
#pragma once

int main()
{
	//Continuously keeps input from user
	while (1)
	{
		string key, userName;
		BFS::user inputUser;
		cout << "**********************************\n";
		cout << "* Enter your name: ";
		cin >> userName;
		cout << "**********************************\n";
		inputUser.name = userName;
		cout << "**********************************\n";
		cout << "* Enter app to be searched: ";
		cin >> key;
		//key = "a";
		cout << "**********************************\n";
		chrono::steady_clock::time_point start1 = chrono::steady_clock::now(); //takes the current time
		//Creating Playstore object. PlayStore class has all the functinalities.
		PlayStore *playStore = new PlayStore();

		//Reads the App database from XML, stores it in the vector. Create Global App Database
		playStore->populateDatabase();
		
		//takes input from user. userName: Login name, Key: substring to be searched in App Database
		

		//Search the substring enter by the user in the database. Searching uses Z- Algorithm. The searched apps
		//are stored in temporary data base.
		chrono::steady_clock::time_point start = chrono::steady_clock::now(); //takes the current time
		playStore->search(key);///////////////////////////////////////////////////////////////////////
		chrono::steady_clock::time_point end = chrono::steady_clock::now(); //takes the reading after executing the implementation
		typedef chrono::duration<int, milli> millisecs_t;
		millisecs_t duration(chrono::duration_cast<millisecs_t>(end - start)); //calculates time difference between start and end
		

		//Creates the data base of the Apps installed by all the users.
		playStore->socialNetworkInstall();

		//This function finds the first connection of the entered userName from the SocialNetwork graph. It uses
		//Breadth First Search (BFS) to find the first connections of a user. 
		playStore->bfs->getFirstConnection(inputUser);

		//Updates the searched list with the total number of install for an App installed by the first connection
		//of the user.
		playStore->updateSocialNetworkInstall(playStore->filteredList, playStore->bfs->appUsers);

		int size = playStore->filteredList->size();
		//The search list updated with total number of installs are sorted using 3-Way Quick Weighted Sort. 
		//Apps are given importance or weights and then applied weighted sort.

		start = chrono::steady_clock::now(); //starts timer
		playStore->Sort((playStore->filteredList), 0, size - 1);//////////////////////////////////////////
		end = chrono::steady_clock::now();//gets the current time
		typedef chrono::duration<int, milli> millisecs_t;
		millisecs_t duration1(chrono::duration_cast<millisecs_t>(end - start));
		

		//cout << "\nFiltered Apps:\n";
		////cout << key;

		//for (vector<Application>::iterator I = playStore->filteredList->begin(); I != playStore->filteredList->end(); I++)
		//{
		//	cout << I->getName() << '\n';
		//}

		//Prints out the recommended list of Apps.

		vector<Application> *freeList = new vector < Application > ;
		vector<Application> *paidList = new vector < Application >;
		for (vector<Application>::iterator I = playStore->filteredList->begin(); I != playStore->filteredList->end(); I++)
		{
			if (I->getPrice() != 0)
			{
				paidList->push_back(*I);
			}

			else
			{
				freeList->push_back(*I);
			}
		}

		cout << "\nRecommended Free App List:\n\n";
		for (vector<Application>::iterator I = freeList->begin(); I != freeList->end(); I++)
		{
			cout << I->getName() << "\t"<< I->getAverageRating()<<'\t'<<"Free"<<"\n";//<< I->getTotalWeight() << std::setw(20)<<'\n';
		}

		cout << "\nRecommended Paid App List:\n\n";
		for (vector<Application>::iterator I = paidList->begin(); I != paidList->end(); I++)
		{
			cout << I->getName() << "\t" << I->getAverageRating() <<"\t"<< I->getPrice() << "$\n";//<< I->getTotalWeight() << std::setw(20)<<'\n';
		}

		chrono::steady_clock::time_point end1 = chrono::steady_clock::now(); //takes the reading after executing the implementation
		typedef chrono::duration<int, milli> millisecs_t;
		millisecs_t duration2(chrono::duration_cast<millisecs_t>(end1 - start1)); //calculates time difference between start and end

		cout << "\nSorting Time: " << duration1.count() << " milliseconds.\n";
		cout << "\nSearching Time: " << duration.count() << " milliseconds.\n\n";
		cout << "\nTotal Time: " << duration2.count() << " milliseconds.\n";


		cout << "\n************************************************************\n";
		
		//map<BFS::user, int>::iterator I;
		/*for (I = bfs.mymap2.begin(); I != bfs.mymap2.end(); I++){
			cout << I->first.name << "\n";
		}*/
		
	
		//vector<string> vec = { "hi","hello" };
		
		
	}
	return 0;
}