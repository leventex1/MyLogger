#pragma once
#include "logger.h"
#include <string>
#include <sstream>
#include <fstream>


using namespace mylog;

bool testOutputStream() {
	std::stringstream testStream;
	Logger::getInstance().setOutputStream(&testStream);

	std::string testString = "Test String";
	Logger::getInstance().log(testString);

	Logger::getInstance().setOutputStream(nullptr);
	return testStream.str() == testString+"\n";
}

bool testFileStreamWrite() {
	std::string fileName = "logtest.txt";
	std::string logText = "Hello Test!";
	Logger::getInstance().setLogFile(fileName);
	Logger::getInstance().log(logText);

	std::stringstream buffer;

	std::ifstream testInputFile(fileName);
	buffer << testInputFile.rdbuf();
	testInputFile.close();

	std::ofstream testOutputFile(fileName);
	testOutputFile.flush();
	testOutputFile.close();

	Logger::getInstance().setLogFile("");

	return buffer.str() == logText+"\n";
}