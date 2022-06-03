/**
	@file oplelection_unittest.cc

	Unit test for the OPLElection class

	@author Luisa Jimenez Alarcon (jimen215@umn.edu)
*/

#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "oplelection.h"
#include "votingsystem.h"

/// Test fixture for testing the OPLElection class.
class OPLElectionTest : public ::testing::Test {
public:
	/// Allocation of resources for test fixture.
	void SetUp() {
		std::vector<std::vector<std::string>> data = VotingSystem::CsvToData("../testing/opl_testfile.csv");
		e = new OPLElection(data, "../testing/");
	}

	/// Deallocation of resources for test fixture.
	void TearDown() {
		delete e;
	}

	/// A pointer to an OPLElection instance.
	OPLElection* e;
};

/// Test the functionality of OPLElection's constructor.
TEST_F(OPLElectionTest, OPLElectionConstructor) {
	EXPECT_EQ(e->get_total_candidates(), 6);
	EXPECT_EQ(e->get_total_seats(), 3);
	EXPECT_EQ(e->get_total_ballots(), 9);
}

/// Test the functionality of OPLElection's DistributeBallots method.
TEST_F(OPLElectionTest, OPLElectionDistributeBallots) {

	e->DistributeBallots();
	//test candidates votes
	std::vector<int> actual_votes = {3, 2, 0, 2, 1, 1};
	std::vector<int> votes;
	for (int i = 0; i < e->get_total_candidates() ; i++){
		votes.push_back(e->get_candidate(i).get_total_votes());
	}

	for (int i = 0; i < e->get_total_candidates(); i++){
		EXPECT_EQ(votes.at(i), actual_votes.at(i));
	}

	//test party votes
	std::vector<int> actual_party_votes = {5, 3, 1};
	for (int i = 0; i < e->get_total_parties(); i++) {
		EXPECT_EQ(e->get_party(i).get_total_votes(), actual_party_votes[i]);
	}
}

/// Test the functionality of OPLElection's GetQuota method.
TEST_F(OPLElectionTest, OPLElectionQuota) {

	e->GetQuota();

	EXPECT_EQ(e->get_quota(), 3);
}

/// Test the functionality of OPLElection's AllocateSeats method.
 TEST_F(OPLElectionTest, OPLElectionAllocateSeats) {

 	e->DistributeBallots();
 	e->GetQuota();
 	e->AllocateSeats();

	std::vector<int> actual_seats = {2, 1, 0};

	for (int i = 0; i < e->get_total_parties(); i++) {
		EXPECT_EQ(e->get_party(i).get_total_seats() , actual_seats[i]);
	}

}

/// Test the functionality of OPLElection's SelectWinners method.
TEST_F(OPLElectionTest, OPLElectionSelectWinners) {

	e->DistributeBallots();
 	e->GetQuota();
 	e->AllocateSeats();
 	e->SelectWinners();

	EXPECT_EQ(e->is_winner(0), true);
	EXPECT_EQ(e->is_winner(1), true);
	EXPECT_EQ(e->is_winner(3), true);
}
