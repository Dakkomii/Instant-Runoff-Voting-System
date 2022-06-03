/**
	@file irelection.h
	
	Header file for the IRElection class
	
	@author Scott Deyo (deyo0005@umn.edu)
*/

#ifndef SRC_IRELECTION_H_
#define SRC_IRELECTION_H_

#include <string>
#include <vector>

#include "election.h"

/**
	@brief Class that represents an election using Instant Runoff voting.
	
	IRElection sets up an election and runs the Instant Runoff voting
	algorithm in order to determine which candidate wins.
*/
class IRElection : public Election {
public:
		/**
				@brief IRElection's constructor.
				@param data The parsed data from the ballot file.
				@param output_dir The output directory for the audit file and media report.
				Defaults to the top level of the project directory.
		*/
		IRElection(std::vector<std::vector<std::string>> data, std::string output_dir="");

		/**
      	@brief IRElection's destructor.
    */
    ~IRElection();

		void Run() override;

private:
		/**
				@brief initial distribution of ballots
		*/
		void DistributeBallots() override;

		/**
				@brief Redistribute a losing candidate's ballots.
				@param c The index of the candidate whose ballots are to
				be redistributed.
		*/
		void RedistributeBallots(int c);

		/**
				@brief find candidate with lowest number of votes -- the 'loser'
				and call RedistributeVotes with the loser's votes
		*/
		void EliminateCandidate();

		/**
				@brief announce winner to terminal, output media and audit files
		*/
		void AnnounceResults() override;

		/**
				@brief Set up the logger for the election.
				@param output_dir The output directory where the audit file and media
				report will be created.
		*/
		void SetUpLogger(std::string output_dir) override;

	  /// Boolean array of whether a candidate is eliminated (0) or not (1).
	  std::vector<bool> candidate_eliminated;

		/// The number of votes needed to have a majority.
		int majority;
};

#endif
