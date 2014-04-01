#ifndef TEST_STORAGE_SRC_STORAGE_CONTAINER_REFERENCE_H_
#define TEST_STORAGE_SRC_STORAGE_CONTAINER_REFERENCE_H_

#include <utility>

#include "BinaryMapping/src/container.h"

#include "io/file.h"

namespace TestStorage {

template <typename Type>
template <typename Base>
class Storage<Type>::container_reference {
	friend Storage<Type>;

	public:
		typedef typename BinaryMapping::Container<Type> container_type;

		typename std::add_pointer<container_type>::type operator->() {
			return &this->container_;
		}

	protected:
		container_reference(File* file, std::ptrdiff_t index, std::size_t size):
			buffer_(file->mirror(
				index * container_type::element_type::size,
				size  * container_type::element_type::size
			)),
			container_(buffer_->data(), buffer_->size()) {
			static_assert(
				!std::is_const<Base>::value,
				"This constructor is only valid for non-const base types"
			);
		}

	private:
		typename std::conditional<
			std::is_const<Base>::value,
			void,
			File::mirror_type
		>::type buffer_;

		container_type container_;

};

}

#endif  // TEST_STORAGE_SRC_STORAGE_CONTAINER_REFERENCE_H_
