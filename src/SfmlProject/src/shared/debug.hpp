#pragma once

#include <windows.h>
#include <sysinfoapi.h> // Time
#include <iostream>

class Debug
{
private:
	// System time
	SYSTEMTIME st; // , lt;
public:
	Debug()
	{
		initSystime();
	}

	/**
	 * Log message to screen with timestamp
	 * @param msg Message to log
	*/
	void log(std::string msg)
	{
#ifdef _DEBUG
		// Time
		std::cout << "[" << st.wHour + 1 << ":" << st.wMinute << ":" << st.wSecond << "] ";

		// Message
		std::cout << msg << std::endl;
#endif // _DEBUG
	}

private:
	/**
	 * @brief Initialize system time for debugging
	*/
	void initSystime()
	{
		GetSystemTime(&st);
	}
};