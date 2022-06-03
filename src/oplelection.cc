/**
	@file oplelection.cc

	Implementation of the methods for the OPLElection class

	@author Luisa Jimenez Alarcon (jimen215@umn.edu)
*/

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "oplelection.h"

OPLElection::OPLElection(std::vector<std::vector<std::string>> data, std::string output_dir) {
    // Number of candidates, seats and ballots
    total_candidates = std::stoi(data[1][0]);
    total_seats = std::stoi(data[3][0]);
    total_ballots = std::stoi(data[4][0]);

    // Initialize winners vector to false
    winners = std::vector<bool>(total_candidates, false);

    // Convert candidate strings to Candidate instances
    for (int i=0; i<total_candidates; i++) {
        // Store candidate's name and party in temp variables
        std::string cand_name = data[2][2*i];
        std::string cand_party = data[2][2*i+1];

        // Search parties vector for whether candidate's party is already accounted for in the election
        auto it = std::find_if(parties.begin(), parties.end(), [cand_party](Party* p){ return p->get_name() == cand_party; });
        Party* party;
        if (it == parties.end()) {
            // If not, create a party under that name and set party to that party name
            parties.push_back(new Party(cand_party));
            total_parties++;
            party = parties.back();
        } else {
            // If so, set party to that party name
            party = *it;
        }

        candidates.push_back(new Candidate(cand_name, cand_party)); // Add candidate to candidates vector
        party->AddCandidateIndex(i); // Add candidate index to party
    }

    // Convert ballot strings to Ballot instances
    for (int i=0; i<total_ballots; i++) {
        ballots.push_back(new Ballot(data[i+5], i));
    }

    // Set up the election logger
    SetUpLogger(output_dir);
}

OPLElection::~OPLElection() {
    for (auto c : candidates) delete c;
    for (auto b : ballots) delete b;
    for (auto p : parties) delete p;
    delete logger;
}

void OPLElection::Run(){

    DistributeBallots();
    GetQuota();
    AllocateSeats();
    SelectWinners();
    AnnounceResults();
}

void OPLElection::DistributeBallots(){

	logger->WriteToAuditFile("\nDistributing ballots:\n");
	
    //loop through each ballot
    for (int i = 0; i < total_ballots; i++) {
        //get the index for the chosen candidate from ballot
        int ind = ballots.at(i)->GetChoice();
        
        logger->WriteToAuditFile("\nBallot " + std::to_string(ballots.at(i)->get_id()) + " added to candidate " + candidates.at(ind)->get_name() + "\n" );
        
        //use ind to add a vote to the candidate at index ind
        candidates.at(ind)->AddBallotId(ballots.at(i)->get_id());
        //loop through the party to add a vote to the candidate's party
        for (int k = 0; k < total_parties; k++){
            //compare candidate party to the party name at parties vector
            //if they are equal then increment votes to the party
            if(candidates.at(ind)->get_party() == parties.at(k)->get_name()){
                parties.at(k)->AddVote();
                logger->WriteToAuditFile("\nAdding a vote to party: " + parties.at(k)->get_name() + "\n");
            }
        }

    }

}

void OPLElection::GetQuota(){
	logger->WriteToAuditFile("\nComputing quota\n");
	
    quota = total_ballots / total_seats;
    logger->WriteToAuditFile("Quota: " + std::to_string(get_quota()) + "\n");
}

void OPLElection::AllocateSeats(){
	logger->WriteToAuditFile("\nAllocating seats\n");
    //temp variable to count how many seats have been allocated so far
    int allocated_seats = 0;

    // integer vector for remainders
    std::vector<int> remainders;

    //this for loop go through the total votes that parties have
    //and calculate the number of seats depending on the quota
    for (int i = 0; i < total_parties; i++){
        ///divide votes from the party by quota and downcasting it to int
        //to get a whole number of seats that must be allocated to the party

        int seats = (int) (parties[i]->get_total_votes() / quota);
        	logger->WriteToAuditFile( parties[i]->get_name() + ": " + std::to_string(parties[i]->get_total_votes())+" divided by "+ std::to_string(quota) + "\n");
        //store the remainder a party got in an array for second allocation in case not all seats were allocated
        int remainder = parties[i]->get_total_votes() % quota;
        // then store the seats in the seats array index that correspond to the party index
        //first checks if there are enough condidates for the seats
        if(seats <= parties[i]->get_total_candidates()){
            //set seats
            parties[i]->set_total_seats(seats);
            logger->WriteToAuditFile(parties[i]->get_name() + " got " + std::to_string(parties[i]->get_total_seats()) + "\n");
            //update temp variable of allocated seats
            allocated_seats += seats;
        }
        else if(seats > parties[i]->get_total_candidates()){
            //if there are not enought candidated for the seats just allocate seats as there are candidates
            int tempseats = 0;
            for (int j = 0; j < parties[i]->get_total_candidates(); j++){
                tempseats++;
            }
            parties[i]->set_total_seats(tempseats);
            logger->WriteToAuditFile(parties[i]->get_name() + " got " + std::to_string(parties[i]->get_total_seats()) + "\n");
            allocated_seats += tempseats;
            remainder = 0;
        }
        logger->WriteToAuditFile("Adding remainder of: " + std::to_string(remainder) + " to a remainder array\n");
        remainders.push_back(remainder);
    }

    int temp_total_seats = 0 ;
    for (int i = 0; i < total_parties; i++)
    {
        temp_total_seats += parties[i]->get_total_seats();
    }
    //if all the seats were not allocated during first iteration then
    //while not all seats have been allocated:
    while (allocated_seats <= total_seats ) {
        // Vector of next parties to be allocated a seat
        std::vector<int> next_allocation;
        // Search for the party/parties with the greatest remainder by pushing it/them onto next_allocation
        for (int i=0; i < total_parties; i++) {
            int max = 0;
            if (remainders[i] > max) {
                max = remainders[i];
                next_allocation.clear();
                next_allocation.push_back(i);
            } else if (remainders[i] == max) {
                next_allocation.push_back(i);
            }
        }

        // The number of parties to be allocated a seat next
        int n = (int) next_allocation.size();
        // rn is from 0 thru n-1, resolving an n-way tie; trivial in case n=1, in which rn=0
        int rn = ResolveTie(n);
        // Distribute seat to the winning party
        parties[rn]->set_total_seats( parties[rn]->get_total_seats()+1 );
        // Adjust winning party's remainder accordingly
        remainders[rn] -= quota;
        // Increment number of allocated seats
        allocated_seats++;
    }
}

void OPLElection::SelectWinners(){
    //loop through parties array to choose winners from a party
    for (int p = 0; p < total_parties; p++) {
        // Continue if no seats
        if (parties[p]->get_total_seats() == 0) {
            continue;
        }
        if(parties[p]->get_total_candidates() == parties[p]->get_total_seats()){
            for(int k = 0; k< parties[p]->get_total_candidates(); k++){
                winners[k] = true;
            }
            continue;
        }
        // Form vector of candidate indices from a single party
        std::vector<int> cands_in_party;
        for (int j=0; j < parties[p]->get_total_candidates(); j++) {
            int cand_idx = parties[p]->get_candidate_index(j);
            cands_in_party.push_back(cand_idx);
        }

        // Sort the cands_in_party vector in descending order
        for (int j=1; j < (int) cands_in_party.size(); j++) {
            int key = cands_in_party[j];
            int i = j-1;
            while ( i>=0 && candidates[cands_in_party[i]]->get_total_votes() < candidates[key]->get_total_votes() ) {
                cands_in_party[i+1] =  cands_in_party[i];
                i--;
            }
            cands_in_party[i+1] = key;
        }
        // Choose the first however-many candidates as winners
        for (int j=0; j < parties[p]->get_total_seats(); j++) {
            int ind = cands_in_party[j]; // Hold index of winning candidate
            int next = cands_in_party[j+1];
            // winners[ind] = true;
            if(candidates[ind]->get_total_votes() == candidates[next]->get_total_votes()){
            logger->WriteToAuditFile("There is a tie between: " + candidates[ind]->get_name() + " and " + candidates[next]->get_name()+ "\n");
                int n = ResolveTie();
                if(n == 1)
                    continue;
                else
                    ind = cands_in_party[next];

            }
            else if(candidates.at(j)->get_total_votes() == candidates.at(j+1)->get_total_votes() &&
                    candidates.at(j)->get_total_votes() == candidates.at(j+2)->get_total_votes()){
     logger->WriteToAuditFile("There is a tie between: " + candidates[ind]->get_name() + ", " + candidates[next + 1]->get_name() + " and " + candidates[ind]->get_name()+ "\n");
                        int n = ResolveTie(3);
                        if(n == 1)
                            continue;
                        else if(n == 2)
                            ind = cands_in_party[next];
                        else
                            ind = cands_in_party[next + 1];

                    }
            winners[ind] = true;
            logger->WriteToAuditFile(candidates.at(ind)->get_name() + " has won!\n");
        }

    }
}

void OPLElection::AnnounceResults(){
    // ASCII art generated at https://patorjk.com/software/taag
    // Ivrit font with default settings
    std::string results;
    results += R"(
   ___  ____  _       _____ _           _   _               ____                 _ _
  / _ \|  _ \| |     | ____| | ___  ___| |_(_) ___  _ __   |  _ \ ___  ___ _   _| | |_ ___
 | | | | |_) | |     |  _| | |/ _ \/ __| __| |/ _ \| '_ \  | |_) / _ \/ __| | | | | __/ __|
 | |_| |  __/| |___  | |___| |  __/ (__| |_| | (_) | | | | |  _ <  __/\__ \ |_| | | |_\__ \
  \___/|_|   |_____| |_____|_|\___|\___|\__|_|\___/|_| |_| |_| \_\___||___/\__,_|_|\__|___/)";

    results += "\n\n\nElection type: OPL\n";
    results += "Number of candidates: " + std::to_string(total_candidates) + "\n";
    results += "Total number of seats distributed: " + std::to_string(total_seats) + "\n";
    results += "Total number of votes: " + std::to_string(total_seats) + "\n";

    results += "\n-----Winners-----\n";
    for (int i = 0; i < total_candidates ; i++){
				if(winners[i] == true){
						Candidate* cand = candidates[i];
						results += "***\n";
						results += "Candidate name: " + cand->get_name() + "\n";
						results += "Candidate party: " + cand->get_party() + "\n";
						results += "Candidate votes: " + std::to_string(cand->get_total_votes()) + " ";
						results += "("+ std::to_string((double) cand->get_total_votes() / (double) total_ballots * 100.0) + "%)\n";
						results += "***\n";
				}
    }

    results += "\nTotal votes in the election: " + std::to_string(total_ballots) + "\n";

    results += "\n-----All candidates information-----\n";
    for (int i = 0; i < total_candidates ; i++){
        results += "***\n";
        results += "Candidate name: " + candidates[i]->get_name() + "\n";
        results += "Candidate party: " + candidates[i]->get_party() + "\n";
        results += "Candidate votes: " + std::to_string(candidates[i]->get_total_votes()) + "\n";
        results += "***\n";
    }

    // write the string to the audit file
		logger->WriteToAuditFile(results);
    // write the string to the media report
    logger->WriteToMediaReport(results);
    // output string to screen
    std::cout << results;
}

void OPLElection::SetUpLogger(std::string output_dir) {
  std::string audit_header;
  audit_header += "\n========== Voting System Audit Results ==========\n\n";
  audit_header += "Election Type: OPL\n";
  audit_header += "Number of Candidates: " + std::to_string(total_candidates) + "\n";
  audit_header += "Candidates: ";
  for (int i=0; i < total_candidates; i++) {
      audit_header += candidates[i]->get_name() + " (" + candidates[i]->get_party();
      if (i == total_candidates-1) {
          audit_header += ")\n";
      } else {
          audit_header += "), ";
      }
  }
  audit_header += "Number of Seats: " + std::to_string(total_seats) + "\n";
  audit_header += "Number of Ballots: " + std::to_string(total_ballots) + "\n\n";

  logger = new ElectionLogger(output_dir);
  logger->WriteToAuditFile(audit_header);
}
