/**
	@file ballot_unittest.cc

	Unit test for the Ballot class

	@author Brian Lu (luxx0463@umn.edu)
*/

#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "ballot.h"

/// Test fixture for testing the Ballot class.
class BallotTest : public ::testing::Test {
public:
	/// Allocation of resources for test fixture.
	void SetUp() {
		std::vector<std::string> bstr1{"1","3","4","2"};
		std::vector<std::string> bstr2{"1","","2",""};
		std::vector<std::string> bstr3{"1","2","3",""};
		std::vector<std::string> bstr4{"","","","1"};

		ballots.push_back(new Ballot(bstr1, 0));
		ballots.push_back(new Ballot(bstr2, 1));
		ballots.push_back(new Ballot(bstr3, 2));
		ballots.push_back(new Ballot(bstr4, -1));
	}

	/// Deallocation of resources for test fixture.
	void TearDown() {
		for (auto b : ballots) {
			delete b;
		}
	}

	/// A vector of pointers to Ballot instances.
	std::vector<Ballot*> ballots;
};

/// Test the functionality of Ballot's constructor.
TEST_F(BallotTest, BallotConstructor) {
	for (int i = 0; i < (int) ballots.size() - 1; i++) {
		EXPECT_EQ(ballots[i]->get_id(), i);
	}
	EXPECT_EQ(ballots[3]->get_id(), -1);
}

/// Test the functionality of Ballot's GetChoice and IncrementRank methods.
TEST_F(BallotTest, BallotGetChoice) {
	EXPECT_EQ(ballots[0]->GetChoice(), 0);
	EXPECT_EQ(ballots[1]->GetChoice(), 0);
	EXPECT_EQ(ballots[2]->GetChoice(), 0);
	EXPECT_EQ(ballots[3]->GetChoice(), 3);

	for (int i = 0; i < (int) ballots.size(); i++) {
		ballots[i]->IncrementRank();
	}

	EXPECT_EQ(ballots[0]->GetChoice(), 3);
	EXPECT_EQ(ballots[1]->GetChoice(), 2);
	EXPECT_EQ(ballots[2]->GetChoice(), 1);
	EXPECT_EQ(ballots[3]->GetChoice(), -1);

	for (int i = 0; i < (int) ballots.size(); i++) {
		ballots[i]->IncrementRank();
	}

	EXPECT_EQ(ballots[0]->GetChoice(), 1);
	EXPECT_EQ(ballots[1]->GetChoice(), -1);
	EXPECT_EQ(ballots[2]->GetChoice(), 2);
	EXPECT_EQ(ballots[3]->GetChoice(), -1);

	for (int i = 0; i < (int) ballots.size(); i++) {
		ballots[i]->IncrementRank();
	}

	EXPECT_EQ(ballots[0]->GetChoice(), 2);
	EXPECT_EQ(ballots[1]->GetChoice(), -1);
	EXPECT_EQ(ballots[2]->GetChoice(), -1);
	EXPECT_EQ(ballots[3]->GetChoice(), -1);

	for (int i = 0; i < (int) ballots.size(); i++) {
		ballots[i]->IncrementRank();
	}

	EXPECT_EQ(ballots[0]->GetChoice(), -1);
	EXPECT_EQ(ballots[1]->GetChoice(), -1);
	EXPECT_EQ(ballots[2]->GetChoice(), -1);
	EXPECT_EQ(ballots[3]->GetChoice(), -1);
}
