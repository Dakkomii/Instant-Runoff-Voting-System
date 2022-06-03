/**
	@file election_logger_unittest.cc

	Unit test for the ElectionLogger class

	@author Brian Lu (luxx0463@umn.edu)
*/

#include <string>
#include "gtest/gtest.h"
#include "election_logger.h"

/// Test fixture for testing the ElectionLogger class.
class ElectionLoggerTest : public ::testing::Test {
public:
	/// Allocation of resources for test fixture.
	void SetUp() {
		l = new ElectionLogger("testing/");
	}

	/// Deallocation of resources for test fixture.
	void TearDown() {
		delete l;
	}

	/// A pointer to an ElectionLogger instance.
	ElectionLogger* l;
};

/// Test the functionality of ElectionLogger's WriteToAuditFile method.
TEST_F(ElectionLoggerTest, ElectionLoggerWriteToAuditFile) {
	l->WriteToAuditFile("ElectionLoggerWriteToAuditFile Unit Test");
	l->WriteToAuditFile("");
	l->WriteToAuditFile("\n\n\n\n\n\n\n\n");
	l->WriteToAuditFile("The following is an integer: " + std::to_string(9929) + "\n");
}

/// Test the functionality of ElectionLogger's WriteToMediaReport method.
TEST_F(ElectionLoggerTest, ElectionLoggerWriteToMediaReport) {
	l->WriteToMediaReport("ElectionLoggerWriteToMediaReport Unit Test");
	l->WriteToMediaReport("");
	l->WriteToMediaReport("\n\n\n\n\n\n\n\n");
	l->WriteToMediaReport("The following is an integer: " + std::to_string(9931) + "\n");
}
