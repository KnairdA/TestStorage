#ifndef TEST_STORAGE_SRC_IO_FILE_H_
#define TEST_STORAGE_SRC_IO_FILE_H_

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string>
#include <exception>

#include "BinaryMapping/src/io/buffer.h"

namespace TestStorage {

class io_exception : public std::exception {
	virtual const char* what() const throw() {
		return "io";
	}
};

class File {
	public:
		File(const std::string&);
		~File();

		inline operator int();

		inline off_t size();
		inline void resize(off_t);

		inline BinaryMapping::Buffer read(off_t, size_t);
		inline void write(off_t, const BinaryMapping::Buffer&);

		inline void grow(size_t);

	private:
		static const int OpenFlags   = O_RDWR  | O_CREAT;
		static const mode_t OpenMode = S_IRUSR | S_IWUSR;

		const int descriptor_;

};

}

#endif  // TEST_STORAGE_SRC_IO_FILE_H_
