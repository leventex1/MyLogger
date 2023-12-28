#include "logger.h"
#include <chrono>
#include <format>


namespace mylog {

	
	void log(const std::string& message) { 
		Logger::getInstance().log(message); 
	}
	
	void info(const std::string& message) {
		Logger::getInstance().log(message, LogSeverity::INFO); 
	}

	void warning(const std::string& message) { 
		Logger::getInstance().log(message, LogSeverity::WARNING);
	}

	void error(const std::string& message) { 
		Logger::getInstance().log(message, LogSeverity::ERROR); 
	}


	Logger::Logger() { }

	Logger::~Logger() {
		if (m_LogFile.is_open())
			m_LogFile.close();
	}

	Logger& Logger::getInstance() {
		static Logger instance;
		return instance;
	}

	void Logger::setLogFile(const std::string& filePath) {
		std::lock_guard<std::mutex> lock(mu_);

		if (m_LogFile.is_open())
			m_LogFile.close();

		m_LogFile.open(filePath, std::ios::app);
	}

	void Logger::setOutputStream(std::ostream* ostream) {
		m_Ostream = ostream;
	}

	void Logger::log(const std::string& message, LogSeverity severity) {
		std::lock_guard<std::mutex> lock(mu_);

		std::string formatedMessage;

		switch (severity)
		{
		case mylog::LogSeverity::NONE:
			formatedMessage = constructMessage("", { message, "-" });
			break;
		case mylog::LogSeverity::INFO:
			formatedMessage = constructMessage(message, m_InfoFormat);
			break;
		case mylog::LogSeverity::WARNING:
			formatedMessage = constructMessage(message, m_WarningFormat);
			break;
		case mylog::LogSeverity::ERROR:
			formatedMessage = constructMessage(message, m_ErrorFormat);
			break;
		default:
			break;
		}

		m_LogFile << formatedMessage << std::endl;
		if(m_Ostream)
			*m_Ostream << formatedMessage << std::endl;
	}

	std::string Logger::constructMessage(const std::string& message, const LogMessageFormat& format) const {
		std::string result = format.format;

		std::string dateTime = std::format("{:%d/%m/%Y %H:%M:%OS}", std::chrono::system_clock::now());

		replaceMessageString(result, "&t", format.severityName);
		replaceMessageString(result, "&T", dateTime);
		replaceMessageString(result, "{}", message);

		return result;
	}

	void Logger::replaceMessageString(std::string& resource, const std::string& target, const std::string& to) const {
		size_t index = resource.find(target, 0);
		while (index != std::string::npos) {
			resource.replace(index, target.size(), to);
			index = resource.find(target, index + 1);
		}
	}

	Logger::LogMessageFormat Logger::constructFormat(const std::string& format, const std::string& severityName) const {
		return { format, severityName };
	}

	void Logger::setInfoFormat(const std::string& format) { 
		m_InfoFormat = constructFormat(format, "INFO"); 
	}

	void Logger::setWarningFormat(const std::string& format) { 
		m_WarningFormat = constructFormat(format, "WARNING"); 
	}

	void Logger::setErrorFormat(const std::string& format) { 
		m_ErrorFormat = constructFormat(format, "ERROR"); 
	}
	
}