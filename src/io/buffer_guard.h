#ifndef TEST_STORAGE_SRC_IO_BUFFER_GUARD_H_
#define TEST_STORAGE_SRC_IO_BUFFER_GUARD_H_

#include <tuple>
#include <cstdint>

namespace TestStorage {

class BufferGuard {
	public:
		typedef std::pair<uint8_t*const, const size_t> buffer_pair;

		BufferGuard(uint8_t*const d, size_t s, bool o = false):
			data(d),
			size(s),
			owner(o) { }

		BufferGuard(const buffer_pair& pair):
			BufferGuard(pair.first, pair.second) { }

		explicit BufferGuard(size_t s):
			data(reinterpret_cast<uint8_t*const>(
				std::calloc(s, sizeof(uint8_t)))
			),
			size(s),
			owner(true) { }

		~BufferGuard() {
			if ( this->owner ) {
				std::free(this->data);
			}
		}

		operator buffer_pair() const {
			return std::make_pair(this->data, this->size);
		}

		uint8_t*const data;
		const size_t size;

	private:
		const bool owner;
};

}

#endif  // TEST_STORAGE_SRC_IO_BUFFER_GUARD_H_
