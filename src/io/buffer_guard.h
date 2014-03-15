#ifndef TEST_STORAGE_SRC_IO_BUFFER_GUARD_H_
#define TEST_STORAGE_SRC_IO_BUFFER_GUARD_H_

#include <tuple>
#include <cstddef>

namespace TestStorage {

template <typename Type>
class BufferGuard {
	public:
		typedef std::pair<Type*const, const std::size_t> pointer;
		typedef std::pair<const Type*const, const std::size_t> const_pointer;

		BufferGuard(Type*const data, std::size_t size, bool owner = false):
			data_(data),
			size_(size),
			owner_(owner) { }

		BufferGuard(const pointer& pair):
			BufferGuard(pair.first, pair.second) { }

		explicit BufferGuard(std::size_t size):
			data_(new Type[size]),
			size_(size),
			owner_(true) { }

		~BufferGuard() {
			if ( this->owner_ ) {
				delete[] this->data_;
			}
		}

		inline operator pointer() {
			return std::make_pair(this->data_, this->size_);
		}

		inline operator const_pointer() const {
			return std::make_pair(this->data_, this->size_);
		}

		inline pointer data() {
			return this->data_;
		}

	private:
		Type*const data_;
		const size_t size_;
		const bool owner_;

};

}

#endif  // TEST_STORAGE_SRC_IO_BUFFER_GUARD_H_
