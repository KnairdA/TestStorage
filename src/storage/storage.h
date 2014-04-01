#ifndef TEST_STORAGE_SRC_STORAGE_STORAGE_H_
#define TEST_STORAGE_SRC_STORAGE_STORAGE_H_

#include "io/file.h"

#include <stdexcept>

namespace TestStorage {

template <typename Type>
class Storage {
	template <typename> class element_guard;

	typedef typename Type::template type<
		BufferGuard::memory_type
	> element_type;

	typedef typename Type::template type<
		const BufferGuard::memory_type
	> const_element_type;

	public:
		typedef std::size_t size_type;
		typedef element_guard<BufferGuard::memory_type> element;
		typedef element_guard<const BufferGuard::memory_type> const_element;

		Storage(const std::string& path):
			file_(path) { }

		size_type size() const {
			return this->file_.size() / element_type::size;
		}

		const_element at(size_type index) const {
			if ( index < this->size() ) {
				return const_element(
					&this->file_,
					index
				);
			} else {
				throw std::out_of_range("range_violated");
			}
		}

		element at(size_type index) {
			if ( index < this->size() ) {
				return element(
					&this->file_,
					index
				);
			} else {
				throw std::out_of_range("range_violated");
			}
		}

		element add() {
			const size_type index(this->size());

			this->file_.grow(element_type::size);

			return this->at(index);
		}

		void reset(size_type index) {
			if ( index < this->size() ) {
				this->file_.write(
					index * element_type::size,
					BufferGuard(element_type::size)
				);
			} else {
				throw std::out_of_range("range_violated");
			}
		}

	private:
		File file_;

};

}

#include "element_guard.h"

#endif  // TEST_STORAGE_SRC_STORAGE_STORAGE_H_
