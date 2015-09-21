#include"playStore.h"
#include<algorithm>
#include<iterator>

typedef std::vector<Application>::iterator iter;
PlayStore::PlayStore(){
	appVector = new vector<Application>();
	filteredList = new vector < Application >;
	bfs = new BFS();
}

void PlayStore::populateDatabase(){
	
	const char *filename = "C:/Users/Suvigya/Documents/Visual Studio 2013/Projects/AppRecommendation/AppRecommendation/XMLFile1024.xml";
	TiXmlDocument doc(filename);
	bool isFileLoaded = doc.LoadFile();
	if (isFileLoaded == false)
	{
		return;
	}
	TiXmlElement *Google = doc.RootElement();
	TiXmlElement* Applications = Google->FirstChildElement();
	if (!Applications)
		return;
	for (TiXmlElement* Apk = Applications->FirstChildElement(); Apk; Apk = Apk->NextSiblingElement())
	{
		float averageRating = 0.0;
		int downloads = 0;
		int noOfComments = 0;
		int price = 0;
		string ApplicationName = Apk->GetText();
		Apk->QueryFloatAttribute("AverageRating", &averageRating);
		Apk->QueryIntAttribute("Downloads", &downloads);
		Apk->QueryIntAttribute("Comments", &noOfComments);
		Apk->QueryIntAttribute("Price", &price);
		Application tempapp;
		tempapp.setName(ApplicationName);
		tempapp.setAverageRating(averageRating);
		tempapp.setNoOfDownload(downloads);
		tempapp.setNoOfComment(noOfComments);
		tempapp.setPrice(price);

		if (appVector != NULL){
			appVector->push_back(tempapp);
		}
	}
}

bool PlayStore::zAlgorithm(string pattern, string target)
{
	transform(pattern.begin(), pattern.end(), pattern.begin(), ::tolower);
	transform(target.begin(), target.end(), target.begin(), ::tolower);

	string s = pattern + '$' + target;
	int n = s.length();
	vector<int> z(n, 0);

	int goal = pattern.length();
	int r = 0, l = 0, i;
	for (int k = 1; k<n; k++)
	{
		if (k>r)
		{
			for (i = k; i<n && s[i] == s[i - k]; i++);
			if (i>k)
			{
				z[k] = i - k;
				l = k;
				r = i - 1;
			}
		}
		else
		{
			int kt = k - l, b = r - k + 1;
			if (z[kt]>b)
			{
				for (i = r + 1; i<n && s[i] == s[i - k]; i++);
				z[k] = i - k;
				l = k;
				r = i - 1;
			}
		}
		if (z[k] == goal)
			return true;
	}
	return false;
}

void PlayStore::search(string keyword)
{
	for (vector<Application>::iterator I = appVector->begin(); I != appVector->end(); I++)
	{
		string currentAppName = I->getName();
		bool isPresent = zAlgorithm(keyword, currentAppName);
		if (isPresent)
		{
			filteredList->push_back(*I);
		}
	}
}

void PlayStore::Sort(vector<Application>* filteredList, int begin, int end)
{
	if (end <= begin)
		return;
	int lt = begin;
	int gt = end;
	Application v = (*filteredList)[begin];
	int i = begin;

	while (i <= gt)
	{
		if ((*filteredList)[i].getTotalWeight() > v.getTotalWeight())
		{
			swap((*filteredList)[lt++], (*filteredList)[i++]);
		}
		else if ((*filteredList)[i].getTotalWeight() < v.getTotalWeight())
		{
			swap((*filteredList)[i], (*filteredList)[gt--]);
		}

		else
			i++;
	}

	Sort(filteredList, begin, lt - 1);
	Sort(filteredList, gt + 1, end);
}


void PlayStore::socialNetworkInstall()
{
	const char *filename = "C:/Users/Suvigya/Documents/Visual Studio 2013/Projects/AppRecommendation/AppRecommendation/UserInstalledApplications.xml";
	TiXmlDocument doc(filename);
	bool isFileLoaded = doc.LoadFile();
	if (isFileLoaded == false)
	{
		return;
	}
	TiXmlElement *Google = doc.RootElement();
	TiXmlElement* Users = Google->FirstChildElement();
	if (!Users)
		return;
	for (TiXmlElement* User = Users->FirstChildElement(); User; User = User->NextSiblingElement())
	{
		if (!User)
			return;
		string UserName = User->Attribute("Name");
		/*cout << "\n\n\nUserName :";
		cout << UserName;*/
		vector<string> *applist = new vector<string>;
		for (TiXmlElement* Application = User->FirstChildElement(); Application; Application = Application->NextSiblingElement())
		{
			string ApplicationName = Application->GetText();
			applist->push_back(ApplicationName);
		}
		bfs->updateUserInstallApp(UserName, applist);
	}
}


void PlayStore::updateSocialNetworkInstall(vector<Application>* filteredList, vector<BFS::user>* appUsers)
{
	vector<Application>::iterator I;
	vector<Application>::iterator appVectorIter;
	vector<BFS::user>::iterator J;

	for (I = filteredList->begin(); I != filteredList->end(); I++)
	{
		float count = 0;
		for (J = appUsers->begin(); J != appUsers->end(); J++)
		{
			for (int k = 0; k < J->userApp->size(); k++)
			{
				if (I->getName() == J->userApp->at(k))
					count++;
			}
		}
		if (count != 0)
		{
			float socialNetworkInstalls = (count / appUsers->size()) * 100.0;

			for (appVectorIter = appVector->begin(); appVectorIter != appVector->end(); appVectorIter++)
			{
				if (I->getName() == appVectorIter->getName())
				{
					I->setSocialNetworkInstall(socialNetworkInstalls);
				}
			}
		}
	}
}