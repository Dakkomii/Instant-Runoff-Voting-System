/**
	@file party.h

	Header file for the Party class

	@author Brian Lu (luxx0463@umn.edu)
*/

#ifndef SRC_PARTY_H
#define SRC_PARTY_H

#include <string>
#include <vector>

/**
	@brief Class that represents a party.

	A party has a name and candidates associated with it, as well as
	the total number of votes its candidates have received.
*/
class Party {
public:
	/**
		@brief Party's constructor.

		@param n The name of the party.
	*/
	Party(std::string n) { name = n; }

	/**
		@brief Associate a candidate with the party.

		@param cand_idx The candidate index to be associated with the party.
	*/
	void AddCandidateIndex(int cand_idx);

	/**
		@brief Indicate that the party has received a vote.
	*/
	void AddVote() { total_votes++; }

	/**
		@brief Returns the name of the party.
	*/
	std::string get_name() { return name; };

	/**
		@brief Returns the total number of candidates associated with the party.
	*/ 
	int get_total_candidates() { return total_candidates; };

	/**
		@brief Returns the i-th candidate associated with the party.
	*/ 
	int get_candidate_index(int i) { return candidate_indices[i]; };

	/**
		@brief Returns the total number of votes the party has received.
	*/ 
	int get_total_votes() { return total_votes; };

	/**
		@brief Returns the total number of seats the party has won.
	*/
	int get_total_seats() { return total_seats; };

	/**
		@brief Set the total number of seats the party has won.
	*/
	void set_total_seats(int n) { total_seats = n; };
	

private:
	/// The name of the party.
	std::string name;

	/// The total number of candidates associated with the party.
	int total_candidates{0};

	/// The candidate indices associated with the party.
	std::vector<int> candidate_indices;

	/// The total number of votes that the party has received.
	int total_votes{0};

	/// The total number of seats that the party has won.
	int total_seats{0};
};

#endif
