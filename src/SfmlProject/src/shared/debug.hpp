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

	void log(std::string msg)
	{
		// Time
		std::cout << "[ " << st.wHour + 1 << ":" << st.wMinute << ":" << st.wSecond << " ] ";

		// Message
		std::cout << msg << std::endl;
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