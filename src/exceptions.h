#ifndef TEST_STORAGE_SRC_EXCEPTIONS_H_
#define TEST_STORAGE_SRC_EXCEPTIONS_H_

#include <exception>

namespace TestStorage {

class io_exception : public std::exception {
	virtual const char* what() const throw() {
		return "io";
	}
};


}

#endif  // TEST_STORAGE_SRC_EXCEPTIONS_H_
