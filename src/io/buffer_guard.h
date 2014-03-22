#ifndef TEST_STORAGE_SRC_IO_BUFFER_GUARD_H_
#define TEST_STORAGE_SRC_IO_BUFFER_GUARD_H_

#include <tuple>
#include <cstddef>

namespace TestStorage {

class BufferGuard {
	public:
		typedef std::uint8_t memory_type;
		typedef std::size_t size_type;
		typedef memory_type* const pointer;
		typedef const memory_type* const const_pointer;

		BufferGuard(pointer, std::size_t, bool = false);
		explicit BufferGuard(std::size_t);

		~BufferGuard();

		inline operator std::pair<pointer, const size_type>();
		inline operator std::pair<const_pointer, const size_type>() const;

		inline pointer data();

	private:
		pointer data_;
		const std::size_t size_;
		const bool owner_;

};

}

#endif  // TEST_STORAGE_SRC_IO_BUFFER_GUARD_H_
