/**
	@file irelection.cc
	Implementation of the methods for the IRElection class
	@author Scott Deyo (deyo0005@umn.edu)
*/

#include <string>
#include <vector>
#include <iostream>
#include "irelection.h"

IRElection::IRElection(std::vector<std::vector<std::string>> data, std::string output_dir) {
    // Number of candidates and ballots
    total_candidates = std::stoi(data[1][0]);
    total_ballots = std::stoi(data[3][0]);

    // Initialize value for clear majority win
    majority = total_ballots / 2;         // greater-than operator will supply +1 for true majority

    // Initialize winners vector to false
    winners = std::vector<bool>(total_candidates, false);

    // Initialize candidate_eliminated vector to false
    candidate_eliminated = std::vector<bool>(total_candidates, false);

    // Convert candidate strings to Candidate instances
    for (int i=0; i<total_candidates; i++) {
        candidates.push_back(new Candidate(data[2][2*i], data[2][2*i+1]));
    }

    // Convert ballot strings to Ballot instances
    for (int i=0; i<total_ballots; i++) {
        ballots.push_back(new Ballot(data[i+4], i));
    }

    // Set up the election logger
    SetUpLogger(output_dir);
}

IRElection::~IRElection() {
    for (auto c : candidates) delete c;
    for (auto b : ballots) delete b;
    delete logger;
}

void IRElection::Run(){

		// can't have zero votes!
		if (total_ballots < 1) {
		  std::cout << "Invalid Election -- < 1 vote!\n";
		  exit(EXIT_FAILURE);
		}
		// can't have zero candidates!
		if (total_ballots < 1) {
		  std::cout << "Invalid Election -- < 1 candidate!\n";
		  exit(EXIT_FAILURE);
		}

    DistributeBallots();

		// keep track of how many candidates are still in the running --
		// for edge case where there is no clear majority
		int candidates_in_running = total_candidates;

		// break out of while loop when there is a winner
		bool win_flag = false;

		while(win_flag == false) {
				// edge case where there is no clear majority
				if (candidates_in_running == 1) {
						for (int i=0; i < total_candidates; i++) {
								if (candidate_eliminated[i] == false)
								{
										winners[i] = true;
										win_flag = true;
										AnnounceResults();
										break;
								}
						}
				}
				// 2 or more candidates, so eliminate one with lowest number of votes and redistribute them
		    else {
						for (int i=0; i < total_candidates; i++) {
			        // check for a clear winner
			        if (candidates[i]->get_total_votes() > majority) {
			            winners[i] = true;
									win_flag = true;
			            logger->WriteToAuditFile("\nWinner declared with clear majority:\n");
			            logger->WriteToAuditFile("Candidate " + std::to_string(i) + " with " + std::to_string(candidates[i]->get_total_votes()) + " votes.\n");
			            AnnounceResults();
			            break;
			        }
						}
					EliminateCandidate();
					candidates_in_running--;
				}
		}
}

void IRElection::DistributeBallots(){
    logger->WriteToAuditFile("\nInitial Ballot Distribution:\n");
    for (int i=0; i < total_ballots; i++) {
				int choice = ballots[i]->GetChoice();
  			candidates[choice]->AddBallotId(ballots[i]->get_id());
	      logger->WriteToAuditFile("Ballot " + std::to_string(i) + " to Candidate " + std::to_string(choice) + "\n");
    }
}

void IRElection::RedistributeBallots(int c) {
	  logger->WriteToAuditFile("\nBallot Redistribution:\n");

		// store some temp variables about ballots to be removed from one candidate and redistributed
		int number_of_ballots = candidates[c]->get_total_votes();
		std::vector<int> ballots_to_redistribute = candidates[c]->RemoveVotes();

		for (int i = 0; i < number_of_ballots; i++) {
					int j = ballots_to_redistribute[i];
					ballots[j]->IncrementRank();
					int new_choice = ballots[j]->GetChoice();
					// if there is a valid incremented choice filled out on ballot
					if (new_choice > 0) {
							candidates[new_choice]->AddBallotId(ballots[j]->get_id());
							logger->WriteToAuditFile("Ballot " + std::to_string(j) + " to Candidate " + std::to_string(new_choice) + "\n");
					}
					else {
							logger->WriteToAuditFile("Ballot " + std::to_string(j) + " has no more valid ranks and is now unassigned.\n");
					}
			}
}

void IRElection::EliminateCandidate() {
    int temp_cand;
    int tie_winner;
    int temp_votes = total_ballots;
    bool tie_flag = false;

    for (int i=0; i < total_candidates; i++) {
        // make sure the candidate is still valid
        if (candidate_eliminated[i] == false) {
            if (candidates[i]->get_total_votes() < temp_votes) {
                // keeping track of lowest number of votes in each pass through 'for' loop
                temp_votes = candidates[i]->get_total_votes();
                // keeping track of candidate with lowest number of votes in each pass through 'for' loop
                temp_cand = i;
                // if there is a new low count, lower than an earlier coin toss result
                tie_flag = false;
            }
            // if vote total is the same, then the tie is resolved
            else if (candidates[i]->get_total_votes() == temp_votes) {
                tie_flag = true;
                if (ResolveTie(2) == 1) {
                    tie_winner = temp_cand;
                    // resolves into new candidate being loser
                    temp_cand = i;
                }
                // new candidate wins coin toss (not eliminated)
                // temp_cand stays the same as it was before coin toss
                else  {tie_winner = i;}
            }
        }
    }
    if (tie_flag == true) {
        logger->WriteToAuditFile("\nLowest count tie resolved with coin toss.\n");
        logger->WriteToAuditFile("Candidate " + std::to_string(tie_winner) + " not eliminated.\n");
    }
    logger->WriteToAuditFile("\nCandidate " + std::to_string(temp_cand) + " eliminated.\n");
    // put candidate in 'eliminated' boolean array
    candidate_eliminated[temp_cand] = true;
    // redistribute loser's ballots
    RedistributeBallots(temp_cand);
}


void IRElection::AnnounceResults(){

  // 'results' string will hold entire message used for outputting to screen and also to audit report
  std::string results;
  // ASCII art generated at https://patorjk.com/software/taag
  // Ivrit font with default settings
  results += R"(
  ___ ____    _____ _           _   _               ____                 _ _
 |_ _|  _ \  | ____| | ___  ___| |_(_) ___  _ __   |  _ \ ___  ___ _   _| | |_ ___
  | || |_) | |  _| | |/ _ \/ __| __| |/ _ \| '_ \  | |_) / _ \/ __| | | | | __/ __|
  | ||  _ <  | |___| |  __/ (__| |_| | (_) | | | | |  _ <  __/\__ \ |_| | | |_\__ \
 |___|_| \_\ |_____|_|\___|\___|\__|_|\___/|_| |_| |_| \_\___||___/\__,_|_|\__|___/)";

    results += "\n\n\nElection type: IR\n";
    results += "Number of candidates: " + std::to_string(total_candidates) + "\n";

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

void IRElection::SetUpLogger(std::string output_dir) {
    // 'audit_header' will hold header for audit file
    std::string audit_header;
    audit_header += "\n========== Voting System Audit Results ==========\n\n";
    audit_header += "Election Type: IR\n";
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
    audit_header += "Number of Ballots: " + std::to_string(total_ballots) + "\n\n";

    // 'logger' is instance of ElectionLogger that we will need to update as election runs
    logger = new ElectionLogger(output_dir);
    // write header to audit file
    logger->WriteToAuditFile(audit_header);
}
