#include"application.h"

Application::Application(){
	name = "";
	averageRating = 0.0;
	noOfDownload =0;
	socialNetworkInstall =0;
	noOfComment = 0;
	totalWeight =0.0;
	price = 0.0;
}

void Application::setName(string appName){
	name = appName;
}

string Application::getName(){
	return name;
}

void Application::setAverageRating(float appRating){
	averageRating = appRating;
}

float Application::getAverageRating(){
	return averageRating;
}

void Application::setNoOfDownload(int appDownload){
	noOfDownload = appDownload;
}

int Application::getNoOfDownload(){
	return noOfDownload;
}

void Application::setSocialNetworkInstall(int appSocialInstall){
	socialNetworkInstall = appSocialInstall;
}

int Application::getSocialNetworkInstall(){
	return socialNetworkInstall;
}

void Application::setNoOfComment(int appComment){
	noOfComment = appComment;
}

int Application::getNoOfComment(){
	return noOfComment;
}

void Application::setPrice(float amount){
	price = amount;
}

float Application::getPrice(){
	return price;
}

float Application::getTotalWeight(){
	/*cout << "\n For Ap: " << this->name;
	cout << "Social Network Install=" << socialNetworkInstall;
	totalWeight = (0.4)*averageRating + (0.2)*noOfDownload + (0.1)*noOfComment;
	cout << "\nTtal weight w/o" << totalWeight;*/
	totalWeight = (0.4)*averageRating + (0.3)*socialNetworkInstall +(0.2)*noOfDownload + (0.1)*noOfComment;
	return totalWeight;
}