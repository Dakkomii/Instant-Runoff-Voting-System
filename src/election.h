/**
	@file election.h

	Header file for the Election class

	@author Brian Lu (luxx0463@umn.edu)
*/

#ifndef SRC_ELECTION_H
#define SRC_ELECTION_H

#include <string>
#include <vector>
#include <fstream>
#include "candidate.h"
#include "ballot.h"
#include "election_logger.h"

/**
	@brief Abstract class that represents an election.

	Provides virtual and non-virtual methods for derived Election classes.
*/
class Election {
public:
	virtual ~Election() = default;

	/**
		@brief Run the election.
	*/
	virtual void Run() = 0;

	/// Return the total number of candidates running in the election.
	int get_total_candidates() { return total_candidates; }

	/// Return the i-th candidate (0-indexed) running in the election.
	Candidate get_candidate(int i) { return *candidates[i]; }

	/// Return the total number of ballots casted in the election.
	int get_total_ballots() { return total_ballots; }

	/// Return whether the i-th candidate wins in the election
	bool is_winner(int i) { return winners[i]; }

protected:
	/**
		@brief Distribute all ballots to the corresponding candidates.
	*/
	virtual void DistributeBallots() = 0;

	/**
		@brief Resolve an n-way tie.

		@param n The number of participants involved in the tie.

		@return A random integer from `0` through `n-1` indicating who won the tie.
	*/
	int ResolveTie(int n=2);

	/**
		@brief Announce the results of the election.
	*/
	virtual void AnnounceResults() = 0;

	/**
		@brief Set up the logger for the election.

		@param output_dir The output directory where the audit file and media
		report will be created.
	*/
	virtual void SetUpLogger(std::string output_dir) = 0;

	/// The total number of candidates running in the election.
	int total_candidates;

	/// A vector of pointers to Candidate instances.
	std::vector<Candidate*> candidates;

	/// The total number of ballots casted in the election.
	int total_ballots;

	/// A vector of pointers to Ballot instances.
	std::vector<Ballot*> ballots;

	/**
		@brief A boolean vector indicating the winners of the election.

		A `true` value at an index indicates that the candidate at the
		corresponding index in the `candidates` array won.
	*/
	std::vector<bool> winners;

	/// The logger for the election.
	ElectionLogger* logger;
};

#endif
