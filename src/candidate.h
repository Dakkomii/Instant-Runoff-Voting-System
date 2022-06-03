/**
	@file candidate.h
	
	Header file for the Candidate class
	
	@author Brian Lu (luxx0463@umn.edu)
*/

#ifndef SRC_CANDIDATE_H
#define SRC_CANDIDATE_H

#include <string>
#include <vector>

/**
	@brief Class that represents a candidate.

	A candidate has a name and party, as well as the total number of votes
	received and the Ballot IDs in which it is the preferred candidate.
*/
class Candidate {
public:
	/**
		@brief Candidate's constructor.

		@param n The name of the candidate.
		@param p The party of the candidate.
	*/
	Candidate(std::string n, std::string p);

	/**
		@brief Distribute a Ballot to the candidate by storing the Ballot ID.

		@param bid The ID of the Ballot to be distributed to the candidate.
	*/
	void AddBallotId(int bid);

	/**
		@brief Remove all of the candidate's votes.

		@return A vector of the candidate's Ballot IDs.
	*/
	std::vector<int> RemoveVotes();

	/**
		@brief Return the name of the candidate.
	*/
	std::string get_name() { return name; }

	/**
		@brief Return the party of the candidate.
	*/
	std::string get_party() { return party; }

	/**
		@brief Return the candidate's total number of votes.
	*/
	int get_total_votes() { return total_votes; }

private:
	/// The name of the candidate.
	std::string name;

	/// The party of the candidate.
	std::string party;

	/// The total number of votes that the candidate has received.
	int total_votes{0};

	/// The Ballot IDs in which the candidate is the preferred candidate.
	std::vector<int> votes;
};

#endif
