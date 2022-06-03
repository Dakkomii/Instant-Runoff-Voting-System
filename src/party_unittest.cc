/**
	@file party_unittest.cc

	Unit test for the Party class

	@author Brian Lu (luxx0463@umn.edu)
*/

#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "party.h"

/// Test fixture for testing the Party class.
class PartyTest : public ::testing::Test {
public:
	/// Allocation of resources for test fixture.
	void SetUp() {
		parties.push_back(new Party("D"));
		parties.push_back(new Party("r"));
		parties.push_back(new Party("I I I I I I I I I I I I I I I I I"));
		parties.push_back(new Party(""));
	}

	/// Deallocation of resources for test fixture.
	void TearDown() {
		for (auto par : parties) {
			delete par;
		}
	}

	/// A vector of pointers to Party instances.
	std::vector<Party*> parties;
};

/// Test the functionality of Party's constructor.
TEST_F(PartyTest, PartyConstructor) {
	EXPECT_EQ(parties[0]->get_name(), "D");
	EXPECT_EQ(parties[1]->get_name(), "r");
	EXPECT_EQ(parties[2]->get_name(), "I I I I I I I I I I I I I I I I I");
	EXPECT_EQ(parties[3]->get_name(), "");
}

/// Test the functionality of Party's AddCandidateIndex method.
TEST_F(PartyTest, PartyAddCandidateIndex) {
	std::vector<int> cand_indices = {2, 3, 5, 7};
	int n = cand_indices.size();

	for (int i=0; i < n; i++) {
		EXPECT_EQ(parties[0]->get_total_candidates(), i);
		parties[0]->AddCandidateIndex(cand_indices[i]);
	}
	EXPECT_EQ(parties[0]->get_total_candidates(), n);

	for (int i=0; i < n; i++) {
		EXPECT_EQ(parties[0]->get_candidate_index(i), cand_indices[i]);
	}
}

/// Test the functionality of Party's AddVote method.
TEST_F(PartyTest, PartyAddVote) {
	int n = 7;

	for (int i=0; i < n; i++) {
		EXPECT_EQ(parties[0]->get_total_votes(), i);
		parties[0]->AddVote();
	}
	EXPECT_EQ(parties[0]->get_total_votes(), n);
}
