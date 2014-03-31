#ifndef TEST_STORAGE_SRC_IO_BUFFERED_SLICE_H_
#define TEST_STORAGE_SRC_IO_BUFFERED_SLICE_H_

#include "io/file.h"

namespace TestStorage {

template <typename Base>
class File::buffered_slice {
	friend File;

	public:
		~buffered_slice() {
			if ( this->file_ != nullptr ) {
				this->file_->template write<
					std::pair<
						BufferGuard::const_pointer,
						const BufferGuard::size_type
					>
				>(this->offset_, this->buffer_);
			}
		}

		typename std::add_pointer<BufferGuard>::type operator->() {
			return &this->buffer_;
		}

	protected:
		buffered_slice(File* file, std::ptrdiff_t offset, std::size_t size):
			offset_(offset),
			size_(size),
			file_(file),
			buffer_(file->read(offset_, size_)) {
			static_assert(
				!std::is_const<Base>::value,
				"This constructor is only valid for non-const base types"
			);
		}

		buffered_slice(const File* file, std::ptrdiff_t offset, std::size_t size):
			offset_(offset),
			size_(size),
			file_(nullptr),
			buffer_(file->read(offset_, size_)) {
			static_assert(
				std::is_const<Base>::value,
				"This constructor is only valid for const base types"
			);
		}

	private:
		const std::ptrdiff_t offset_;
		const std::size_t size_;

		File* const file_;
		BufferGuard buffer_;

};

}

#endif  // TEST_STORAGE_SRC_IO_BUFFERED_SLICE_H_
