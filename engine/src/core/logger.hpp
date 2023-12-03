#pragma once

#include "define.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <filesystem>

namespace LIB_NAMESPACE
{

#define FT_CRITICAL(...) ft::log << ft::Logger::Level::CRITICAL << __VA_ARGS__ << std::endl
#define FT_ERROR(...) ft::log << ft::Logger::Level::ERROR << __VA_ARGS__ << std::endl
#define FT_WARNING(...) ft::log << ft::Logger::Level::WARNING << __VA_ARGS__ << std::endl
#define FT_INFO(...) ft::log << ft::Logger::Level::INFO << __VA_ARGS__ << std::endl
#define FT_DEBUG(...) ft::log << ft::Logger::Level::DEBUG << __VA_ARGS__ << std::endl
#define FT_TRACE(...) ft::log << ft::Logger::Level::TRACE << __VA_ARGS__ << std::endl

	/**
	 * @brief A class that represents a file.
	*/
	class File: public std::ofstream
	{

	public:

		/**
		 * @brief Construct a new File object which opens a file.
		 * 
		 * @param path The path to the file.
		 * 
		 * @throw std::runtime_error if the file could not be opened.
		*/
		File(const std::filesystem::path & path): std::ofstream(path)
		{
			if (!is_open())
			{
				std::runtime_error("Could not open log file: " + path.string());
			}
		}

		File(File &&other): std::ofstream(std::move(other)) {}

		/**
		 * @brief Destroy the File object and close the file.
		*/
		~File()
		{
			close();
		}

	};

	class LogLevel
	{

	public:

		/**
		 * @brief The different levels of logging.
		*/
		enum class Value
		{
			CRITICAL = 0,
			ERROR = 1,
			WARNING = 2,
			INFO = 3,
			DEBUG = 4,
			TRACE = 5,
			MAX = 6
		};

		/**
		 * @brief Holds the current level of logging.
		*/
		Value value;

		/**
		 * @brief A map of the different levels of logging to their string representations.
		*/
		inline static std::string const levelToString[static_cast<uint32_t>(Value::MAX)] =
		{
			"[CRITICAL]:",
			"[ERROR]   :",
			"[WARNING] :",
			"[INFO]    :",
			"[DEBUG]   :",
			"[TRACE]   :"
		};

		/**
		 * @brief A map of the different levels of logging to their color codes.
		*/
		inline static std::string const levelToColor[static_cast<uint32_t>(Value::MAX)] =
		{
			"\e[33;41;1m",
			"\e[31m",
			"\e[33m",
			"\e[32m",
			"\e[34m",
			"\e[35m"
		};

	};


	// TODO: Render the logger thread-safe.


	/**
	 * @brief A class for logging messages to the console and to files.
	*/
	FT_API class Logger
	{
	
	public:

		typedef LogLevel::Value Level;


		/**
		 * @brief Construct a new Logger object.
		*/
		Logger(): _fileInitialized(false) {}

		/**
		 * @brief Construct a new Logger object and open 5 different files for logging. If the files exist, they will be overwritten.
		 * 
		 * @param path The path to the log files.
		 * 
		 * @throw std::runtime_error if a log file could not be opened.
		*/
		Logger(const std::filesystem::path & path)
		{
			configure(path);
		}

		/**
		 * @brief Open 5 different files for logging. If the files exist, they will be overwritten.
		 * 
		 * @param path The path to the log files.
		 * 
		 * @throw std::runtime_error if a log file could not be opened.
		*/
		void configure(const std::filesystem::path & path)
		{
			_logFiles[0] = std::make_unique<File>(path.string() + "/critical.log");
			_logFiles[1] = std::make_unique<File>(path.string() + "/error.log");
			_logFiles[2] = std::make_unique<File>(path.string() + "/warning.log");
			_logFiles[3] = std::make_unique<File>(path.string() + "/info.log");
			_logFiles[4] = std::make_unique<File>(path.string() + "/debug.log");
			_logFiles[5] = std::make_unique<File>(path.string() + "/trace.log");
			_fileInitialized = true;
		}

		/**
		 * @brief Set the minimum level of messages to log to the console.
		 * 
		 * @param level The level to set.
		*/
		void setLevel(Level level)
		{
			_minConsoleLevel = level;
		}

		/**
		 * @brief Return the minimum level of messages to log to the console.
		*/
		Level level() const
		{
			return _minConsoleLevel;
		}

		/**
		 * @brief Enable or disable timestamps.
		 * 
		 * @param enabled Whether or not to enable timestamps.
		*/
		void setTimestamp(bool enabled)
		{
			_timestampEnabled = enabled;
		}

		/**
		 * @brief Set the message level.
		 * 
		 * @param level The level to set.
		 * 
		 * @throw std::runtime_error if a message is currently being logged.
		*/
		Logger & operator<<(Level level)
		{
			if (!_currentMsg.str().empty())
			{
				std::runtime_error("Cannot change message level while a message is being logged. Please flush the message first with std::endl.");
			}

			_nextMsgLevel = level;
			return *this;
		}

		/**
		 * @brief Transfer a manipulator to the stringstream buffer waiting to be flushed. If the manipulator is std::endl, the buffer will be flushed.
		 * 
		 * @param manipulator The manipulator to transfer.
		*/
		Logger & operator<<(std::wostream & (*manipulator)(std::wostream &))
		{
			if (manipulator == static_cast<std::wostream & (*)(std::wostream &)>(std::endl))
			{
				_flush();
			}
			else
			{
				_currentMsg << manipulator;
			}

			return *this;
		}

		/**
		 * @brief Transfer a argument to the stringstream buffer waiting to be flushed.
		*/
		template <typename T>
		Logger & operator<<(T const & arg)
		{
			_currentMsg << arg;
			return *this;
		}
	
	private:

		bool _fileInitialized = false;

		std::stringstream _currentMsg;

		std::unique_ptr<File> _logFiles[static_cast<int>(LogLevel::Value::MAX)];
		LogLevel::Value _minConsoleLevel = LogLevel::Value::TRACE;
		LogLevel::Value _nextMsgLevel = LogLevel::Value::INFO;

		bool _timestampEnabled = true;


		/**
		 * @brief Flush the stringstream buffer to the console and to the appropriates log files.
		*/
		void _flush()
		{
			if (_currentMsg.str().empty())
			{
				return;
			}
			_writeToConsole(_currentMsg.str());
			if (_fileInitialized)
				_writeToFile(_currentMsg.str());
			_currentMsg.str("");
		}

		/**
		 * @brief Return the appropriate log file for the message level.
		*/
		File & _logFile(Level level) const
		{
			return *_logFiles[static_cast<int>(level)].get();
		}

		/**
		 * @brief Write the message level to the console if the message level is greater than or equal to the minimum console level.
		*/
		void _writeToConsole(std::string const & message)
		{
			if (_nextMsgLevel <= _minConsoleLevel)
			{
				std::cout << _timestamp() << _levelHeader(_nextMsgLevel) << message << std::endl;
			}
		}

		/**
		 * @brief Write the message level to the appropriate log file.
		*/
		void _writeToFile(std::string const & message)
		{

			std::string finalMessage = _timestamp() + _levelHeader(_nextMsgLevel, false) + message;
			switch (_nextMsgLevel)
			{
				case LogLevel::Value::CRITICAL:
					_logFile(LogLevel::Value::CRITICAL) << finalMessage << std::endl;
				case LogLevel::Value::ERROR:
					_logFile(LogLevel::Value::ERROR) << finalMessage << std::endl;
				case LogLevel::Value::WARNING:
					_logFile(LogLevel::Value::WARNING) << finalMessage << std::endl;
				case LogLevel::Value::INFO:
					_logFile(LogLevel::Value::INFO) << finalMessage << std::endl;
				case LogLevel::Value::DEBUG:
					_logFile(LogLevel::Value::DEBUG) << finalMessage << std::endl;
				case LogLevel::Value::TRACE:
					_logFile(LogLevel::Value::TRACE) << finalMessage << std::endl;
				default:
					break;
			}
		}

		/**
		 * @brief Return the header for the message level.
		*/
		std::string _levelHeader(Level level, bool color = true)
		{
			std::stringstream ss;
			ss << (color ? LogLevel::levelToColor[static_cast<int>(level)] : "")
				<< LogLevel::levelToString[static_cast<int>(level)]
				<< (color ? "\e[0m " : " ");
			return ss.str();
		}

		/**
		 * @brief Return the current timestamp.
		*/
		std::string _timestamp()
		{
			if (!_timestampEnabled)
			{
				return "";
			}
			std::time_t t = std::time(nullptr);
			std::tm tm = *std::localtime(&t);
			std::stringstream ss;
			ss << std::put_time(&tm, "[%Y-%m-%d %H:%M:%S] ");
			return ss.str();
		}

	};

	extern Logger log;
	
} // namespace LIB_NAMESPACE