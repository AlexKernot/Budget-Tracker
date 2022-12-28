#include <string>
#include "rootInfo.h"

rootInfo::rootInfo(std::string inputUserName, double inputTotalBalance) {
	userName = inputUserName;
	totalBalance = inputTotalBalance;
}

std::string rootInfo::getUserName() {
	return userName;
}

bool rootInfo::setUserName(std::string inputUserName) {
	userName = inputUserName;
	return true;
}

double rootInfo::getTotalBalance() {
	return totalBalance;
}

bool rootInfo::setTotalBalance(double inputTotalBalance) {
	totalBalance = inputTotalBalance;
	return true;
}