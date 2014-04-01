#ifndef TEST_STORAGE_SRC_IO_FILE_H_
#define TEST_STORAGE_SRC_IO_FILE_H_

#include <string>
#include <cstddef>

#include "exceptions.h"
#include "buffer_guard.h"

namespace TestStorage {

class File {
	template <typename> class mirrored_buffer;

	public:
		typedef mirrored_buffer<BufferGuard::memory_type> mirror_type;
		typedef mirrored_buffer<const BufferGuard::memory_type> const_mirror_type;

		File(const std::string&);
		~File();

		std::size_t size() const;
		BufferGuard read(std::ptrdiff_t, std::size_t) const;

		mirror_type mirror(std::ptrdiff_t, std::size_t);
		const_mirror_type mirror(std::ptrdiff_t, std::size_t) const;

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

#include "mirrored_buffer.h"

#endif  // TEST_STORAGE_SRC_IO_FILE_H_
