#pragma once

#include <string>

class Goals {
	std::string name;
	int priority;
	double goal;
	double progress;
	double allocation;
	bool allowOverflow;
	bool isError = false;
	int errorCode = 0;

public:

	Goals(std::string a_name = "Null", int a_priority = 0, double a_goal = 0, double a_progress = 0, double a_allocation = 0, bool a_allowOverflow = false);

	double getPecentage();

	std::string getName();

	bool setName(std::string a_name);

	double getGoal();

	bool setGoal(double a_goal);

	double getProgress();

	bool setProgress(double a_progress);

	double getAllocation();

	bool setAllocation(double a_allocation);

	bool getIsError();

	int getErrorCode();

	bool error(bool createError, int setErrorCode);
};