#ifndef TEST_STORAGE_SRC_STORAGE_ELEMENT_GUARD_H_
#define TEST_STORAGE_SRC_STORAGE_ELEMENT_GUARD_H_

#include <utility>

#include "io/file.h"
#include "io/buffer_guard.h"

namespace TestStorage {

template <typename Type>
template <typename Base>
class Storage<Type>::element_guard {
	friend Storage<Type>;

	public:
		typedef typename Type::template type<Base> element_type;

		~element_guard() {
			this->file_.template write<
				std::pair<
					BufferGuard::const_pointer,
					const BufferGuard::size_type
				>
			>(this->offset_, this->buffer_);
		}

		typename std::add_pointer<element_type>::type operator->() {
			return &this->element_;
		}

	protected:
		element_guard(File& file, std::ptrdiff_t index):
			offset_(index * element_type::size),
			file_(file),
			buffer_(file.read(offset_, element_type::size)),
			element_(buffer_.data()) { }

	private:
		const std::ptrdiff_t offset_;

		File& file_;
		BufferGuard buffer_;
		element_type element_;

};

}

#endif  // TEST_STORAGE_SRC_STORAGE_ELEMENT_GUARD_H_
