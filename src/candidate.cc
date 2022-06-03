/**
	@file candidate.cc
	
	Implementation of the methods for the Candidate class
	
	@author Brian Lu (luxx0463@umn.edu)
*/

#include <string>
#include <vector>
#include "candidate.h"

Candidate::Candidate(std::string n, std::string p) {
	name = n;
	party = p;
}

void Candidate::AddBallotId(int bid) {
	votes.push_back(bid);
	total_votes++;
}

std::vector<int> Candidate::RemoveVotes() {
	total_votes = 0;
	return votes;
}
