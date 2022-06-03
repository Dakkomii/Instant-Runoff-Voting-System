/**
	@file candidate_unittest.cc

	Unit test for the Candidate class

	@author Brian Lu (luxx0463@umn.edu)
*/

#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "candidate.h"

/// Test fixture for testing the Candidate class.
class CandidateTest : public ::testing::Test {
public:
	/// Allocation of resources for test fixture.
	void SetUp() {
		candidates.push_back(new Candidate("Rosen", "D"));
		candidates.push_back(new Candidate("kleinberg", "r"));
		candidates.push_back(new Candidate("Chou Chou Chou Chou Chou Chou Chou", "I I I I I I I I I I I I I I I I I"));
		candidates.push_back(new Candidate("", ""));
	}

	/// Deallocation of resources for test fixture.
	void TearDown() {
		for (auto cand : candidates) {
			delete cand;
		}
	}

	/// A vector of pointers to Candidate instances.
	std::vector<Candidate*> candidates;
};

/// Test the functionality of Candidate's constructor.
TEST_F(CandidateTest, CandidateConstructor) {
	EXPECT_EQ(candidates[0]->get_name(), "Rosen");
	EXPECT_EQ(candidates[0]->get_party(), "D");
	EXPECT_EQ(candidates[1]->get_name(), "kleinberg");
	EXPECT_EQ(candidates[1]->get_party(), "r");
	EXPECT_EQ(candidates[2]->get_name(), "Chou Chou Chou Chou Chou Chou Chou");
	EXPECT_EQ(candidates[2]->get_party(), "I I I I I I I I I I I I I I I I I");
	EXPECT_EQ(candidates[3]->get_name(), "");
	EXPECT_EQ(candidates[3]->get_party(), "");
}

/// Test the functionality of Candidate's AddBallotId and RemoveVotes.
TEST_F(CandidateTest, CandidateVotes) {
	int n = 5;

	for (int i=0; i<n; i++) {
		EXPECT_EQ(candidates[0]->get_total_votes(), i);
		candidates[0]->AddBallotId(i);
	}
	EXPECT_EQ(candidates[0]->get_total_votes(), n);

	std::vector<int> votes = candidates[0]->RemoveVotes();
	EXPECT_EQ(candidates[0]->get_total_votes(), 0);

	for (int i=0; i<n; i++) {
		EXPECT_EQ(votes[i], i);
	}
}
