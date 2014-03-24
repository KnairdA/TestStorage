#ifndef TEST_STORAGE_SRC_STORAGE_STORAGE_H_
#define TEST_STORAGE_SRC_STORAGE_STORAGE_H_

#include "io/file.h"
#include "buffered_structure_guard.h"

#include "BinaryMapping/src/container.h"

namespace TestStorage {

template <typename Type>
class Storage {
	public:
		typedef Type element_type;

		Storage(const std::string& path):
			file_(path) { }

		BufferedStructureGuard<element_type> at(std::size_t index) {
			if ( (index+1) * element_type::size  <= this->file_.size() ) {
				return BufferedStructureGuard<element_type>(&this->file_, index);
			}
		}

		BufferedStructureGuard<element_type> add() {
			const std::size_t index(this->file_.size() / element_type::size);

			this->file_.grow(element_type::size);

			return this->at(index);
		}

	private:
		File file_;

};

}

#endif  // TEST_STORAGE_SRC_STORAGE_STORAGE_H_
