#ifndef TEST_STORAGE_SRC_IO_MAPPED_BUFFER_H_
#define TEST_STORAGE_SRC_IO_MAPPED_BUFFER_H_

#include "io/file.h"
#include <sys/mman.h>

namespace {

const int ProtFlags = PROT_READ | PROT_WRITE;
const int MapFlags  = MAP_SHARED;

}

namespace TestStorage {

template <typename Base>
class File::mapped_buffer {
	friend File;

	public:
		~mapped_buffer() {
			munmap(this->data_, this->size_);
		}

		typename std::add_pointer<BufferGuard>::type operator->() {
			return &this->buffer_;
		}

	protected:
		mapped_buffer(File* file, std::ptrdiff_t offset, std::size_t size):
			size_(size),
			file_(file),
			data_(reinterpret_cast<BufferGuard::pointer>(mmap(
				nullptr,
				size_,
				ProtFlags,
				MapFlags,
				*file, 
				offset
			))),
			buffer_(data_, size_) {
			static_assert(
				!std::is_const<Base>::value,
				"This constructor is only valid for non-const base types"
			);

			if ( this->data_ == reinterpret_cast<void*>(-1) ) {
				throw io_exception();
			}
		}

	private:
		const std::size_t size_;

		File* const file_;
		BufferGuard::pointer data_;
		BufferGuard buffer_;

};

}

#endif  // TEST_STORAGE_SRC_IO_MAPPED_BUFFER_H_
