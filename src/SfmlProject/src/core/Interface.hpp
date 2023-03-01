#pragma once

/**
 * Base class for interface
 * 
 * All interfaces throughout the game engine should derive from this class.
*/
class Interface
{
private:
	/**
	 * Consider whether an object implements a certain interface
	 * @param object Object to check
	 * @param interface Interface to match
	 * @return True if derived from interface, false if not
	*/
	virtual bool doesImplementInterface(void* object, Interface interface) = 0;
};