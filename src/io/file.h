#ifndef TEST_STORAGE_SRC_IO_FILE_H_
#define TEST_STORAGE_SRC_IO_FILE_H_

#include <string>
#include <cstddef>

#include "exceptions.h"
#include "buffer_guard.h"

namespace TestStorage {

class File {
	public:
		File(const std::string&);
		~File();

		std::size_t size() const;
		BufferGuard read(std::ptrdiff_t, std::size_t) const;

		operator int();

		void resize(std::size_t);
		void grow(std::ptrdiff_t);

		template <typename Type>
		void write(std::ptrdiff_t, Type);

	private:
		const int descriptor_;

};

}

#endif  // TEST_STORAGE_SRC_IO_FILE_H_
