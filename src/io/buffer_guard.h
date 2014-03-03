#ifndef TEST_STORAGE_SRC_IO_BUFFER_GUARD_H_
#define TEST_STORAGE_SRC_IO_BUFFER_GUARD_H_

#include <tuple>
#include <cstdint>

namespace TestStorage {

template <typename Type>
class BufferGuard {
	public:
		typedef std::pair<Type*const, const size_t> buffer_pair;

		BufferGuard(Type*const d, size_t s, bool o = false):
			data(d),
			size(s),
			owner(o) { }

		BufferGuard(const buffer_pair& pair):
			BufferGuard(pair.first, pair.second) { }

		explicit BufferGuard(size_t s):
			data(reinterpret_cast<Type*const>(
				std::calloc(s, sizeof(Type)))
			),
			size(s),
			owner(true) { }

		~BufferGuard() {
			if ( this->owner ) {
				std::free(this->data);
			}
		}

		operator buffer_pair() {
			return std::make_pair(this->data, this->size);
		}

		Type*const data;
		const size_t size;

	private:
		const bool owner;
};

}

#endif  // TEST_STORAGE_SRC_IO_BUFFER_GUARD_H_
