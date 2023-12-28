#pragma once
#include "logger.h"
#include <string>
#include <sstream>
#include <thread>
#include <vector>


using namespace mylog;

namespace threadfn {

	void loggingFunction() {
		for (int i = 0; i < 100; i++) {
			Logger::getInstance().log("Some thread is logging a message.");
		}
	}

}

bool testThreadSafe() {
	std::string fileName = "logtest.txt";
	Logger::getInstance().setLogFile(fileName);

	std::vector<std::thread> threads;

	for (int i = 0; i < 10; i++) {
		threads.emplace_back(threadfn::loggingFunction);
	}

	for (auto& t : threads) {
		t.join();
	}

	const int maxLineCount = 10 * 100;
	const std::string lineString = "Some thread is logging a message.";
	bool result = true;


	std::ifstream inputFileStream(fileName);
	std::string line;
	int lineCount = 0;
	while (std::getline(inputFileStream, line)) {
		result &= line == lineString;
		lineCount++;
		if (!result)
			break;
	}
	result &= lineCount == maxLineCount;
	inputFileStream.close();


	std::ofstream outputFileStream(fileName);
	outputFileStream.flush();
	outputFileStream.close();

	Logger::getInstance().setLogFile("");

	return result;
}