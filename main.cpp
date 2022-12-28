#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <json/json.h>
#include "goals.h"

const std::string fileName = "info.json";

//	Number of items to look for inside the file
const int numberOfSettings = 10;

bool getInfo(Goals goals[255]);

int main() {
	std::string command;

	//	Getting data from previous sessions
	Goals info[255];
	Goals* ptr = &info[0];
	getInfo(ptr);
	if (info[0].getIsError()) {
		std::cout << "\nAn error occured while accessing the info file. Error code " + info[0].getErrorCode() + '\n';
		return -1;
	}

	//	TODO: Input processing
	while (true) {
		std::cout << "Please enter a command (type 'help' [Not currently available] to see all available commands)\n";
		std::cin >> command;
	}
	std::cout << "Program closed. Press enter to exit the terminal.";
	std::cin.ignore();
	return 0;
}

bool getInfo(Goals goals[255]) {
	std::ifstream file;
	std::string word;
	file.open(fileName, std::ifstream::binary);

	// If the file isn't open for any reason, throw an error
	if (!file.is_open()) {
		std::cout << "Error opening file";
	}

	Json::Value root;
	file >> root;

	std::string balance = root.get("balance", "null").asString();

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
	return true;
}