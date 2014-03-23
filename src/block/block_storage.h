#ifndef TEST_STORAGE_SRC_BLOCK_BLOCK_STORAGE_H_
#define TEST_STORAGE_SRC_BLOCK_BLOCK_STORAGE_H_

#include "io/file.h"

#include "BinaryMapping/src/container.h"

namespace TestStorage {

template <std::size_t BlockSize>
class BlockStorage {
	typedef BinaryMapping::Tuple<
		std::uint32_t,
		BinaryMapping::ByteField<BlockSize>
	> block_type;

	public:
		BlockStorage(const std::string& path):
			file_(path) { }

		void add(std::size_t count) {
			this->file_.grow(count * block_type::size);
		}

		std::size_t size() const {
			return this->file_.size() / block_type::size;
		}

	private:
		File file_;

};

}

#endif  // TEST_STORAGE_SRC_BLOCK_BLOCK_STORAGE_H_
