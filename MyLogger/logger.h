#pragma once
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <mutex>
#include <iostream>
#include <vector>


namespace mylog {
	/*
		Log formats: &t=type, &T=time, {}=message
		Example: ("[&t] &T: Error occured with message: {}")
	*/

	enum class LogSeverity {
		NONE = 0,
		INFO,
		WARNING,
		ERROR
	};

	class Logger {
	public:

		struct LogMessageFormat {
			std::string format;
			std::string severityName;
		};

		static Logger& getInstance();

		void setLogFile(const std::string& filePath);
		void setOutputStream(std::ostream* ostream);

		void setInfoFormat(const std::string& format);
		void setWarningFormat(const std::string& format);
		void setErrorFormat(const std::string & format);

		void log(const std::string& message, LogSeverity severity=LogSeverity::NONE);

	private:
		Logger();
		~Logger();

		LogMessageFormat constructFormat(const std::string& format, const std::string& severityName) const;
		std::string constructMessage(const std::string& message, const LogMessageFormat& format) const;
		void replaceMessageString(std::string& resource, const std::string& target, const std::string& to) const;

		Logger(const Logger&) = delete;
		Logger* operator=(const Logger&) = delete;
		Logger(Logger&&) = delete;


		LogMessageFormat m_InfoFormat;
		LogMessageFormat m_WarningFormat;
		LogMessageFormat m_ErrorFormat;

		std::ofstream m_LogFile;
		std::ostream* m_Ostream;
		std::mutex mu_;
	};

	void log(const std::string& message);
	void info(const std::string& message);
	void warning(const std::string& message);
	void error(const std::string& message);

}