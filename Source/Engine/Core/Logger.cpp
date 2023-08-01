#include "Logger.h"

#include <iostream>

#include "FileIO.h"

namespace ane {
	Logger globalLogger(LogLevel::INFO, &std::cout);

	bool Logger::Log(LogLevel logLevel, const std::string& fileName, int line) {
		if(logLevel < this->logLevel) {
			return false;
		}

		switch(logLevel) {
			case LogLevel::INFO:
				*(this->ostream) << "INFO: ";
				break;
			case LogLevel::WARNING:
				*(this->ostream) << "WARNING: ";
				break;
			case LogLevel::ERROR:
				*(this->ostream) << "ERROR: ";
				break;
			case LogLevel::ASSERT:
				*(this->ostream) << "ASSERT: ";
				break;
			default:
				break;
		}

		*(this->ostream) << getFileName(fileName) << "(" << line << ")\n";

		return true;
	}
}