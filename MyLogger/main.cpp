#include "logger.h"
#include <sstream>
#include <iostream>
#include "tests.h"


int main() {
	//runTests();

	mylog::Logger::getInstance().setOutputStream(&std::cout);
	mylog::Logger::getInstance().setLogFile("log.txt");

	mylog::Logger::getInstance().setInfoFormat("[&t] {&T}: {}");
	mylog::Logger::getInstance().setWarningFormat("[&t] {&T}: {}");
	mylog::Logger::getInstance().setErrorFormat("[&t] {&T}: {} !&t!");

	
	mylog::log("&T Hello World!");
	mylog::info("The value is 1");
	mylog::warning("The value cannot be 0");
	mylog::error("value -1 will exit the program");


	return 0;
}