/**
	@file votingsystem.h

	Header file for the VotingSystem class

	@author King Yiu Suen (suenx008@umn.edu)
*/

#ifndef SRC_VOTINGSYSTEM_H
#define SRC_VOTINGSYSTEM_H

#include <string>
#include <vector>
#include <fstream>

using namespace std;

/**
 * @brief Class that validates and parses the ballot file.
 */
class VotingSystem {
public:
	/**
	 * @brief Validate the ballot file.
	 *
	 * @param fname The filename entered by the user.
	 */
	bool readFileName(string fname);

	/**
	 * @brief Create an Election instance and run the corresponding algorithm.
	 */
	void startAnElection();

	/**
	 * @brief Parse the CSV ballot file.
	 *
	 * @param fname The name of the ballot file to parse.
	 *
	 * @return The parsed data from the ballot file.
	 */
	static vector<vector<string>> CsvToData(string fname);

private:
	/// Name of the ballot file.
	string filename;
};

#endif
