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

		uint8_t* get() const;

	private:
		static const int ProtFlags = PROT_READ | PROT_WRITE;
		static const int MapFlags  = MAP_SHARED;

		File* const file_;
		void* data_;

};

}

#endif  // TEST_STORAGE_SRC_IO_MMAP_H_
