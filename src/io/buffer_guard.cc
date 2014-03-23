#include "buffer_guard.h"

namespace TestStorage {

BufferGuard::BufferGuard(pointer data, std::size_t size, bool owner):
	data_(data),
	size_(size),
	owner_(owner) { }

BufferGuard::BufferGuard(std::size_t size):
	data_(new memory_type[size]),
	size_(size),
	owner_(true) { }

BufferGuard::~BufferGuard() {
	if ( this->owner_ ) {
		delete[] this->data_;
	}
}

BufferGuard::operator std::pair<pointer, const size_type>() {
	return std::make_pair(this->data_, this->size_);
}

BufferGuard::operator std::pair<const_pointer, const size_type>() const {
	return std::make_pair(this->data_, this->size_);
}

auto BufferGuard::data() -> pointer {
	return this->data_;
}

auto BufferGuard::size() const -> size_type {
	return this->size_;
}

}
