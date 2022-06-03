/**
	@file election.cc

	Implementation of the methods for the Election class

	@author Brian Lu (luxx0463@umn.edu)
*/

#include <string>
#include <cstdlib>			// rand, srand
#include <ctime>				// time
#include "election.h"

int Election::ResolveTie(int n) {
	srand(time(nullptr));
	return rand() % n;
}
