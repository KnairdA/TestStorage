#ifndef TEST_STORAGE_SRC_IO_MMAP_H_
#define TEST_STORAGE_SRC_IO_MMAP_H_

#include <sys/mman.h>

#include <cstdint>

#include "file.h"

namespace TestStorage {

class MMap {
	public:
		MMap(File*);
		~MMap();

		BufferGuard data();

	private:
		File* const file_;
		void* data_;

};

}

#endif  // TEST_STORAGE_SRC_IO_MMAP_H_
