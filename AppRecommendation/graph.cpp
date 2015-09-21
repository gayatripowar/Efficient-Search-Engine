/*
Graph Class function definition
*/

#include "graph.h"

//BFS constructor. All the vectors and maps are initialized and memory is allocated.
BFS::BFS()
{
	vec = new vector < int > ;
	users = new vector < user > ;
	appUsers = new vector < user >;
	mymap2 = new map < user, int > ;
	createGraph();
}


//addEdge constructs edge between v and w.
void BFS::addEdge(int v, int w)
{
	//iterate over the adjacency list
	for (list<list<int>>::iterator I = adj->begin(); I != adj->end(); I++)
	{
		//Find v and push w on v's list
		if ((*I).front() == v)
		{
			(*I).push_back(w);
			break;
		}
	}

	//To create undirected graph, push v on w's list
	for (list<list<int>>::iterator I = adj->begin(); I != adj->end(); I++)
	{
		if ((*I).front() == w)
		{
			(*I).push_back(v);
			break;
		}
	}
}


//Function to find the first connection of the input user
void BFS::BFSfunc(int s)
{
	// 'i' will be used to get all adjacent vertices of a vertex
	for (list<list<int>>::iterator I = adj->begin(); I != adj->end(); I++)
	{
		if ((*I).front() == s)
		{
			for (list<int>::iterator J = I->begin(); J != I->end(); J++){
				vec->push_back(*J);
			}
			break;
		}
	}
}


//Function to read the data from the text file and create the graph
void BFS::createGraph(){
	string filename = "C:/Users/Suvigya/Desktop/UserGraph.txt";
	string tmp1;
	string tmp2;
	int arraySize = 0;
	ifstream fin(filename);
	
	if (!fin.is_open())
	{
		//Throws exception if file is not opened
		cout << "\nFile not opened";
		return;
	}
	int userCnt = 0;
	adj = new list<list<int>>;

	//Read user from text file until EOF is reached.
	while (fin >> tmp1>>tmp2)
	{
		list<int> *list1=new list<int>;
		list<int> *list2=new list<int>;
		user currentUser1, currentUser2;
		currentUser1.name = tmp1;
		currentUser1.userApp = new vector < string > ;
		currentUser2.userApp = new vector < string >;
		
		//Check if the first input name is present in map. If not present, enter into Map and push onto adjacency list
		if (mymap2->find(currentUser1) == mymap2->end())
		{
			users->push_back(currentUser1);
			(*mymap2)[currentUser1] = userCnt;
			list1->push_back(userCnt);
			adj->push_back(*list1);
			userCnt++;
		}

		currentUser2.name = tmp2;
		//Check if the second input name is present in map. If not present, enter into Map and push onto adjacency list
		if (mymap2->find(currentUser2) == mymap2->end())
		{
			users->push_back(currentUser2);
			(*mymap2)[currentUser2] = userCnt;
			list2->push_back(userCnt);
			adj->push_back(*list2);
			userCnt++;
		}

		//Find the key for a particular name to pass into addEdge function
		int x = mymap2->at(currentUser1);
		int y = mymap2->at(currentUser2);
		addEdge(x, y);
	}
	
	//close file
	fin.close();
	V = userCnt + 1;
	cout << "\nGraph Created....!!!\n";
}


//
void BFS::getFirstConnection(user a){
	try{
		int mapNum = mymap2->at(a);
		BFSfunc(mapNum);
		for (int i = 1; i < vec->size(); i++){
			//cout << (FindI(*mymap2, vec->at(i))).name << "\n";
			appUsers->push_back((FindI(*mymap2, vec->at(i))));
		}

		for (int i = 0; i < appUsers->size(); i++){
			cout << "Apps Installed by first connection of "<< a.name<<" : " <<(appUsers->at(i)).name << "\n" ;
			for (int j = 0; j < appUsers->at(i).userApp->size(); j++){
				cout << appUsers->at(i).userApp->at(j) << '\t';
			}
			cout << "\n\n";
		}
	}
	catch (const std::out_of_range& oor) {
		std::cerr << "User not present in graph"<< '\n';
	}
}

BFS::user BFS::FindI(map<user, int>& mymap, int i){
	map<user, int>::iterator I;
	for (I = mymap.begin(); I != mymap.end(); I++){
		if ((*I).second == i){
			return (*I).first;
		}
	}
}


bool BFS::updateUserInstallApp(string name, vector<string>* userApp){
	user searchUser;
	searchUser.name = name;
	map<user, int>::iterator I = mymap2->find(searchUser);
	if ( I != mymap2->end())
	{
		*I->first.userApp = *userApp ;
	}
	return true;
}
