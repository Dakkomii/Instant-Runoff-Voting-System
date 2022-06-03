/**
	@file irelection_unittest.cc

	Unit test for the IRElection class

	@author Scott Deyo (deyo0005@umn.edu)
*/

#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "irelection.h"
#include "votingsystem.h"

/// Test fixture for testing the IRElection class.
class IRElectionTest : public ::testing::Test {
public:
	/// Allocation of resources for test fixture.
	void SetUp() {
		std::vector<std::vector<std::string>> data = VotingSystem::CsvToData("../testing/ir_testfile.csv");
		e = new IRElection(data, "../testing/");
    e->Run();
	}

	/// Deallocation of resources for test fixture.
	void TearDown() {
		delete e;
	}

	/// A pointer to an IRElection instance.
	IRElection* e;
};

/// Test the functionality of IRElection's constructor.
TEST_F(IRElectionTest, IRElectionConstructor) {
	EXPECT_EQ(e->get_total_candidates(), 4);
	EXPECT_EQ(e->get_total_ballots(), 6);
}
/**
/// Test the functionality of IRElection's DistributeBallots method.
TEST_F(IRElectionTest, IRElectionDistributeBallots) {
  //test candidates votes
  std::vector<int> actual_votes = {3, 2, 0, 2, 1, 1};
  std::vector<int> votes;
  for (int i = 0; i < e->get_total_candidates() ; i++){
    votes.push_back(e->get_candidate(i).get_total_votes());
  }

  for (int i = 0; i < e->get_total_candidates(); i++){
    EXPECT_EQ(votes.at(i), actual_votes.at(i));
  }
}

/// Test the correctness of IRElection's winners.
TEST_F(IRElectionTest, IRElectionWinner) {

	EXPECT_TRUE(e->is_winner(0));
	EXPECT_TRUE(e->is_winner(1));
	EXPECT_TRUE(e->is_winner(3));
}**/
