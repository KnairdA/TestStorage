#ifndef TEST_STORAGE_SRC_STORAGE_ELEMENT_GUARD_H_
#define TEST_STORAGE_SRC_STORAGE_ELEMENT_GUARD_H_

#include <utility>

#include "io/file.h"

namespace TestStorage {

template <typename Type>
template <typename Base>
class Storage<Type>::element_guard {
	friend Storage<Type>;

	public:
		typedef typename Type::template type<Base> element_type;

		typename std::add_pointer<element_type>::type operator->() {
			return &this->element_;
		}

	protected:
		element_guard(File* file, std::ptrdiff_t index):
			buffer_(
				file->mirror(index * element_type::size, element_type::size)
			),
			element_(buffer_->data()) {
			static_assert(
				!std::is_const<Base>::value,
				"This constructor is only valid for non-const base types"
			);
		}

		element_guard(const File* file, std::ptrdiff_t index):
			buffer_(
				file->mirror(index * element_type::size, element_type::size)
			),
			element_(buffer_->data()) {
			static_assert(
				std::is_const<Base>::value,
				"This constructor is only valid for const base types"
			);
		}

	private:
		typename std::conditional<
			std::is_const<Base>::value,
			File::const_mirror_type,
			File::mirror_type
		>::type buffer_;

		element_type element_;

};

}

#endif  // TEST_STORAGE_SRC_STORAGE_ELEMENT_GUARD_H_
