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

auto BufferGuard::data() -> pointer {
	return this->data_;
}

auto BufferGuard::data() const -> const_pointer {
	return this->data_;
}

auto BufferGuard::size() const -> size_type {
	return this->size_;
}

}
