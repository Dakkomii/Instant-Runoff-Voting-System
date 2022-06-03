/**
	@file election_logger.cc

	Implementation of the methods for the Election Logger class

	@author Brian Lu (luxx0463@umn.edu)
*/

#include <string>
#include <ctime>				// time, localtime
#include <cstdio>				// snprintf
#include <chrono>				// std::chrono
#include "election_logger.h"

ElectionLogger::ElectionLogger(std::string output_dir) {
	// Get the current time
	std::string current_time = GetCurrentTime();

	// Open the audit file and media report
	audit_file.open(output_dir + "VotingSystem_AuditFile_" + current_time + ".txt");
	media_report.open(output_dir + "VotingSystem_MediaReport_" + current_time + ".txt");
}

ElectionLogger::~ElectionLogger() {
	// Close the audit file and media report
	audit_file.close();
	media_report.close();
}

std::string ElectionLogger::GetCurrentTime() {
	// Get the local time
	time_t timer = time(nullptr);
	tm* now = localtime(&timer);
	auto us = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count() % 1000000;

	// Format the local time in a C-string, then return it as a C++ string
	char current_time[27];
	snprintf(current_time, 27, "%04d-%02d-%02d_%02d:%02d:%02d.%06d", 1900+now->tm_year, now->tm_mon, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec, (int) us);
	return std::string(current_time);
}
