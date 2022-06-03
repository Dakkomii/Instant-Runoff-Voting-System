/**
	@file oplelection.h

	Header file for the OPLElection class

	@author Luisa Jimenez Alarcon (jimen215@umn.edu)
*/

#ifndef SRC_OPLELECTION_H
#define SRC_OPLELECTION_H

#include <string>
#include <vector>
#include "election.h"
#include "party.h"

/**
	@brief Class that represents an election using Open Party List voting.

	OPLElection sets up an election and runs the Open Party List voting
  algorithm in order to determine which candidates win a seat.
*/
class OPLElection : public Election{

public:
    /**
        @brief OPLElection's constructor.

        @param data The parsed data from the ballot file.

        @param output_dir The output directory for the audit file and media report.
        Defaults to the top level of the project directory.
    */
    OPLElection(std::vector<std::vector<std::string>> data, std::string output_dir="");

    /**
        @brief OPLElection's destructor.
    */
    ~OPLElection();

    /**
        @brief Runs the OPL election.
    */
    void Run() override;

    /**
		@brief Return the total number of seats.
    */
    int get_total_seats() { return total_seats; }

    /**
		@brief Return quota.
    */
    int get_quota(){return quota;}

    /**
		@brief Return the total number of parties in the election.
    */
    int get_total_parties(){ return total_parties; }

    /**
		@brief Return the i-th party (0-indexed) in the election.
    */
    Party get_party(int i) { return *parties[i]; }

    void DistributeBallots() override;

    /**
        @brief Computes the quota and stores it in the quota variable.
	  */
    void GetQuota();

    /**
        @brief Allocates number of seats each party gets
    */
    void AllocateSeats();

    /**
        @brief Select winners per party depending on the votes and the number of seats available.
        when the winner is chosen the winner array value at index corresponding to the candidate is
        changed to true.
	  */
    void SelectWinners();


private:

	/**
	@brief Announce winner in terminal along with a summary of the election data.
    */
    void AnnounceResults() override;



    /**
  		@brief Set up the logger for the election.

  		@param output_dir The output directory where the audit file and media
  		report will be created.
  	*/
    void SetUpLogger(std::string output_dir) override;




    /// The total number of seats.
    int total_seats;

    /// The total number of parties.
    int total_parties{0};

    /// The parties in the election.
    std::vector<Party*> parties;

    /// The quota to win a seat.
    int quota;
};

#endif //SRC_OPLELECTION_H
