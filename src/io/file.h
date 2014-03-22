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

		operator int();

		std::size_t size();
		void resize(std::ptrdiff_t);

		BufferGuard<std::uint8_t> read(std::ptrdiff_t, std::size_t);
		BufferGuard<const std::uint8_t> read(std::ptrdiff_t, std::size_t) const;

		template <typename Type>
		void write(std::ptrdiff_t, Type);

		void grow(std::size_t);

	private:
		const int descriptor_;

};

}

#endif  // TEST_STORAGE_SRC_IO_FILE_H_
