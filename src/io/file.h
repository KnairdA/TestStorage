#ifndef TEST_STORAGE_SRC_IO_FILE_H_
#define TEST_STORAGE_SRC_IO_FILE_H_

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string>

#include "buffer_guard.h"

namespace TestStorage {

class File {
	public:
		File(const std::string&);
		~File();

		operator int();

		off_t size();
		void resize(off_t);

		BufferGuard read(off_t, size_t);
		void write(off_t, const BufferGuard::buffer_pair&);

		void grow(size_t);

	private:
		static const int OpenFlags   = O_RDWR  | O_CREAT;
		static const mode_t OpenMode = S_IRUSR | S_IWUSR;

		const int descriptor_;

};

}

#endif  // TEST_STORAGE_SRC_IO_FILE_H_
