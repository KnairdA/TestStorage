#ifndef TEST_STORAGE_SRC_IO_MIRRORED_BUFFER_H_
#define TEST_STORAGE_SRC_IO_MIRRORED_BUFFER_H_

#include "io/file.h"

namespace TestStorage {

template <typename Base>
class File::mirrored_buffer {
	friend File;

	public:
		~mirrored_buffer() {
			if ( this->file_ != nullptr ) {
				this->file_->write(this->offset_, this->buffer_);
			}
		}

		typename std::add_pointer<BufferGuard>::type operator->() {
			return &this->buffer_;
		}

	protected:
		mirrored_buffer(File* file, std::ptrdiff_t offset, std::size_t size):
			offset_(offset),
			file_(file),
			buffer_(file->read(offset_, size)) {
			static_assert(
				!std::is_const<Base>::value,
				"This constructor is only valid for non-const base types"
			);
		}

		mirrored_buffer(const File* file, std::ptrdiff_t offset, std::size_t size):
			offset_(offset),
			file_(nullptr),
			buffer_(file->read(offset_, size)) {
			static_assert(
				std::is_const<Base>::value,
				"This constructor is only valid for const base types"
			);
		}

	private:
		const std::ptrdiff_t offset_;

		File* const file_;
		BufferGuard buffer_;

};

}

#endif  // TEST_STORAGE_SRC_IO_MIRRORED_BUFFER_H_
