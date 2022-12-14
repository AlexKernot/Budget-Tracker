#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <json/json.h>
#include "goals.h"
#include "rootInfo.h"

const std::string fileName = "info.json";

//	Number of items to look for inside the file
const int numberOfSettings = 10;
const int maxNumberOfGoals = 100;

Json::Value getInfo(Goals goals[maxNumberOfGoals]);

bool generateSummary(Goals goalsPointer[maxNumberOfGoals], rootInfo userInfo);

std::string roundString(std::string inputString, int decimalPlaces = 2);

rootInfo getUserInfo(Json::Value *userData);

Json::Value addGoal(Goals newGoal, Json::Value root);

Json::Value goalToJson(Goals goal);

int main() {
	std::string command;

	//	Getting data from previous sessions
	Json::Value dataFromFile;

	Goals info[maxNumberOfGoals];
	Goals* goalsPointer = &info[0];

	rootInfo userInfo;

	dataFromFile = getInfo(goalsPointer);

	userInfo = getUserInfo(&dataFromFile);

	if (info[0].getIsError()) {
		std::cout << "\nAn error occured while accessing the info file. Error code " + info[0].getErrorCode() + '\n';
		return -1;
	}

	generateSummary(goalsPointer, userInfo);

	//	TODO: Input processing
	while (true) {
		std::cout << "Please enter a command (type 'help' [Not currently available] to see all available commands)\n";
		std::cin >> command;
	}
	std::cout << "Program closed. Press enter to exit the terminal.";
	std::cin.ignore();
	return 0;
}

Json::Value getInfo(Goals goals[maxNumberOfGoals]) {
	std::ifstream file;
	std::string word;
	file.open(fileName, std::ifstream::binary);

	// If the file isn't open for any reason, throw an error
	if (!file.is_open()) {
		std::cout << "Error opening file";
	}

	Json::Value root;
	file >> root;

	Json::Value goalsList;
	goalsList = root["goals"];

	std::string name;
	int priority;
	double goal;
	double progress;
	double allocation;
	bool allowOverflow;

	for (int i = 0; i < goalsList.size(); ++i) {
		name = goalsList[i].get("name", "null").asString();
		priority = goalsList[i].get("priority", -1).asInt();
		goal = goalsList[i].get("goal", 0).asDouble();
		progress = goalsList[i].get("progress", 0).asDouble();
		allocation = goalsList[i].get("allocation", 0).asDouble();
		allowOverflow = goalsList[i].get("allowOverflow", false).asBool();

		goals[i] = Goals(name, priority, goal, progress, allocation, allowOverflow);
	}
	return root;
}

Json::Value addGoal(const Goals newGoal, Json::Value root) {
	Json::Value json = goalToJson(newGoal);
	root["goals"].append(json);

	std::ofstream file;
	file.open(fileName, std::ofstream::binary);

	// If the file isn't open for any reason, throw an error
	if (!file.is_open()) {
		std::cout << "Error opening file";
	}

	file << root;

	return root;
}

Json::Value goalToJson(Goals goal) {
	Json::Value json;

	json["name"] = goal.getName();
	json["priority"] = 1;
	json["progress"] = goal.getProgress();
	json["goal"] = goal.getGoal();
	json["allocation"] = goal.getAllocation();
	json["allowOverflow"] = false;

	return json;
}

rootInfo getUserInfo(Json::Value *userData) {

	double balance = userData->get("balance", 0).asDouble();
	std::string userName = userData->get("username", "User").asString();

	rootInfo userInfo = rootInfo(userName, balance);
	return userInfo;
}

bool generateSummary(Goals goalsPointer[maxNumberOfGoals], rootInfo userInfo) {

	std::string balance = roundString(std::to_string(userInfo.getTotalBalance()));

	// Base summary
	std::string summary = "Welcome " + userInfo.getUserName() + "!\n"
		+ "You currently have $" + balance + " saved. \n\n";

	// Goals summary

	for (int i = 0; goalsPointer[i].getName() != "Null"; ++i) {

		Goals currentGoal = goalsPointer[i];

		std::string name = currentGoal.getName();
		std::string progress = roundString(std::to_string(currentGoal.getProgress()));
		std::string percentage = roundString(std::to_string(currentGoal.getPecentage()), 1);
		std::string goal = roundString(std::to_string(currentGoal.getGoal()));

		summary +=  name + " has $" + progress + " saved out of $" + goal + " (" + percentage + "%)\n";
	}

	summary += "\n";
	std::cout << summary;

	return true;
}

std::string roundString(std::string inputString, int decimalPlaces) {

	std::string newString;

	// Access each char individually until decimal place
	int i = 0;
	for (i = 0; !(inputString.at(i) == '.'); ++i) {
		newString += inputString.at(i);
	}

	// Add period outside loop
	newString += inputString.at(i);
	++i;

	int repeats = i + decimalPlaces;

	// Add number of decimal places to newString
	for (i = i; i < repeats; ++i) {
		newString += inputString.at(i);
	}
	return newString;
}