#pragma once
#include "logger.h"


using namespace mylog;

bool testInitialization() {
	Logger& instance1 = Logger::getInstance();
	Logger& instance2 = Logger::getInstance();

	return &instance1 == &instance2;
}