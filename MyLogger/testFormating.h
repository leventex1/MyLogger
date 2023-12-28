#pragma once
#include "logger.h"
#include <string>
#include <sstream>


using namespace mylog;

bool testFormating() {
	std::stringstream testStream;
	std::string testFormat = "&t  {}";
	std::string testString = "Hello Test!";

	//std::string dateTime = std::format("{:%d/%m/%Y %H:%M:%OS}", std::chrono::system_clock::now());
	std::string dateTime = "";

	std::string resultString = " " + dateTime + " " + testString;
	std::string logString = "- " + dateTime + " " + testString;
	std::string infoString = "INFO" + resultString;
	std::string warningString = "WARNING" + resultString;
	std::string errorString = "ERROR" + resultString;

	Logger::getInstance().setInfoFormat(testFormat);
	Logger::getInstance().setWarningFormat(testFormat);
	Logger::getInstance().setErrorFormat(testFormat);
	Logger::getInstance().setOutputStream(&testStream);


	bool result = true;

	info(testString);
	result &= testStream.str() == infoString + "\n";
	testStream.str(std::string());

	warning(testString);
	result &= testStream.str() == warningString + "\n";
	testStream.str(std::string());

	error(testString);
	result &= testStream.str() == errorString + "\n";
	testStream.str(std::string());

	log("&t  " + testString);
	result &= testStream.str() == logString + "\n";
	testStream.str(std::string());


	Logger::getInstance().setOutputStream(nullptr);
	Logger::getInstance().setInfoFormat("");
	Logger::getInstance().setWarningFormat("");
	Logger::getInstance().setErrorFormat("");

	return result;
}