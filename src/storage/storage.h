#ifndef TEST_STORAGE_SRC_STORAGE_STORAGE_H_
#define TEST_STORAGE_SRC_STORAGE_STORAGE_H_

#include "io/file.h"

#include <stdexcept>

namespace TestStorage {

template <typename Type>
class Storage {
	public:
		typedef typename Type::template type<std::uint8_t> element_type;

		template <typename> class element_guard;

		Storage(const std::string& path):
			file_(path) { }

		std::size_t size() const {
			return this->file_.size() / element_type::size;
		}

		element_guard<std::uint8_t> at(std::size_t index) {
			if ( index < this->size() ) {
				return element_guard<std::uint8_t>(
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

		element_guard<std::uint8_t> add() {
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
