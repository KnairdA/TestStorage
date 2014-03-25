#ifndef TEST_STORAGE_SRC_STORAGE_BUFFERED_STRUCTURE_GUARD_H_
#define TEST_STORAGE_SRC_STORAGE_BUFFERED_STRUCTURE_GUARD_H_

#include <utility>

#include "io/file.h"
#include "io/buffer_guard.h"

namespace TestStorage {

template <typename> class Storage;

template <typename Type>
class BufferedStructureGuard {
	public:
		typedef Type element_type;

		~BufferedStructureGuard() {
			this->file_->template write<
				std::pair<
					BufferGuard::const_pointer,
					const BufferGuard::size_type
				>
			>(this->offset_, this->buffer_);
		}

		typename std::add_pointer<element_type>::type operator->() {
			return &this->structure_;
		}

	protected:
		friend Storage<Type>;

		BufferedStructureGuard(File* file, std::ptrdiff_t index):
			offset_(index * element_type::size),
			file_(file),
			buffer_(file->read(offset_, element_type::size)),
			structure_(buffer_.data()) { }

	private:
		const std::ptrdiff_t offset_;

		File* const file_;
		BufferGuard buffer_;
		Type structure_;

};

}

#endif  // TEST_STORAGE_SRC_STORAGE_BUFFERED_STRUCTURE_GUARD_H_
