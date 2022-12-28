#include "goals.h"
#include <string>

Goals::Goals(std::string a_name, int a_priority, double a_goal, double a_progress, double a_allocation, bool a_allowOverflow) {

	name = a_name;
	priority = a_priority;
	goal = a_goal;
	progress = a_progress;
	allocation = a_allocation;
	allowOverflow = a_allowOverflow;
}

double Goals::getPecentage() {
	return progress / goal;
}

std::string Goals::getName() {
	return name;
}

bool Goals::setName(std::string a_name) {
	name = a_name;
	return true;
}

double Goals::getGoal() {
	return goal;
}

bool Goals::setGoal(double a_goal) {
	goal = a_goal;
	return true;
}

double Goals::getProgress() {
	return progress;
}

bool Goals::setProgress(double a_progress) {
	progress = a_progress;
	return true;
}

double Goals::getAllocation() {
	return allocation;
}

bool Goals::setAllocation(double a_allocation) {
	allocation = a_allocation;
	return true;
}

bool Goals::getIsError() {
	return isError;
}

int Goals::getErrorCode() {
	return errorCode;
}

bool Goals::error(bool createError, int setErrorCode) {
	isError = createError;
	errorCode = setErrorCode;

	return true;
}
