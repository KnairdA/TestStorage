#include "file.h"

#include "exceptions.h"

namespace TestStorage {

File::File(const std::string& path):
	descriptor_(
		open(path.data(), OpenFlags, OpenMode)
	) {
	if ( this->descriptor_ == -1 ) {
		throw io_exception();
	}
}

File::~File() {
	close(this->descriptor_);
}

File::operator int() {
	return this->descriptor_;
}

off_t File::size() {
	struct stat info;

	fstat(this->descriptor_, &info);

	return info.st_size;
}

void File::resize(off_t size) {
	if ( ftruncate(this->descriptor_, size) == -1 ) {
		throw io_exception();
	}
}

BinaryMapping::Buffer File::read(off_t offset, size_t size) {
	void* buffer = nullptr;

	if ( ssize_t readSize = pread(this->descriptor_,
	                              buffer,
	                              size,
	                              offset) >= 0 ) {
		return BinaryMapping::Buffer(
			reinterpret_cast<uint8_t*>(buffer),
			readSize
		);
	} else {
		throw io_exception(); 
	}
}

void File::write(off_t offset, const BinaryMapping::Buffer& data) {
	if ( pwrite(this->descriptor_,
	            reinterpret_cast<const void*>(data.front()),
	            data.size(),
	            offset) < 0 ) {
		throw io_exception();
	}
}

void File::grow(size_t space) {
	this->resize(this->size() + space);
}

}
