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

std::size_t File::size() const {
	struct stat info;

	fstat(this->descriptor_, &info);

	return info.st_size;
}

BufferGuard File::read(std::ptrdiff_t offset, std::size_t size) const {
	BufferGuard buffer(size);

	ssize_t readSize(pread(
		this->descriptor_,
		reinterpret_cast<void*>(buffer.data()),
		size,
		offset
	));

	if ( readSize == static_cast<ssize_t>(size) ) {
		return buffer;
	} else {
		throw io_exception(); 
	}
}

void File::resize(std::size_t size) {
	if ( ftruncate(this->descriptor_, size) == -1 ) {
		throw io_exception();
	}
}

void File::grow(std::ptrdiff_t offset) {
	this->resize(this->size() + offset);
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

template <typename Type>
void File::append(Type data) {
	const std::ptrdiff_t size(this->size());

	this->grow(data.second);
	this->write(size, data);
}

}

#include "file.tmpl"
