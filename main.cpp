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

rootInfo getInfo(Goals goals[100]);

bool generateSummary(Goals goalsPointer[100], rootInfo userInfo);

std::string roundString(std::string inputString, int decimalPlaces = 2);

int main() {
	std::string command;

	//	Getting data from previous sessions
	Goals info[100];
	Goals* goalsPointer = &info[0];

	rootInfo userInfo;

	userInfo = getInfo(goalsPointer);

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

rootInfo getInfo(Goals goals[100]) {
	std::ifstream file;
	std::string word;
	file.open(fileName, std::ifstream::binary);

	// If the file isn't open for any reason, throw an error
	if (!file.is_open()) {
		std::cout << "Error opening file";
	}

	Json::Value root;
	file >> root;

	double balance = root.get("balance", 0).asDouble();
	std::string userName = root.get("username", "User").asString();

	rootInfo userInfo = rootInfo(userName, balance);

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
	return userInfo;
}

bool generateSummary(Goals goalsPointer[100], rootInfo userInfo) {

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

	int i = 0;
	for (i = 0; !(inputString.at(i) == '.'); ++i) {
		newString += inputString.at(i);
	}
	newString += inputString.at(i);
	++i;

	int repeats = i + decimalPlaces;

	for (i = i; i < repeats; ++i) {
		newString += inputString.at(i);
	}
	return newString;
	// Access each char individually until decimal place

	// Add period and number of decimal places outside loop

	// Return new string.
}