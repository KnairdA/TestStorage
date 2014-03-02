#include "mmap.h"

#include "exceptions.h"

namespace TestStorage {

MMap::MMap(File* file):
	file_(file),
	data_(mmap(
		nullptr,
		file->size(),
		ProtFlags,
		MapFlags,
		*file, 
		0
	)) {
	if ( this->data_ == reinterpret_cast<void*>(-1) ) {
		throw io_exception();
	}
}

MMap::~MMap() {
	munmap(this->data_, this->file_->size());
}

uint8_t* MMap::get() const {
	return reinterpret_cast<uint8_t*>(this->data_);
}

}
