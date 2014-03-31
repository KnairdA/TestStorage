#ifndef TEST_STORAGE_SRC_IO_FILE_H_
#define TEST_STORAGE_SRC_IO_FILE_H_

#include <string>
#include <cstddef>

#include "exceptions.h"
#include "buffer_guard.h"

namespace TestStorage {

class File {
	template <typename> class buffered_slice;

	public:
		typedef buffered_slice<BufferGuard::memory_type> buffered_type;
		typedef buffered_slice<const BufferGuard::memory_type> const_buffered_type;

		File(const std::string&);
		~File();

		std::size_t size() const;
		BufferGuard read(std::ptrdiff_t, std::size_t) const;

		buffered_type mirror(std::ptrdiff_t, std::size_t);
		const_buffered_type mirror(std::ptrdiff_t, std::size_t) const;

		operator int();

		void resize(std::size_t);
		void grow(std::ptrdiff_t);

		template <typename Type>
		void write(std::ptrdiff_t, Type);

		template <typename Type>
		void append(Type);

	private:
		const int descriptor_;

};

}

#include "buffered_slice.h"

#endif  // TEST_STORAGE_SRC_IO_FILE_H_
