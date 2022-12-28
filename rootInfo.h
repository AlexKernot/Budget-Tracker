#pragma once

#include <string>

class rootInfo {
	std::string userName = "User";
	double totalBalance = 0;

public:
	rootInfo(std::string inputUserName = "User", double inputTotalBalance = 0);
	std::string getUserName();
	bool setUserName(std::string inputUserName);
	double getTotalBalance();
	bool setTotalBalance(double inputTotalBalance);
};