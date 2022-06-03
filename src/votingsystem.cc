/**
	@file votingsystem.cc

	Implementation of the methods for the VotingSystem class

	@author King Yiu Suen (suenx008@umn.edu)
*/

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <boost/tokenizer.hpp>
#include "votingsystem.h"
#include "irelection.h"
#include "oplelection.h"

using namespace std;

bool VotingSystem::readFileName(string fname) {
	// Check if the file extension is csv
	if (fname.length() < 4 || fname.substr(fname.length() - 4) != ".csv") {
		cout << "File must be in csv format!" << endl << endl;
		return false;
	}
	// Check if the file exists
	if (!ifstream(fname)) {
		cout << "File does not exist!" << endl << endl;
		return false;
	}
	filename = fname;
	return true;
}

void VotingSystem::startAnElection() {
	vector<vector<string>> data = CsvToData(filename);
	Election* election;

	// Read the election type
	if (data[0][0] == "IR") {
		election = new IRElection(data);
	} else if (data[0][0] == "OPL") {
		election = new OPLElection(data);
	}
	election->Run();
	return;
}

vector<vector<string>> VotingSystem::CsvToData(string fname) {
	vector<vector<string>> data;
	fstream csv(fname, ios::in);
	string csvline;

	while (getline(csv, csvline)) {
		vector<string> line;

		typedef boost::tokenizer<boost::char_separator<char>> Tokenizer;
		boost::char_separator<char> sep(", ", "", boost::keep_empty_tokens);
		Tokenizer tok(csvline, sep);

		for (Tokenizer::iterator beg = tok.begin(); beg != tok.end(); beg++) {
			string entry = *beg;
			entry.erase(remove(entry.begin(), entry.end(), '['), entry.end());
			entry.erase(remove(entry.begin(), entry.end(), ']'), entry.end());
			entry.erase(remove(entry.begin(), entry.end(), '('), entry.end());
			entry.erase(remove(entry.begin(), entry.end(), ')'), entry.end());
			line.push_back(entry);
		}

		data.push_back(line);
	}
	return data;
}
