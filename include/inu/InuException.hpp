/** @file InuException.hpp
 * @brief Exceptions used by the Inu library.
*/


#ifndef INUEXCEPTION_H
#define INUEXCEPTION_H


#include <stdexcept>


namespace inu {
	class InuException : public std::runtime_error {
	public:
		explicit InuException(const std::string& msg) : std::runtime_error(msg) {}
		explicit InuException(const char* msg) : std::runtime_error(msg) {}
	};
}


#endif
