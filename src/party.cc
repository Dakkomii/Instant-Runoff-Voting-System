/**
	@file party.cc

	Implementation of the methods for the Party class

	@author Brian Lu (luxx0463@umn.edu)
*/

#include <string>
#include <vector>
#include "party.h"

void Party::AddCandidateIndex(int cand_idx) {
	candidate_indices.push_back(cand_idx);
	total_candidates++;
}
