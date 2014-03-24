#include "io/file.h"

#include "storage/storage.h"

#include <iostream>

int main() {
	TestStorage::Storage<
		BinaryMapping::PlainTuple<
			std::uint32_t,
			BinaryMapping::ByteField<32>
		>
	> storage("./storage/test");

	auto test(storage.add());

	test->set<0>(42);
}
