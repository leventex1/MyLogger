#pragma once
#include <assert.h>
#include <iostream>
#include "testInitialization.h"
#include "testStreams.h"
#include "testThreadSafe.h"
#include "testFormating.h"


void runTests() {

	std::cout << "test initialization: ";
	assert(testInitialization() && "Singleton instance returns different objects.");
	std::cout << "+" << std::endl;

	std::cout << "test streams: ";
	assert(testOutputStream() && "The stream havent got the same message.");
	std::cout << "+";
	assert(testFileStreamWrite() && "File stream havent got the same message.");
	std::cout << "+" << std::endl;

	std::cout << "test thread safety: ";
	assert(testThreadSafe() && "The logger is not thread safe.");
	std::cout << "+" << std::endl;

	std::cout << "test formating: ";
	assert(testFormating() && "Error in logger formating.");
	std::cout << "+" << std::endl;

}