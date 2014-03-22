#include "file.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <cstddef>

namespace {

const int OpenFlags   = O_RDWR  | O_CREAT;
const mode_t OpenMode = S_IRUSR | S_IWUSR;

}

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

std::size_t File::size() {
	struct stat info;

	fstat(this->descriptor_, &info);

	return info.st_size;
}

void File::resize(std::ptrdiff_t size) {
	if ( ftruncate(this->descriptor_, size) == -1 ) {
		throw io_exception();
	}
}

BufferGuard<std::uint8_t> File::read(std::ptrdiff_t offset, std::size_t size) {
	void* buffer{};

	if ( ssize_t readSize = pread(this->descriptor_,
	                              buffer,
	                              size,
	                              offset) >= 0 ) {
		return BufferGuard<std::uint8_t>(
			reinterpret_cast<std::uint8_t*>(buffer),
			readSize,
			true
		);
	} else {
		throw io_exception(); 
	}
}

template <typename Type>
void File::write(std::ptrdiff_t offset, Type data) {
	if ( pwrite(this->descriptor_,
	            reinterpret_cast<const void*>(data.first),
	            data.second,
	            offset) < 0 ) {
		throw io_exception();
	}
}

template void File::write<BufferGuard<std::uint8_t>::pointer>(
	std::ptrdiff_t,
	BufferGuard<std::uint8_t>::pointer
);

template void File::write<BufferGuard<std::uint8_t>::const_pointer>(
	std::ptrdiff_t,
	BufferGuard<std::uint8_t>::const_pointer
);

void File::grow(std::size_t space) {
	this->resize(this->size() + space);
}

}
