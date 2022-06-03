/**
	@file ballot.cc
	
	Implementation of the methods for the Ballot class
	
	@author Brian Lu (luxx0463@umn.edu)
*/

#include <string>
#include <vector>
#include <algorithm>
#include "ballot.h"

Ballot::Ballot(std::vector<std::string> bstr, int bid) {
	// Assign ID
	id = bid;

	// Assign choices
	bool end_of_ballot = false;
	for (int i = 1; !end_of_ballot; i++) {
		// Search for entry "i" in bstr
		auto iterator = std::find(bstr.begin(), bstr.end(), std::to_string(i));
		// If entry "i" is found
		if (iterator != bstr.end()) {
			// Then push the corresponding candidate index
			// onto position i-1 of the choices vector
			int cand_idx = iterator - bstr.begin();
			choices.push_back(cand_idx);
		} else {
			// Otherwise, indicate that the end of the ballot has been reached
			end_of_ballot = true;
		}
	}
}

int Ballot::GetChoice() {
	// If the rank is lower than the number of preferred candidates
	if (rank < (int) choices.size()) {
		// Then return current preferred candidate
		return choices[rank];
	} else {
		// Otherwise, return -1, indicating that
		// there are no more preferred candidates
		return -1;
	}
}
