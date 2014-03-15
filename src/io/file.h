#ifndef TEST_STORAGE_SRC_IO_FILE_H_
#define TEST_STORAGE_SRC_IO_FILE_H_

#include <string>

#include "exceptions.h"
#include "buffer_guard.h"

namespace TestStorage {

class File {
	public:
		File(const std::string&);
		~File();

		operator int();

		off_t size();
		void resize(off_t);

		BufferGuard<uint8_t> read(off_t, size_t);
		BufferGuard<const uint8_t> read(off_t, size_t) const;

		template <typename Type>
		void write(std::ptrdiff_t, Type);

		void grow(size_t);

	private:
		const int descriptor_;

};

}

#endif  // TEST_STORAGE_SRC_IO_FILE_H_
