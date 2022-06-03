/**
	@file election_logger.h

	Header file for the ElectionLogger class

	@author Brian Lu (luxx0463@umn.edu)
*/

#ifndef SRC_ELECTION_LOGGER_H
#define SRC_ELECTION_LOGGER_H

#include <string>
#include <vector>
#include <fstream>

/**
	@brief Class that handles files for an Election.

	This class manages and writes to the audit file and media report for
	an Election.
*/
class ElectionLogger {
public:
	/**
		@brief ElectionLogger's constructor.

		@param output_dir The output directory where the audit file and media
		report will be created.

		Create the audit file and media report under unique filenames,
		and open them.
	*/
	ElectionLogger(std::string output_dir="");

	/**
		@brief ElectionLogger's destructor.

		Close the audit file and media report.
	*/
	~ElectionLogger();

	/**
		@brief Write content to the audit file.

		@param content Content to be written to the audit file.
	*/
	void WriteToAuditFile(std::string content) { audit_file << content; }

	/**
		@brief Write content to the media report.

		@param content Content to be written to the media report.
	*/
	void WriteToMediaReport(std::string content) { media_report << content; }

private:
	/**
		@brief Get the current time.

		@return The current time as a string.

		The current time is returned in the format
		`yyyy-MM-dd HH:mm:ss.ssssss`.

		- `yyyy`: year
		- `MM`: 2-digit month
		- `dd`: 2-digit day
		- `HH`: hours, in 24-hour format
		- `mm`: minutes
		- `ss.ssssss`: seconds, with precision to microseconds
	*/
	std::string GetCurrentTime();

	/// The file stream for the audit file.
	std::ofstream audit_file;

	/// The file stream for the media report.
	std::ofstream media_report;
};

#endif
