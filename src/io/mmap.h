#ifndef TEST_STORAGE_SRC_IO_MMAP_H_
#define TEST_STORAGE_SRC_IO_MMAP_H_

#include <sys/mman.h>

#include <cstdint>

namespace TestStorage {

class File;

class MMap {
	public:
		MMap(File*);
		~MMap();

		inline uint8_t* get() const;

	private:
		static const int ProtFlags = PROT_READ | PROT_WRITE;
		static const int MapFlags  = MAP_SHARED;

		File* const file_;
		void* data_;

};

}

#endif  // TEST_STORAGE_SRC_IO_MMAP_H_
