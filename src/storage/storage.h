#ifndef TEST_STORAGE_SRC_STORAGE_STORAGE_H_
#define TEST_STORAGE_SRC_STORAGE_STORAGE_H_

#include "io/file.h"

#include "BinaryMapping/src/container.h"

#include <stdexcept>

namespace TestStorage {

template <typename Type>
class Storage {
	public:
		typedef Type element_type;

		class element_guard;

		Storage(const std::string& path):
			file_(path) { }

		std::size_t size() const {
			return this->file_.size() / element_type::size;
		}

		element_guard at(std::size_t index) {
			if ( index < this->size() ) {
				return element_guard(
					this->file_,
					index
				);
			} else {
				throw std::out_of_range("range_violated");
			}
		}

		void reset(std::size_t index) {
			if ( index < this->size() ) {
				this->file_.template write<
					std::pair<
						BufferGuard::const_pointer,
						const BufferGuard::size_type
					>
				>(
					index * element_type::size,
					BufferGuard(element_type::size)
				);
			} else {
				throw std::out_of_range("range_violated");
			}
		}

		element_guard add() {
			const std::size_t index(this->size());

			this->file_.grow(element_type::size);

			return this->at(index);
		}

	private:
		File file_;

};

}

#include "element_guard.h"

#endif  // TEST_STORAGE_SRC_STORAGE_STORAGE_H_
